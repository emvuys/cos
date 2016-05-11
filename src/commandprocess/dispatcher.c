#include "../inc/types.h"

void insertCard(u1* imsi,
				u1* ki,
				u1* opc,
				u1* iccid,
				u1* acc,
				u1* spn,
				u1* apn,
				u1* hplmn,
				u1* ehplmn,
				u1* loci,
				u1* psloci,
				u1* fplmn) {
	LOGD_FUNC();

	initADF();
	MFRef = buildFileSystem();
	configureProfile(imsi, ki, opc, iccid, acc, spn, hplmn, ehplmn, loci, psloci, fplmn);
	initChannel();
	tlv = COS_MALLOC(sizeof(TLV));

	initAuth(ki, opc);
}

u2 dispatcher(u1* apdu, u2 apduLen, u1* responseBuf, u2* responseLen) {
	u1 ins;
	u2 sw, index;

	*responseLen = 0;

	LOGD_FUNC();
	sw = preCheckAPDU(apdu, apduLen);
	if (sw != NONE) {
		return 0;
	}
	printAPDU();

	ins = getINS();
	
#if DEBUG_LEVLE>=2
	LOGD("Chn: %02X\n", getCurChannelID());
	if (getCurEF() != INVALID_FILE) {
		LOGD("CurEF: %02X\n", getCurEF()->fid);
	}
	if (getCurDF() != INVALID_FILE) {
		LOGD("CurDF: %02X\n", getCurDF()->fid);
	}
	if (getCurADF() != INVALID_FILE) {
		LOGD("CurAD: %02X\n", getCurADF()->fid);
	}
#endif

	sw = setCurChannelID(getCLS());
	if (sw != NONE) {
		return 0;
	}
	sw = INVALID_INS;
	switch (ins) {
		case INS_SELECT:
			sw = processSelect(apdu, responseBuf, responseLen);
			break;
		case INS_STATUS:
			sw = processStatus(apdu, responseBuf, responseLen);
			break;
		case INS_VERIFY_PIN:
			sw = processVerifyPIN(apdu, responseBuf, responseLen);
			break;
		case INS_UNBLOCK_PIN:
			sw = processUnBlockPIN(apdu, responseBuf, responseLen);
			break;
		case INS_MANAGE_CHANNEL:
			sw = processManageChannel(apdu, responseBuf, responseLen);
			break;
		case INS_READ_BINARY:
			sw = processReadBin(apdu, responseBuf, responseLen);
			break;
		case INS_UPDATE_BINARY:
			sw = processUpdateBin(apdu, responseBuf, responseLen);
			break;
		case INS_READ_RECORD:
			sw = processReadRecord(apdu, responseBuf, responseLen);
			break;
		case INS_UPDATE_RECORD:
			sw = processUpdateRecord(apdu, responseBuf, responseLen);
			break;
		case INS_AUTHENTICATE:
			sw = processAuth(apdu, responseBuf, responseLen);
			break;
		case INS_PRIVATE:
			sw = getPrivateInfo(getP1(), responseBuf, responseLen);
			break;
		default:
			PRINT_STR("Unkown command");
			*responseLen = 0;
			index = 0;
			responseBuf[index ++] = sw >> 8;
			responseBuf[index ++] = sw & 0xFF;
			return index;
	}

	index = *responseLen;
	responseBuf[index ++] = sw >> 8;
	responseBuf[index ++] = sw & 0xFF;
	*responseLen = index;

	printRepon(responseBuf, *responseLen);
	return index;
}

u2 getPrivateInfo(u1 tag, u1* responseBuf, u2* len) {
	switch (tag) {
		case 0x01: // imsi
			COS_MEMCPY(responseBuf, profile->imsi->data, LENGTH_IMSI);
			*len = LENGTH_IMSI;
			break;
		case 0x02: // ki
			COS_MEMCPY(responseBuf, AuthKi, LENGTH_KI);
			*len = LENGTH_KI;
			break;
		case 0x03: // opc
			COS_MEMCPY(responseBuf, AuthOpc, LENGTH_OPC);
			*len = LENGTH_OPC;			
			break;
		default:
			return INVALID_INS;
	}
	return NONE;
}

u2 preCheckAPDU(u1* apdu, u2 apduLen) {
	if (apduLen < 4) {
		return WRONG_LENGTH;
	}
	apduCommand.cla = *(apdu);
	apduCommand.ins = *(apdu + 1);
	apduCommand.p1 = *(apdu + 2);
	apduCommand.p2 = *(apdu + 3);
	apduCommand.lc = 0;
	apduCommand.le = -1;
	
	if (apduLen == 4) {
		return NONE;
	}
	if (apduLen == 5) {
		apduCommand.le = *(apdu + 4);
		return NONE;
	}
	apduCommand.lc = *(apdu + 4);
	if (apduLen == (apduCommand.lc + 5)) {
		apduCommand.data = apdu + 5;
		return NONE;
	}
	if (apduLen == (apduCommand.lc + 6)) {
		apduCommand.lc = *(apdu + 4);
		apduCommand.data = apdu + 5;
		apduCommand.le = *(apdu + 5 + apduCommand.lc) & 0xFF;
		return NONE;
	}
	return WRONG_LENGTH;
}

u2 processSelect(u1* apdu, u1* responseBuf, u2* responseLen) {
	u1 needsFcp = 0, flag = 0;
	FileDesc* file;
	u2 sw = FILE_NOT_FOUND;

	LOGD_FUNC();

	//printADF();
	
	switch ((getP2() >> 2) & 0x07) {
		case 1: 
			needsFcp = 1;
			break;
		case 0:
		case 3: 
			needsFcp = 0;
			break;
		default:
			return WRONG_PARAMS;
        }

	switch (getP1()) {
		case 0x00: // select MF
			if (getLc() == 0) {
				file = selectFId(MF);
			} else if (getLc() != 2) {
				return WRONG_PARAMS;
			} else {
				file = selectFId(getDataShort(apdu));
			}
			break;
		case 0x01: // selectChildDf
			file = selectChildDf(getCurDF(), getDataShort(apdu));
			break;
		case 0x03: // selectParentDf
			file = selectParentDf(getDataShort(apdu));
			break;
		case 0x04: // selectbyAID
			flag = (getP2() >> 5) & 0x03; // 2, terminate; 0, not
			file = selectbyAID(getData(), getLc(), flag);
			break;
		case 0x08: //selectByPathFromMf
			if (getLc() % 2 != 0) {
				return WRONG_DATA;
			}
			file = selectByPathFromMf(getData(), getLc());
			break;
		case 0x09:
			if (getLc() % 2 != 0) {
				return WRONG_DATA;
			}
			file = selectByPathFromCurrentDf(getData(), getLc());
			break;
		default:
			return WRONG_PARAMS;
	}

	if ( file != INVALID_FILE) {
		sw = NONE;

		if ((file->filetype == DF) || (file->filetype == MF) || (file->filetype == ADF)) {
			setCurDF(file);
			if (file->filetype == ADF) {
				setCurADF(file);
			}
			setCurEF(INVALID_FILE);
		} else if (file->filetype == EF) {
			setCurEF(file);
		}

		if (needsFcp != 0) {
			getFCP(file, responseBuf);
			*responseLen = getCurTLVLen() + 2;
		}
		else {
			*responseLen = 0;
		}
	}
	
	return sw;
}

u2 processStatus(u1* apdu, u1* responseBuf, u2* responseLen) {
	FileDesc* file;
	u2 sw = NONE;

	if (getP1() != 0x00 && getP1() != 0x01 && getP1() != 0x02) {
		return WRONG_PARAMS;
        }
        switch (getP2()) {
		case 0x00:
			file = getCurDF();
			getFCP(file, responseBuf);
			*responseLen = getCurTLVLen() + 2;
			return sw;
		case 0x01:
			file = getCurADF();
			if (file == INVALID_FILE) {
				return FILE_NOT_FOUND;
			}
			getADFName(file, responseBuf);
			*responseLen = getCurTLVLen() + 2;
			return sw;
		case 0x0C:
			return sw;
		default:
			return WRONG_PARAMS;
	}
}

u2 processVerifyPIN(u1* apdu, u1* responseBuf, u2* responseLen) {
	if (getP1() != 0 || getP2() != 0x01) {
		return WRONG_PARAMS;
	}
	*responseLen = 0;
	switch (getLc()) {
		case 0x00:
			return VERYFY_PIN_RETRY_LEFT_TIME;
		case 0x08:
			return PIN_BLOCKED;
		default:
			return WRONG_PARAMS;
	}
	return NONE;
}

u2 processUnBlockPIN(u1* apdu, u1* responseBuf, u2* responseLen) {
	if (getP1() != 0 || getP2() != 0x01) {
		return WRONG_PARAMS;
	}
	*responseLen = 0;
	switch (getLc()) {
		case 0x00:
			//return VERYFY_PIN_RETRY_LEFT_TIME;
		case 0x08:
			return UNBLOCK_PIN_RETRY_LEFT_TIME;
		default:
			return WRONG_PARAMS;
	}
	return NONE;
}

u2 processManageChannel(u1* apdu, u1* responseBuf, u2* responseLen) {
	u2 sw = NONE;
	u1 newChannel = INVALID_CHANNLE_ID;

	switch (getP1() & 0xFF) {
		case 0x00:
			if (getP2() != 0x00) {
				return WRONG_PARAMS;
			}
			newChannel = openChannel(getCurChannelID());
			if (newChannel == INVALID_CHANNLE_ID) {
				return LOGICAL_CHANNEL_NOT_SUPPORTED;
			} else {
				*responseBuf = newChannel;
				*responseLen = 1;
				return sw;
			}
		case 0x80:
			if (getP2() == 0) {
				return WRONG_PARAMS;
			}
			newChannel = closeChannel(getP2());
			if (newChannel != RETURN_OK) {
				return LOGICAL_CHANNEL_NOT_SUPPORTED;
			} else {
				return NONE;
			}
		default:
			return WRONG_PARAMS;
        }
}

u1 openChannel(u1 srcChnId) {
	u1 desChn = getAvaibleChannlNum();
	if (desChn == INVALID_CHANNLE_ID) {
		return INVALID_CHANNLE_ID;
	}
	if (srcChnId != CHANNEL_0) {
		copyChannelInfo(srcChnId, desChn);
	} else {
		openChannelID(desChn);
		setCurDFonChn(MFRef, desChn);
	}
	return desChn;
}

u1 closeChannel(u1 sChnId) {
	if (isChannelIdOpen(sChnId)) {
		closeChannelID(sChnId);
		return RETURN_OK;
	} else {
		return RETURN_ERR;
	}
}

u2 processReadBin(u1* apdu, u1* responseBuf, u2* responseLen) {
	FileDesc* file;
	u2 offset, len, sw = NONE;
	u2 size = getLe() & 0xFF;
	if ((getP1() & 0x80) == 0) {
		offset = getP1() << 8 | getP2();
		file = getCurEF();
	} else {
		offset = getP2();
		file = selectBySfi(getP1() & 0x1F);
	}
	if (file == INVALID_FILE) {
		return NO_FILE_SELECTED;
	}
	*responseLen = readBinary(file, offset, size, responseBuf, responseLen);
	return sw;
}

u2 readBinary(FileDesc* file, u2 offset, u2 size, u1* responseBuf, u2* responseLen) {
	if ((offset < 0) || (offset > 0x7FFF) ||  (offset > file->fileLen) ||(size < 0) || (size > 0x7FFF)) {
		return WRONG_LENGTH;
	}
        if (size == 0) {
		size = file->fileLen - offset;
		if (size >= 0x100) {
			size = 0x100;
		}
	}
	COS_MEMCPY(responseBuf, file->data + offset, size);
	return size;
}

u2 processUpdateBin(u1* apdu, u1* responseBuf, u2* responseLen) {
	FileDesc* file;
	u2 offset, len, sw = NONE;
	u2 size = getLc() & 0xFF;
	if ((getP1() & 0x80) == 0) {
		offset = getP1() << 8 | getP2();
		file = getCurEF();
	} else {
		offset = getP2();
		file = selectBySfi(getP1() & 0x1F);
	}
	if (file == INVALID_FILE) {
		return NO_FILE_SELECTED;
	}
	updateBinary(file, offset, getData(), getLc());
	*responseLen = 0;
	return sw;
}

u2 updateBinary(FileDesc* file, u2 offset, u1* data, u1 len) {
	u2 sw = NONE;
	if ((offset < 0) || (offset > 0x7FFF) || (offset + len > file->fileLen)) {
		return WRONG_LENGTH;
	}
	COS_MEMCPY(file->data + offset, data, len);
	return sw;
}

u2 processReadRecord(u1* apdu, u1* responseBuf, u2* responseLen) {
	u1 number = getP1() & 0xFF;
	u1 sfi = (getP2() >> 3) & 0x1F;
	FileDesc* file;

	if (sfi == 0) {
		file = getCurEF();
	} else {
		file = selectBySfi(sfi);
	}

	if (file == INVALID_FILE) {
		return NO_FILE_SELECTED;
	}

        switch (getP2() & 0x07) {
		case 2:
			readNextRecord(file, responseBuf);
			break;
		case 3:
			readPreviousRecord(file, responseBuf);
			break;
		case 4:
			readRecordAbs(file, number, responseBuf);
			break;
		default:
			return WRONG_PARAMS;
        }
	*responseLen = file->recordLen;
	return NONE;
}

void readNextRecord(FileDesc* file, u1* responseBuf) {
	if (file->recordPointer > file->recordCnt) {
		return;
	}
	file->recordPointer ++;
	if (file->recordPointer ==  file->recordCnt) {
		 file->recordPointer = 1;
	}
	readRecordAbs(file, 0, responseBuf);
}

void readPreviousRecord(FileDesc* file, u1* responseBuf) {
	if (file->recordPointer < 0) {
		return;
	}
	file->recordPointer --;
	if (file->recordPointer ==  0) {
		 file->recordPointer = file->recordCnt;
	}
	readRecordAbs(file, 0, responseBuf);
}

void readRecordAbs(FileDesc* file, u1 recordNum, u1* responseBuf) {
	if (file->eftype != LINEAR) {
		return;
	}
	if ((recordNum < 0) || (recordNum > file->recordCnt)) {
		return;
	}

        if (recordNum == 0) {
		recordNum = file->recordPointer;
        }
	recordNum --;
	COS_MEMCPY(responseBuf, file->data + file->recordLen * recordNum, file->recordLen);
}

u2 processUpdateRecord(u1* apdu, u1* responseBuf, u2* responseLen) {
	u1 number = getP1() & 0xFF;
	u1 sfi = (getP2() >> 3) & 0x1F;
	FileDesc* file;
	if (sfi == 0) {
		file = getCurEF();
	} else {
		file = selectBySfi(sfi);
	}

        if (file == INVALID_FILE) {
		return NO_FILE_SELECTED;
        }
        switch (getP2() & 0x07) {
		case 2:
			updateNextRecord(file, getData());
			break;
		case 3:
			updatePreviousRecord(file, getData());
			break;
		case 4:
			updateRecordAbs(file, number, getData());
			break;
		default:
			return WRONG_PARAMS;
        }
        *responseLen = 0;
        return NONE;
}

void updateNextRecord(FileDesc* file, u1* apduData) {
	if (file->recordPointer > file->recordCnt) {
		return;
	}
	file->recordPointer ++;
	if (file->recordPointer ==  file->recordCnt) {
		 file->recordPointer = 1;
	}
	updateRecordAbs(file, 0, apduData);
}

void updatePreviousRecord(FileDesc* file, u1* apduData) {
	if (file->recordPointer < 0) {
		return;
	}
	file->recordPointer --;
	if (file->recordPointer ==  0) {
		 file->recordPointer = file->recordCnt;
	}
	updateRecordAbs(file, 0, apduData);
}

void updateRecordAbs(FileDesc* file, u1 recordNum, u1* apduData) {
	if (file->eftype != LINEAR) {
		return;
	}
	if ((recordNum < 0) || (recordNum > file->recordCnt)) {
		return;
	}

        if (recordNum == 0) {
		recordNum = file->recordPointer;
        }
	recordNum --;
	COS_MEMCPY(file->data + file->recordLen * recordNum, apduData, file->recordLen);
}

u2 processAuth(u1* apdu, u1* responseBuf, u2* responseLen) {
	u1 rand[16];
	u1 authToken[16];
	RijndaelKeySchedule(AuthKi);
	COS_MEMCPY(rand, apdu + OFFSET_DATA + 1, 16);
	COS_MEMCPY(authToken, apdu + OFFSET_DATA + 18, 16);	
	return Auth(rand, authToken, responseBuf, responseLen);
}

FileDesc* selectMF() {
	return MFRef;
}

FileDesc* selectBySfi(u1 sfi) {
	return selectChildSfi(getCurDF(), sfi);
}

FileDesc* selectFId(u2 fid) {
	FileDesc* file;

	LOGD_FUNC();

#if DEBUG_LEVLE > 2	
	LOGD("selecting fid [%02X]\n", fid);
#endif

	if (fid == 0x3F00) {
		return selectMF();
	}
	// 7FFF, ADF
	if (fid == 0x7FFF) {
		return getCurADF();
	}
	// child file
	file = selectChild(getCurDF(), fid);
	if (file != INVALID_FILE) {
		return file;
	}
	//parent file
	file = selectParentDf(fid);
	if (file != INVALID_FILE) {
		return file;
	}
	//brother file
	file = selectChild(getCurDF()->parent, fid);
	if (file != INVALID_FILE) {
		return file;
	}
	return file;
}

FileDesc* selectChild(FileDesc* df, u2 fid) {
	FileDesc* file;
	LOGD_FUNC();
	
	file = selectChildDf(df, fid);
	if (file == INVALID_FILE) {
		file = selectChildEf(df, fid);
	}
	return file;
}

FileDesc* selectChildSfi(FileDesc* df, u1 sfi) {
	FileDesc* file;
	LOGD_FUNC();
	
	file = selectChildDfSfi(df, sfi);
	if (file == INVALID_FILE) {
		file = selectChildEfSfi(df, sfi);
	}
	return file;
}

FileDesc* selectChildDf(FileDesc* df, u2 fid) {
	FileDesc* file = INVALID_FILE;
	FileList* curDF = df->childDf;

	LOGD_FUNC();	
	while (curDF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		LOGD("ChildDF[%02X]\n", curDF->me->fid);
#endif		
		if (curDF->me->fid == fid) {
			file = curDF->me;
			break;
		}
		curDF = curDF->next;
	}
	return file;
}

FileDesc* selectChildDfSfi(FileDesc* df, u1 sfi) {
	FileDesc* file = INVALID_FILE;
	FileList* curDF = df->childDf;

	LOGD_FUNC();
	
	while (curDF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		LOGD("ChildDF[%02X], sfi[%02X]\n", curDF->me->fid, curDF->me->sfi);
#endif		
		if (curDF->me->sfi == sfi) {
			file = curDF->me;
			break;
		}
		curDF = curDF->next;
	}
	return file;
}

FileDesc* selectChildEf(FileDesc* df, u2 fid) {
	FileDesc* file = INVALID_FILE;
	FileList* curEF = df->childEf;

	LOGD_FUNC();
	
	while (curEF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		LOGD("ChildEF[%02X]\n", curEF->me->fid);
#endif
		if (curEF->me->fid == fid) {
			file = curEF->me;
			break;
		}
		curEF = curEF->next;
	}
	return file;
}

FileDesc* selectChildEfSfi(FileDesc* df, u1 sfi) {
	FileDesc* file = INVALID_FILE;
	FileList* curEF = df->childEf;

	LOGD_FUNC();
	
	while (curEF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		LOGD("ChildEF[%02X], sfi[%02X]\n", curEF->me->fid, curEF->me->sfi);
#endif
		if (curEF->me->sfi == sfi) {
			file = curEF->me;
			break;
		}
		curEF = curEF->next;
	}
	return file;
}

FileDesc* selectParentDf(u2 fid) {
	FileDesc* file = getCurDF()->parent;
	
	LOGD_FUNC();
	
	if ((file != INVALID_FILE) && (file->fid == fid)) {
		return file;
	}
	return INVALID_FILE;
}

FileDesc* selectbyAID(u1* aidBuf, u1 len, u1 terminal) {
	FileDesc* file;
	
	LOGD_FUNC();
	
	file = getAdfFileDes(aidBuf, len);
	if (file != INVALID_FILE) {
		return file;
	}
	return INVALID_FILE;
}

FileDesc* selectByPathFromMf(u1* fidPath, u1 len) {
	LOGD_FUNC();
	return selectByPath(getMF(), fidPath, len);
}

FileDesc* selectByPathFromCurrentDf(u1* fidPath, u1 len) {
	LOGD_FUNC();
	return selectByPath(getCurDF(), fidPath, len);
}

u2 getShort(u1* buf) {
	return (buf[0] << 8) + buf[1];
}
FileDesc* selectByPath(FileDesc* df, u1* fidPath, u1 len) {
	FileDesc* file = df;
	u1 step = len / 2;
	u2 fid;
	u1* pfid = fidPath;

	LOGD_FUNC();
#if DEBUG_LEVLE > 2	
	LOGD("selectByPath DF[%02X], len[%02d], step[%02d]\n", df->fid, len, step);
#endif

	while (step --) {
		//LOGD("step[%02d]\n", step);
		fid = getShort(pfid);
#if DEBUG_LEVLE > 2	
		LOGD("selectByPath fid[%02X]\n", fid);
#endif
		if (fid == 0x7FFF) {
			file = getCurADF();
			pfid += 2;
			//step --;
			continue;
		}
		
		file = selectChild(file, fid);
		if (file == INVALID_FILE) {
			return INVALID_FILE;
		}
		pfid += 2;
	}
	
	return file;
}

