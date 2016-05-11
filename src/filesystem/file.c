#include "../inc/types.h"

void getADFName(FileDesc* file, u1* resBuf) {
	setCurTLVTag(FILE_CONTROL_PARAMETERS_TAG);
	setCurTLVLen(0);
	setCurTLVOff(2);
	getDFname(file, resBuf);
	resBuf[0] = getCurTLVTag();
	resBuf[1] = getCurTLVLen();
}

void getFCP(FileDesc* file, u1* resBuf) {
	u1 isEF = isFileEF(file);
#if DEBUG_LEVLE >= 2
	if (file != INVALID_FILE) {
		LOGD("getFCP fid[%04X]\n", file->fid);
	} else {
		LOGD("getFCP INVALID_FILE\n");
		return;
	}
#endif	
	setCurTLVTag(FILE_CONTROL_PARAMETERS_TAG);

	setCurTLVLen(0);
	setCurTLVOff(2);
	getFileDescriptor(file, resBuf);
	getFileIdentifier(file, resBuf);
	if (file->filetype == ADF) {
		getDFname(file, resBuf);
	}
	getProprietaryInformation(file, resBuf);
	getLifeCycleStatusInteger(file, resBuf);
	getSecurityattributes(file, resBuf);
	if (isEF) {
		getFilesize(file, resBuf);
		getTotalfilesize(file, resBuf);
		getShortFileIdentifier(file, resBuf);
	} else {
		getPINStatusTemplateDO(file, resBuf);
		getTotalfilesize(file, resBuf);
	}

	resBuf[0] = getCurTLVTag();
	resBuf[1] = getCurTLVLen();
}

void getFileDescriptor(FileDesc* file, u1* resBuf) {
	u1 fileDescByte = 0;
	u1 bytes[5] = {0, 0x21};
	u1 isEF = isFileEF(file);

	if (file->shareble == SHAREABLE) {
		fileDescByte |= 1 << 6;
	}
	if (isEF) {
		//fileDescByte |= 1 << 3; // internal file set to 1
		switch (file->eftype) {
			case LINEAR:
				fileDescByte |= 1 << 1;
				break;
			case TRANSPARENT:
				fileDescByte |= 1 << 0;
				break;
			case CIRCLE:
				fileDescByte |= 3 << 1;
				break;
			case BERSTUCT:
				fileDescByte = 0x39;
				break;
		}
	} else {
		fileDescByte |= 7 << 3;
	}

	bytes[0] = fileDescByte;
	if (isEF && ((file->eftype == CIRCLE) || (file->eftype == LINEAR))) {
		bytes[2] = file->recordLen >> 8;
		bytes[3] = file->recordLen & 0xFF;
		bytes[4] = file->recordCnt;
		appendTLBufferV(resBuf, FILE_DESCRIPTOR_TAG, bytes, 0, 5);
	} else {
		appendTLBufferV(resBuf, FILE_DESCRIPTOR_TAG, bytes, 0, 2);
	}
}

void getFileIdentifier(FileDesc* file, u1* resBuf) {
	appendTLShortV(resBuf, FILE_IDENTIFIER_TAG, file->fid);
}

void getDFname(FileDesc* file, u1* resBuf) {
	u1 len = 0;
	u1* buf = getAdfAID(file, &len);
	if (len > 0) {
		appendTLBufferV(resBuf, DF_NAME_TAG, buf, 0, len);
	}
}

void getProprietaryInformation(FileDesc* file, u1* resBuf) {
	u1 buf[3] = {0x80, 0x01, 0x71};
	appendTLBufferV(resBuf, PROPRIETARY_INFORMATION_TAG, buf, 0, 3);
}

void getLifeCycleStatusInteger(FileDesc* file, u1* resBuf) {
	appendTLByteV(resBuf, LIFE_CYCLE_STATUS_INTEGER_TAG, 5);
}

void getSecurityattributes(FileDesc* file, u1* resBuf) {
	u1 buf[3];
	buf[0] = file->arrRef.arrFid >> 8;
	buf[1] = file->arrRef.arrFid & 0xFF;
	buf[2] = file->arrRef.arrRecordNum;
	appendTLBufferV(resBuf, SECURITY_ATTRIBUTES_TAG, buf, 0, 3);
}

void getFilesize(FileDesc* file, u1* resBuf) {
	appendTLShortV(resBuf, FILE_SIZE_TAG, file->fileLen);
}

void getTotalfilesize(FileDesc* file, u1* resBuf) {
	
}

void getShortFileIdentifier(FileDesc* file, u1* resBuf) {
	appendTLByteV(resBuf, SHORT_FILE_IDENTIFIER_TAG, file->sfi);
}

void getPINStatusTemplateDO(FileDesc* file, u1* resBuf) {
	u1 buf[6] = {0x90, 0x01, 0x00, 0x83, 0x01, 0x01};
	appendTLBufferV(resBuf, PIN_STATUS_TEMPLATE_DO_TAG, buf, 0, 6);
}

u1 isFileEF(FileDesc* file) {
	return file->filetype == EF;
}

void addChildEFs(FileDesc* parent, u2* fids, u2 len) {
	LOGD_FUNC();
#if DEBUG_LEVLE > 2	
	LOGD("fid num: %d\n", len);
#endif	
	buildEFs(parent,  fids, len);
}

void addChildFile(FileDesc* parent, FileDesc* file, u1 fileType) {
	FileList* p, *pNew, **pfileList;
	LOGD_FUNC();

#if DEBUG_LEVLE > 2		
		LOGD("addChildFile: [0x%2X]======\n", file->fid);
#endif		

	file->parent = parent;
	
	if (fileType == EF) {
		pfileList = &(parent->childEf);
	} else if (fileType == DF) {
		pfileList = &(parent->childDf);
	}
	
	if (*pfileList == INVALID_FILE_LIST) {
		PRINT_STR("pfileList is INVALID_FILE_LIST");
		pNew = COS_MALLOC(sizeof(FileList));
#if DEBUG_LEVLE > 2			
		LOGD("COS_MALLOC addr[0x%4X]======\n", (u4)pNew);
#endif		
		COS_MEMSET(pNew, 0, sizeof(FileList));
		pNew->me = file;
		pNew->next = INVALID_FILE_LIST;
		*pfileList = pNew;
	} else {
		PRINT_STR("pfileList is NOT INVALID_FILE_LIST");
		p = *pfileList;
#if DEBUG_LEVLE > 2	
		LOGD("pfileList addr[0x%4X], fid[0x%02X]======\n", (u4)p, p->me->fid);
#endif
		while (p->next!= INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2		
			LOGD("pfileList addr next[0x%4X], fid[0x%02X]======\n", (u4)(p->next), p->me->fid);
#endif
			p = p->next;
		}
		pNew = COS_MALLOC(sizeof(FileList));
#if DEBUG_LEVLE > 2		
		LOGD("COS_MALLOC addr[0x%4X]======\n", (u4)pNew);
#endif
		COS_MEMSET(pNew, 0, sizeof(FileList));
		pNew->me = file;
		pNew->next = INVALID_FILE_LIST;
		p->next = pNew;
	}
}

void initADF() {
	u1 i = 0;
	while (i < AID_COUNT) {
		aidFile[i].aid = (u1*)NULL;
		aidFile[i].aidLen = 0;
		aidFile[i].file = INVALID_FILE;
		i ++;
	}
}

u1* getAdfAID(FileDesc* file, u1* aidLen) {
	u1 i = 0;
	while (i < sizeof(aidFile)) {
		if (aidFile[i].file != INVALID_FILE) {
			printf("aid fid[%02X]\n", aidFile[i].file->fid);
		}
		if (file == aidFile[i].file) {
			*aidLen = aidFile[i].aidLen;
			return aidFile[i].aid;
		}
		i ++;
	}
	return NULL;
}

FileDesc* getAdfFileDes(u1* aid, u1 aidLen) {
	FileDesc* file = INVALID_FILE;
	u1 index = 0, i = 0, len = aidLen;

	LOGD_FUNC();

#if DEBUG_LEVLE > 2	
	LOGD("len[%02X], aid: ", len);
	while (len --) {
		LOGD("%02X",  *(aid + (i ++)));
	}
	LOGD("\n");
	i = 0;
#endif

	do{
#if DEBUG_LEVLE > 2		
		len = aidFile[index].aidLen;
		if (aidFile[index].file != INVALID_FILE) {
			LOGD("len[%02X], index[%d], fid[%02X], aidMember: ", len, index,  aidFile[index].file->fid);
		} else {
			LOGD("len[%02X], index[%d], aidMember: ", len, index);
		}
		if (len != 0) {
			i = 0;
			while (len --) {
				LOGD("%02X",  *(aidFile[index].aid + (i ++)));
			}
			i = 0;
		}
		LOGD("\n");
#endif
		if ((aidFile[index].aidLen != 0) &&
			(aidFile[index].aidLen == aidLen) && 
			(COS_MEMCMP(aidFile[index].aid, aid, aidLen) == 0) &&
			(aidFile[index].file != INVALID_FILE)) {
			file = aidFile[index].file;
			break;
		}
	} while (index ++ < (AID_COUNT - 1));
#if DEBUG_LEVLE >= 2
	if (file != INVALID_FILE) {
		LOGD("ADF found: fid[%02X]\n", file->fid);
	}
#endif
	PRINT_FUNC_DONE();
	return file;
}

void addAdfAid(u1 * aid, FileDesc* file, u1 index) {
	u1* buf, len;
	buf = aidString2Buffer(aid, &len);
	aidFile[index].aid = buf;
	aidFile[index].aidLen = len;
	aidFile[index].file = file;

	LOGD_FUNC();
#if DEBUG_LEVLE >= 2
	LOGD("aid[%s], len[%02X], index[%d], fid[%02X]\n", aid, len, index, file->fid);
#endif
}

void configureProfile(	u1* imsi,
						u1* ki,
						u1* opc,
						u1* iccid,
						u1* acc,
						u1* spn,
						u1* hplmn,
						u1* ehplmn,
						u1* loci,
						u1* psloci,
						u1* fplmn ) {
	configIMSI(imsi);
	configKI(ki);
	configOPC(opc);
	configICCID(iccid);
	configACC(acc);
	configSPN(spn);
	configHPLMN(hplmn);
	configEHPLMN(ehplmn);
	configLOCI(loci);
	configPSLOCI(psloci);
	configFPLMN(fplmn);
}

void configIMSI(u1* imsi) {
	u1 buf[18], len = COS_STRLEN(imsi);
	if (len == 0) {
		return;
	}
	COS_MEMSET(buf, 'F', sizeof(buf));
	buf[0] = (len + 1) / 2 + '0';
	buf[1] = '0';
	buf[2] = (len % 2 == 0) ? '1' : '9';
	COS_MEMCPY(buf + 3, imsi, len);
	charString2ByteString(buf, profile->imsi->data, 0, STRING_NOSPACE_WAPE);
	printFileContent(profile->imsi);
	return;
}

void configKI(u1* ki) {
	u1 len = COS_STRLEN(ki);
	if (len != 0x20) {
		return;
	}
	charString2ByteString(ki, profile->ki->data, 0, STRING_NOSPACE_NOWAPE);
	printFileContent(profile->ki);
	charString2ByteString(ki, AuthKi, 0, STRING_NOSPACE_NOWAPE);
}

void configOPC(u1* opc) {
	u1 len = COS_STRLEN(opc);
	if (len != 0x20) {
		return;
	}
	charString2ByteString(opc, profile->ki->data + LENGTH_KI, 0, STRING_NOSPACE_NOWAPE);
	charString2ByteString(opc, AuthOpc, 0, STRING_NOSPACE_NOWAPE);
}

void configICCID(u1* iccid) {
	u1 buf[20], len = COS_STRLEN(iccid);
	if (len == 0) {
		return;
	}
	COS_MEMSET(buf, 'F', sizeof(buf));
	COS_MEMCPY(buf, iccid, len);
	charString2ByteString(buf, profile->iccid->data, 0, STRING_NOSPACE_WAPE);
	printFileContent(profile->iccid);
}

void configACC(u1* acc) {
	u1 len = COS_STRLEN(acc);
	if (len == 0) {
		return;
	}
	charString2ByteString(acc, profile->acc->data, 0, STRING_NOSPACE_NOWAPE);
	printFileContent(profile->acc);
}

u1 isASCII(u1* buf) {
	u1 i, length = COS_STRLEN(buf), ch;
	for (i = 0; i < length; i ++) {
		ch = *(buf + i);
		if (ch > 0x7F) {
			return RETURN_ERR;
		}
	}
	return RETURN_OK;
}
void configSPN(u1* spn) {
	u1 buf[17], len = COS_STRLEN(spn);

	if (len == 0) {
		return;
	}
	COS_MEMSET(buf, 0xFF, sizeof(buf));

	buf[0] = 00;
	if (isASCII(spn) == RETURN_OK) {
		if (len > 16) {
			len = 16;
		}
		COS_MEMCPY(buf + 1, spn, len);
	} else {
		if (len > 14) {
			len = 14;
		}
		buf[1] = 0x80;
		COS_MEMCPY(buf + 2, spn, len);
	}
	COS_MEMCPY(profile->spn->data, buf, 17);
	printFileContent(profile->spn);
}

void configHPLMN(u1* hplmn) {
	u1 len = COS_STRLEN(hplmn);
	if (len == 0) {
		return;
	}
	if ((len != 5) && (len != 6)) {
		return;
	}
	profile->hplmn->data[3] = len -3;
	printFileContent(profile->hplmn);
}

void configEHPLMN(u1* ehplmn) {
	u1 len = COS_STRLEN(ehplmn);
	if (len == 0) {
		return;
	}
	convetPLMNs(ehplmn, profile->ehplmn->data, PMLNS_SPLITER);
	printFileContent(profile->ehplmn);
}

void configLOCI(u1* rplmn) {
	u1 len = COS_STRLEN(rplmn);
	u1 buf[7];	
	if (len == 0) {
		return;
	}
	COS_MEMCPY(buf, rplmn, len);
	buf[len] = PMLNS_SPLITER;
	convetPLMNs(rplmn, profile->psloci->data+4, PMLNS_SPLITER);
	profile->psloci->data[10] = 0;
	printFileContent(profile->loci);
}

void configPSLOCI(u1* rplmn) {
	u1 len = COS_STRLEN(rplmn);
	u1 buf[7];	
	if (len == 0) {
		return;
	}
	COS_MEMCPY(buf, rplmn, len);
	buf[len] = PMLNS_SPLITER;
	convetPLMNs(rplmn, profile->psloci->data + 7, PMLNS_SPLITER);
	profile->psloci->data[13] = 0;
	printFileContent(profile->psloci);
}

void configFPLMN(u1* fplmn) {
	u1 len = COS_STRLEN(fplmn);
	if (len == 0) {
		return;
	}
	convetPLMNs(fplmn, profile->fplmn->data, PMLNS_SPLITER);
	printFileContent(profile->fplmn);
}

