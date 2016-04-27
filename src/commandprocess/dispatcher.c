#include <stdio.h>
#include <stdlib.h>
#include "../filesystem/filetype.h"
#include "../filesystem/fileSystem.h"
#include "../inc/types.h"

FileDesc* MFRef;
FileDesc* AdfUsimRef;

TLV* tlv;

void insertCard(u1* iccid, u1* imsi, u1* ki) {
	PRINT_FUNC_NAME();

	COS_MEMSET(aidFile, 0, sizeof(aidFile));
	MFRef = buildFileSystem();
	initChannel();

	tlv = COS_MALLOC(sizeof(TLV));
}

void showFS() {
	showFileSystem(MFRef);
}



u1 getCLS(u1* apdu) {
	return *(apdu + OFFSET_CLS);
}
u1 getINS(u1* apdu) {
	return *(apdu + OFFSET_INS);
}
u1 getP1(u1* apdu) {
	return *(apdu + OFFSET_P1);
}
u1 getP2(u1* apdu) {
	return *(apdu + OFFSET_P2);
}
u1 getP3(u1* apdu) {
	return *(apdu + OFFSET_P3);
}
u1* getData(u1* apdu) {
	return apdu + OFFSET_DATA;
}
u2 getDataByte(u1* apduData){
	return *(apduData);
}
u2 getDataShort(u1* apduData){
	return ((*(apduData + OFFSET_DATA) << 8) & 0xFF00) | (*(apduData + OFFSET_DATA + 1) & 0xFF);
}

short dispatcher(u1* apdu, u1* responseBuf, u2* responseLen) {
	u1 ins = getINS(apdu);

	PRINT_FUNC_NAME();
	printAPDU(apdu);
	switch(ins) {
		case INS_SELECT:
			return processSelect(apdu, responseBuf, responseLen);
		case INS_STATUS:
			return processStatus(apdu, responseBuf, responseLen);
		case INS_VERIFY_PIN:
			return processVerifyPIN(apdu, responseBuf, responseLen);
		case INS_UNBLOCK_PIN:
			return processUnBlockPIN(apdu, responseBuf, responseLen);
		case INS_MANAGE_CHANNEL:
			return processManageChannel(apdu, responseBuf, responseLen);
		case INS_READ_BINARY:
			return processReadBin(apdu, responseBuf, responseLen);
		case INS_UPDATE_BINARY:
			return processUpdateBin(apdu, responseBuf, responseLen);
		case INS_READ_RECORD:
			return processReadRecord(apdu, responseBuf, responseLen);
		case INS_UPDATE_RECORD:
			return processUpdateRecord(apdu, responseBuf, responseLen);
		case INS_AUTHENTICATE:
			return processAuth(apdu, responseBuf, responseLen);
		default:
			PRINT_STR("Unkown command");
			return INVALID_INS;
			break;
	}
}

void printAPDU(u1* apdu) {
	u2 i = 0, p3 = getP3(apdu);
	
	printf("APDU< %02X%02X%02X%02X%02X", 
		getCLS(apdu),
		getINS(apdu),
		getP1(apdu),
		getP2(apdu),
		getP3(apdu)
		);

	while(p3 --) {
		printf("%02X",  *(apdu + OFFSET_DATA + (i ++)));
	}
	printf(" >\n");
}

short processSelect(u1* apdu, u1* responseBuf, u2* responseLen){
	u1 needsFcp = 0, flag = 0;
	FileDesc* file;
	u2 sw = FILE_NOT_FOUND;

	PRINT_FUNC_NAME();

	//printADF();

	if(getCurEF() != INVALID_FILE) {
		printf("CurEF: %02X\n", getCurEF()->fid);
	}
	if(getCurDF() != INVALID_FILE) {
		printf("CurDF: %02X\n", getCurDF()->fid);
	}
	if(getCurADF() != INVALID_FILE) {
		printf("CurAD: %02X\n", getCurADF()->fid);
	}

	switch ((getP2(apdu) >> 2) & 0x07) {
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

	switch (getP1(apdu)) {
		case 0x00: // select MF
			if(getP3(apdu) == 0) {
				file = selectFId(MF);
			} else if(getP3(apdu) != 2) {
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
			flag = (getP2(apdu) >> 5) & 0x03; // 2, terminate; 0, not
			file = selectbyAID(getData(apdu), getP3(apdu), flag);
			break;
		case 0x08: //selectByPathFromMf
			if(getP3(apdu) % 2 != 0) {
				return WRONG_DATA;
			}
			file = selectByPathFromMf(getData(apdu), getP3(apdu));
			break;
		case 0x09:
			if(getP3(apdu) % 2 != 0) {
				return WRONG_DATA;
			}
			file = selectByPathFromCurrentDf(getData(apdu), getP3(apdu));
			break;
		default:
			return WRONG_PARAMS;
	}

	if( file != INVALID_FILE) {
		sw = NONE;

		if((file->filetype == DF) || (file->filetype == MF) || (file->filetype == ADF)) {
			setCurDF(file);
			if(file->filetype == ADF) {
				setCurADF(file);
			}
			setCurEF(INVALID_FILE);
		}
		else if(file->filetype == EF) {
			setCurEF(file);
		}
	

		if(needsFcp != 0) {
			/*
			needsFcp = 0;
			responseBuf[needsFcp ++] = needsFcp;
			responseBuf[needsFcp ++] = needsFcp;
			responseBuf[needsFcp ++] = needsFcp;
			responseBuf[needsFcp ++] = needsFcp;
			responseBuf[needsFcp ++] = needsFcp;
			responseBuf[needsFcp ++] = needsFcp;
			*responseLen = needsFcp;
			*/
			getFCP(file, responseBuf);
			*responseLen = getCurTLVLen() + 2;
		}
		else {
			*responseLen = 0;
		}
		
	}
	
	return sw;
}
short processStatus(u1* apdu, u1* responseBuf, u2* responseLen){
	FileDesc* file;
	u2 sw = NONE;
	
	if (getP1(apdu) != 0x00 && getP1(apdu) != 0x01 && getP1(apdu) != 0x02) {
		return WRONG_PARAMS;
        }
        switch (getP2(apdu)) {
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

short processVerifyPIN(u1* apdu, u1* responseBuf, u2* responseLen){
	if(getP1(apdu) != 0 || getP2(apdu) != 0x01) {
		return WRONG_PARAMS;
	}
	*responseLen = 0;
	switch (getP3(apdu)) {
		case 0x00:
			return VERYFY_PIN_RETRY_LEFT_TIME;
		case 0x08:
			return PIN_BLOCKED;
		default:
			return WRONG_PARAMS;
	}
	return NONE;
}

short processUnBlockPIN(u1* apdu, u1* responseBuf, u2* responseLen){
	if(getP1(apdu) != 0 || getP2(apdu) != 0x01) {
		return WRONG_PARAMS;
	}
	*responseLen = 0;
	switch (getP3(apdu)) {
		case 0x00:
			return VERYFY_PIN_RETRY_LEFT_TIME;
		case 0x08:
			return UNBLOCK_PIN_RETRY_LEFT_TIME;
		default:
			return WRONG_PARAMS;
	}
	return NONE;
}

short processManageChannel(u1* apdu, u1* responseBuf, u2* responseLen){
	
}
short processReadBin(u1* apdu, u1* responseBuf, u2* responseLen){
	FileDesc* file;
	u2 offset, len, sw = NONE;
	u2 size = getP3(apdu) & 0xFF;
	if((getP1(apdu) & 0x80) == 0) {
		offset = getP1(apdu) << 8 | getP2(apdu);
		file = getCurEF();
	} else {
		offset = getP2(apdu);
		file = selectBySfi(getP1(apdu) & 0x1F);
	}
	if(file == INVALID_FILE) {
		return NO_FILE_SELECTED;
	}
	*responseLen = readBinary(file, offset, size, responseBuf, responseLen);
	return sw;
}

short readBinary(FileDesc* file, u2 offset, u2 size, u1* responseBuf, u2* responseLen) {
	if((offset < 0) || (offset > 0x7FFF) ||  (offset > file->fileLen) ||(size < 0) || (size > 0x7FFF)) {
		return WRONG_LENGTH;
	}
        if(size == 0) {
		size = file->fileLen - offset;
		if(size >= 0x100) {
			size = 0x100;
		}
	}
	COS_MEMCPY(responseBuf, file->data + offset, size);
	return size;
}

short processUpdateBin(u1* apdu, u1* responseBuf, u2* responseLen){
	FileDesc* file;
	u2 offset, len, sw = NONE;
	u2 size = getP3(apdu) & 0xFF;
	if((getP1(apdu) & 0x80) == 0) {
		offset = getP1(apdu) << 8 | getP2(apdu);
		file = getCurEF();
	} else {
		offset = getP2(apdu);
		file = selectBySfi(getP1(apdu) & 0x1F);
	}
	if(file == INVALID_FILE) {
		return NO_FILE_SELECTED;
	}
	updateBinary(file, offset, getData(apdu), getP3(apdu));
	*responseLen = 0;
	return sw;
}

short updateBinary(FileDesc* file, u2 offset, u1* data, u1 len) {
	u2 sw = NONE;
	if((offset < 0) || (offset > 0x7FFF) || (offset + len > file->fileLen)) {
		return WRONG_LENGTH;
	}
	COS_MEMCPY(file->data + offset, data, len);
	return sw;
}

short processReadRecord(u1* apdu, u1* responseBuf, u2* responseLen){
	u1 number = getP1(apdu) & 0xFF;
	u1 sfi = (getP2(apdu) >> 3) & 0x1F;
	FileDesc* file;

	if(sfi == 0) {
		file = getCurEF();
	} else {
		file = selectBySfi(sfi);
	}

	if(file == INVALID_FILE) {
		return NO_FILE_SELECTED;
	}

        switch (getP2(apdu) & 0x07) {
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
	if(file->recordPointer > file->recordCnt) {
		return;
	}
	file->recordPointer ++;
	if(file->recordPointer ==  file->recordCnt) {
		 file->recordPointer = 1;
	}
	readRecordAbs(file, 0, responseBuf);
}

void readPreviousRecord(FileDesc* file, u1* responseBuf) {
	if(file->recordPointer < 0) {
		return;
	}
	file->recordPointer --;
	if(file->recordPointer ==  0) {
		 file->recordPointer = file->recordCnt;
	}
	readRecordAbs(file, 0, responseBuf);
}

void readRecordAbs(FileDesc* file, u1 recordNum, u1* responseBuf) {
	if(file->eftype != LINEAR) {
		return;
	}
	if((recordNum < 0) || (recordNum > file->recordCnt)) {
		return;
	}

        if (recordNum == 0) {
		recordNum = file->recordPointer;
        }
	recordNum --;
	COS_MEMCPY(responseBuf, file->data + file->recordLen * recordNum, file->recordLen);
}



short processUpdateRecord(u1* apdu, u1* responseBuf, u2* responseLen){
	u1 number = getP1(apdu) & 0xFF;
	u1 sfi = (getP2(apdu) >> 3) & 0x1F;
	FileDesc* file;
	if (sfi == 0) {
		file = getCurEF();
	} else {
		file = selectBySfi(sfi);
	}

        if (file == INVALID_FILE) {
		return NO_FILE_SELECTED;
        }
        switch (getP2(apdu) & 0x07) {
		case 2:
			updateNextRecord(file, getData(apdu));
			break;
		case 3:
			updatePreviousRecord(file, getData(apdu));
			break;
		case 4:
			updateRecordAbs(file, number, getData(apdu));
			break;
		default:
			return WRONG_PARAMS;
        }
        *responseLen = 0;
        return NONE;
}

void updateNextRecord(FileDesc* file, u1* apduData) {
	if(file->recordPointer > file->recordCnt) {
		return;
	}
	file->recordPointer ++;
	if(file->recordPointer ==  file->recordCnt) {
		 file->recordPointer = 1;
	}
	updateRecordAbs(file, 0, apduData);
}

void updatePreviousRecord(FileDesc* file, u1* apduData) {
	if(file->recordPointer < 0) {
		return;
	}
	file->recordPointer --;
	if(file->recordPointer ==  0) {
		 file->recordPointer = file->recordCnt;
	}
	updateRecordAbs(file, 0, apduData);
}

void updateRecordAbs(FileDesc* file, u1 recordNum, u1* apduData) {
	if(file->eftype != LINEAR) {
		return;
	}
	if((recordNum < 0) || (recordNum > file->recordCnt)) {
		return;
	}

        if (recordNum == 0) {
		recordNum = file->recordPointer;
        }
	recordNum --;
	COS_MEMCPY(file->data + file->recordLen * recordNum, apduData, file->recordLen);
}

short processAuth(u1* apdu, u1* responseBuf, u2* responseLen){
}


FileDesc* selectMF() {
	return MFRef;
}

FileDesc* selectBySfi(u1 sfi) {
	return selectChildSfi(getCurDF(), sfi);
}

FileDesc* selectFId(u2 fid) {
	FileDesc* file;

	PRINT_FUNC_NAME();

#if DEBUG_LEVLE > 2	
	printf("selecting fid [%02X]\n", fid);
#endif

	if (fid == 0x3F00) {
		return selectMF();
	}
	// 7FFF, ADF
	if(fid == 0x7FFF) {
		return getCurADF();
	}
	// child file
	file = selectChild(getCurDF(), fid);
	if(file != INVALID_FILE) {
		return file;
	}
	//parent file
	file = selectParentDf(fid);
	if(file != INVALID_FILE) {
		return file;
	}
	//brother file
	file = selectChild(getCurDF()->parent, fid);
	if(file != INVALID_FILE) {
		return file;
	}
	return file;
}

FileDesc* selectChild(FileDesc* df, u2 fid) {
	FileDesc* file;
	PRINT_FUNC_NAME();
	
	file = selectChildDf(df, fid);
	if(file == INVALID_FILE) {
		file = selectChildEf(df, fid);
	}
	return file;
}

FileDesc* selectChildSfi(FileDesc* df, u1 sfi) {
	FileDesc* file;
	PRINT_FUNC_NAME();
	
	file = selectChildDfSfi(df, sfi);
	if(file == INVALID_FILE) {
		file = selectChildEfSfi(df, sfi);
	}
	return file;
}

FileDesc* selectChildDf(FileDesc* df, u2 fid) {
	FileDesc* file = INVALID_FILE;
	FileList* curDF = df->childDf;

	PRINT_FUNC_NAME()
	
	while(curDF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		printf("ChildDF[%02X]\n", curDF->me->fid);
#endif		
		if(curDF->me->fid == fid) {
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

	PRINT_FUNC_NAME()
	
	while(curDF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		printf("ChildDF[%02X], sfi[%02X]\n", curDF->me->fid, curDF->me->sfi);
#endif		
		if(curDF->me->sfi == sfi) {
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

	PRINT_FUNC_NAME();
	
	while(curEF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		printf("ChildEF[%02X]\n", curEF->me->fid);
#endif
		if(curEF->me->fid == fid) {
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

	PRINT_FUNC_NAME();
	
	while(curEF != INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2	
		printf("ChildEF[%02X], sfi[%02X]\n", curDF->me->fid, curDF->me->sfi);
#endif
		if(curEF->me->sfi == sfi) {
			file = curEF->me;
			break;
		}
		curEF = curEF->next;
	}
	return file;
}

FileDesc* selectParentDf(u2 fid) {
	FileDesc* file = getCurDF()->parent;
	
	PRINT_FUNC_NAME();
	
	if((file != INVALID_FILE) && (file->fid == fid)) {
		return file;
	}
	return INVALID_FILE;
}

FileDesc* selectbyAID(u1* aidBuf, u1 len, u1 terminal) {
	FileDesc* file;
	
	PRINT_FUNC_NAME();
	
	file = getAdfFileDes(aidBuf, len);
	if(file != INVALID_FILE) {
		return file;
	}
	return INVALID_FILE;
}

FileDesc* selectByPathFromMf(u1* fidPath, u1 len) {
	PRINT_FUNC_NAME();
	return selectByPath(getMF(), fidPath, len);
}
FileDesc* selectByPathFromCurrentDf(u1* fidPath, u1 len) {
	PRINT_FUNC_NAME();
	return selectByPath(getCurDF(), fidPath, len);
}

u2 getShort(u1* buf){
	return (buf[0] << 8) + buf[1];
}
FileDesc* selectByPath(FileDesc* df, u1* fidPath, u1 len) {
	FileDesc* file = df;
	u1 step = len / 2;
	u2 fid;
	u1* pfid = fidPath;

	PRINT_FUNC_NAME();
#if DEBUG_LEVLE > 2	
	printf("selectByPath DF[%02X], len[%02d], step[%02d]\n", df->fid, len, step);
#endif

	while(step --){
		//printf("step[%02d]\n", step);
		fid = getShort(pfid);
#if DEBUG_LEVLE > 2	
		printf("selectByPath fid[%02X]\n", fid);
#endif
		if(fid == 0x7FFF) {
			file = getCurADF();
			pfid += 2;
			//step --;
			continue;
		}
		
		file = selectChild(file, fid);
		if(file == INVALID_FILE) {
			return INVALID_FILE;
		}
		pfid += 2;
	}
	
	return file;
}


void printADF(){
	u1 len, index = 0, i = 0;
	
	len = aidFile[index].aidLen;
	printf("len[%02X], index[%d], aidMember: ", len, index);
	if(len != 0) {
		while(len --) {
			printf("%02X",  *(aidFile[index].aid + (i ++)));
		}
		i = 0;
	}
	
	index ++;
	len = aidFile[index].aidLen;
	printf("len[%02X], index[%d], aidMember: ", len, index);
	if(len != 0) {
		while(len --) {
			printf("%02X",  *(aidFile[index].aid + (i ++)));
		}
		i = 0;
	}
}

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
	setCurTLVTag(FILE_CONTROL_PARAMETERS_TAG);

	setCurTLVLen(0);
	setCurTLVOff(2);
	getFileDescriptor(file, resBuf);
	getFileIdentifier(file, resBuf);
	if(file->filetype == ADF) {
		getDFname(file, resBuf);
	}
	getProprietaryInformation(file, resBuf);
	getLifeCycleStatusInteger(file, resBuf);
	getSecurityattributes(file, resBuf);
	if(isEF) {
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

	if(file->shareble == SHAREABLE) {
		fileDescByte |= 1 << 6;
	}
	if(isEF) {
		fileDescByte |= 1 << 3;
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
	if(isEF && ((file->eftype == CIRCLE) || (file->eftype == LINEAR))) {
		bytes[2] = file->recordLen >> 8;
		bytes[3] = file->recordLen & 0xFF;
		bytes[4] = file->recordCnt;
		appendTLBufferV(resBuf, FILE_DESCRIPTOR_TAG, bytes, 0, 5);
	} else if(isEF){
		appendTLBufferV(resBuf, FILE_DESCRIPTOR_TAG, bytes, 0, 2);
	}
}

void getFileIdentifier(FileDesc* file, u1* resBuf) {
	appendTLShortV(resBuf, FILE_IDENTIFIER_TAG, file->fid);
}

void getDFname(FileDesc* file, u1* resBuf) {
	u1 len;
	u1* buf = getAdfAID(file, &len);
	appendTLBufferV(resBuf, DF_NAME_TAG, buf, 0, len);
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

u2 getCurTLVTag() {
	return tlv->tag;
}
u2 getCurTLVOff() {
	return tlv->offset;
}
u2 getCurTLVLen() {
	return tlv->length;
}
u2 setCurTLVTag(u1 tag) {
	tlv->tag = tag;
}
u2 setCurTLVOff(u2 off) {
	tlv->offset = off;
}
u2 setCurTLVLen(u2 len) {
	tlv->length = len;
}

void appendTLByteV(u1* buffer, u1 tag, u1 val){
	u2 currLen = getCurTLVLen(), currOff = getCurTLVOff(tag);
	currLen += 3;
	buffer[currOff ++] = tag;
	buffer[currOff ++] = 1;
	buffer[currOff ++] = val;
	setCurTLVLen(currLen);
	setCurTLVOff(currOff);
}

void appendTLShortV(u1* buffer, u1 tag, u2 val){
	u2 currLen = getCurTLVLen(), currOff = getCurTLVOff(tag);
	currLen += 4;
	buffer[currOff ++] = tag;
	buffer[currOff ++] = 2;
	buffer[currOff ++] = val >> 8;
	buffer[currOff ++] = val & 0xFF;
	setCurTLVLen(currLen);
	setCurTLVOff(currOff);
}

void appendTLBufferV(u1* buffer, u1 tag, u1* valBuf, u1 valOff, u1 valLen){
	u2 currLen = getCurTLVLen(), currOff = getCurTLVOff(tag);
	currLen += (valLen + 2);
	buffer[currOff ++] = tag;
	buffer[currOff ++] = valLen;
	COS_MEMCPY(buffer + currOff, valBuf + valOff, valLen);
	currOff += valLen;
	setCurTLVLen(currLen);
	setCurTLVOff(currOff);
}




