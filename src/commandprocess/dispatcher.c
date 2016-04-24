#include <stdio.h>
#include <stdlib.h>
#include "../filesystem/filetype.h"
#include "../filesystem/fileSystem.h"
#include "../inc/types.h"

FileDesc* MFRef;

void insertCard(u1* iccid, u1* imsi, u1* ki) {
	MFRef = buildFileSystem();
}

void showFS() {
	showFileSystem(MFRef);
}

#define OFFSET_CLS	0
#define OFFSET_INS	1
#define OFFSET_P1	2
#define OFFSET_P2	3
#define OFFSET_P3	4
#define OFFSET_DATA	5

u1 getCLS(char* apdu) {
	return *(apdu + OFFSET_P1);
}
u1 getINS(char* apdu) {
	return *(apdu + OFFSET_P1);
}
u1 getP1(char* apdu) {
	return *(apdu + OFFSET_P1);
}
u1 getP2(char* apdu) {
	return *(apdu + OFFSET_P1);
}
u1 getP3(char* apdu) {
	return *(apdu + OFFSET_P1);
}
u1* getData(char* apdu) {
	return apdu + OFFSET_DATA;
}
u2 getDataByte(char* apduData){
	return *(apduData);
}
u2 getDataShort(char* apduData){
	return *((u2*)apduData);
}

short dispatcher(char* apdu, char* responseBuf, u2* responseLen) {
	unsigned char ins = apdu[1];

	PRINT_FUNC_NAME();

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


short processSelect(char* apdu, char* responseBuf, u2* responseLen){
	u1 needsFcp = 0, flag = 0;
	FileDesc* file;

	PRINT_FUNC_NAME();

	switch ((getP2(apdu) >> 2) & 0x07) {
		case 1: 
			needsFcp = 1;
			break;
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
			file = selectChildDf();
			break;
		case 0x03: // selectParentDf
			file = selectParentDf();
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
	return WRONG_PARAMS;
}

short processManageChannel(char* apdu){
	PRINT_FUNC_NAME();
}

FileDesc* selectMF() {
	return MFRef;
}

FileDesc* selectFId(u2 fid) {
	FileDesc* file;
	// 7FFF, ADF

	// child file

	//parent file

	//brother file

	//MF
	if (fid == 0x7FFF) {
		//return selectFile(currentAdf);
	}

	if (fid == 0x3F00) {
		return selectMF();
	}
	return file;
}
FileDesc* selectChildDf() {
	FileDesc* file;
	return file;
}
FileDesc* selectParentDf() {
	FileDesc* file;
	return file;
}
FileDesc* selectbyAID(u1* aidBuf, u1 len, u1 terminal) {
	FileDesc* file;
	return file;
}
FileDesc* selectByPathFromMf(u1* fidPath, u1 len) {
	FileDesc* file;
	return file;
}
FileDesc* selectByPathFromCurrentDf(u1* fidPath, u1 len) {
	FileDesc* file;
	return file;
}
