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



u1 getCLS(char* apdu) {
	return *(apdu + OFFSET_CLS);
}
u1 getINS(char* apdu) {
	return *(apdu + OFFSET_INS);
}
u1 getP1(char* apdu) {
	return *(apdu + OFFSET_P1);
}
u1 getP2(char* apdu) {
	return *(apdu + OFFSET_P2);
}
u1 getP3(char* apdu) {
	return *(apdu + OFFSET_P3);
}
u1* getData(char* apdu) {
	return apdu + OFFSET_DATA;
}
u2 getDataByte(char* apduData){
	return *(apduData);
}
u2 getDataShort(char* apduData){
	return ((*(apduData + OFFSET_DATA) << 8) & 0xFF00) | (*(apduData + OFFSET_DATA + 1) & 0xFF);
}

short dispatcher(char* apdu, char* responseBuf, u2* responseLen) {
	unsigned char ins = getINS(apdu);

	PRINT_FUNC_NAME();
	printAPDU(apdu);
	switch(ins) {
		case 0xA4:
			return processSelect(apdu, responseBuf, responseLen);
		case 0x70:
			return processManageChannel(apdu);
			break;
		default:
			PRINT_STR("Unkown command");
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



short processSelect(char* apdu, char* responseBuf, u2* responseLen){
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

short processManageChannel(char* apdu){
	PRINT_FUNC_NAME();
}

FileDesc* selectMF() {
	return MFRef;
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




