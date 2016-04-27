#include <stdio.h>
#include <stdlib.h>
#include "filetype.h"
#include "fileSystem.h"



FileDesc* buildEFs(FileDesc* parent, u2* fids, u1 len) {
	u2 fid;
	u1 index = 0;
	FileDesc* ef = INVALID_FILE;

	if(len == 0) {
		return INVALID_FILE;
	}
	
	do{
		fid = fids[index];
#if DEBUG_LEVLE > 2	
		printf("fid[0x%2x], idx: %d\n", fid, index);
#endif
		switch (fid) {
			case EF_ACC:
				ef = creatEF_ACC();
				break;
			case EF_ACL:
				ef = creatEF_ACL();
				break;
			case EF_AD:
				ef = creatEF_AD();
				break;
			case EF_ARR:
				ef = creatEF_ARR();
				break;
			case EF_ARR_SUB:
				ef = creatEF_ARR_SUB();
				break;
			case EF_DIR:
				ef = creatEF_DIR();
				break;
			case EF_ECC:
				ef = creatEF_ECC();
				break;
			case EF_EHPLMN:
				ef = creatEF_EHPLMN();
				break;
			case EF_EST:
				ef = creatEF_EST();
				break;
			case EF_FPLMN:
				ef = creatEF_FPLMN();
				break;
			case EF_HPLMNwAcT:
				ef = creatEF_HPLMNwAcT();
				break;
			case EF_HPPLMN:
				ef = creatEF_HPPLMN();
				break;
			case EF_ICCID:
				ef = creatEF_ICCID();
				break;
			case EF_IMSI:
				ef = creatEF_IMSI();
				break;
			case EF_Kc:
				ef = creatEF_Kc();
				break;
			case EF_KcGPRS:
				ef = creatEF_KcGPRS();
				break;
			case EF_Keys:
				ef = creatEF_Keys();
				break;
			case EF_KeysPS:
				ef = creatEF_KeysPS();
				break;
			case EF_LI:
				ef = creatEF_LI();
				break;
			case EF_LOCI:
				ef = creatEF_LOCI();
				break;
			case EF_NETPAR:
				ef = creatEF_NETPAR();
				break;
			case EF_OPL:
				ef = creatEF_OPL();
				break;
			case EF_OPLMNwAcT:
				ef = creatEF_OPLMNwAcT();
				break;
			case EF_PL:
				ef = creatEF_PL();
				break;
			case EF_PLMNwAcT:
				ef = creatEF_PLMNwAcT();
				break;
			case EF_PNN:
				ef = creatEF_PNN();
				break;
			case EF_PSLOCI:
				ef = creatEF_PSLOCI();
				break;
			case EF_SPDI:
				ef = creatEF_SPDI();
				break;
			case EF_SPN:
				ef = creatEF_SPN();
				break;
			case EF_START_HFN:
				ef = creatEF_START_HFN();
				break;
			case EF_THRESHOLD:
				ef = creatEF_THRESHOLD();
				break;
			case EF_UST:
				ef = creatEF_UST();
				break;
			default:
				break;
		}
		if(ef != INVALID_FILE) {
			addChildFile(parent, ef, EF);
		}
	}while(index ++ < (len - 1));
}


FileDesc* creatEF_ACC() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ACC;
	ef->sfi = 0x06;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 3;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 01", ef->data, 0);
	
	printFileContent(ef->data, ef->fileLen);
		
	return ef;
}
FileDesc* creatEF_ACL() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ACL;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("01 DD 00", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	
	return ef;
}
FileDesc* creatEF_AD() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_AD;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 00 00 02", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	

	return ef;
}
FileDesc* creatEF_ARR() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ARR;
	ef->sfi = 6;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = LINEAR;
	ef->recordCnt = 2;
	ef->recordLen = 0x20;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("80 01 01 90 00 80 01 1A A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)));
	charString2ByteString("80 01 01 90 00 80 01 02 A4 06 83 01 01 95 01 08 80 01 18 A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)));

	printFileContent(ef->data, ef->fileLen);
	
	
	return ef;
}
FileDesc* creatEF_ARR_SUB() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ARR_SUB;
	ef->sfi = 0x17;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = LINEAR;
	ef->recordCnt = 4;
	ef->recordLen = 0x20;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	
	charString2ByteString("80 01 01 90 00 80 01 1A A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)));
	charString2ByteString("80 01 01 90 00 80 01 02 A4 06 83 01 01 95 01 08 80 01 18 A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)));
	charString2ByteString("80 01 01 A4 06 83 01 01 95 01 08 80 01 1A A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)));
	charString2ByteString("80 01 03 A4 06 83 01 01 95 01 08 80 01 18 A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)));

	printFileContent(ef->data, ef->fileLen);
	

	return ef;
}
FileDesc* creatEF_DIR() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_DIR;
	ef->sfi = 1;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = LINEAR;
	ef->recordCnt = 4;
	ef->recordLen = 0x20;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("61 1A 4F 10 A0 00 00 00 87 10 02 FF 86 FF FF 89 FF FF FF FF 50 06 52 45 44 54 45 41", 
		ef->data, (ef->recordLen * (index ++)));

	printFileContent(ef->data, ef->fileLen);
	

	return ef;
}
FileDesc* creatEF_ECC() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ECC;
	ef->sfi = 1;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = LINEAR;
	ef->recordCnt = 4;
	ef->recordLen = 0x20;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	

	return ef;
}
FileDesc* creatEF_EHPLMN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_EHPLMN;
	ef->sfi = 0x1D;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 3;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	

	return ef;
}
FileDesc* creatEF_EST() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_EST;
	ef->sfi = 0x1D;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_FPLMN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_FPLMN;
	ef->sfi = 0x0D;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF FF FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_HPLMNwAcT() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_HPLMNwAcT;
	ef->sfi = 0x13;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 3;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00 00", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_HPPLMN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_HPPLMN;
	ef->sfi = 0x12;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 3;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("50", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_ICCID() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ICCID;
	ef->sfi = 0x2;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("98 58 02 00 00 00 00 00 00 04", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_IMSI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_IMSI;
	ef->sfi = 0x7;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("08 FF FF FF FF FF FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_Kc() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_Kc;
	ef->sfi = 0x1;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF 07", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_KcGPRS() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_KcGPRS;
	ef->sfi = 0x1;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF 07", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	return ef;
}
FileDesc* creatEF_Keys() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_Keys;
	ef->sfi = 0x8;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x30;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("07 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_KeysPS() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_KeysPS;
	ef->sfi = 0x9;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x30;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("07 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_LI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_LI;
	ef->sfi = 0x2;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 2;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_LOCI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_LOCI;
	ef->sfi = 0xB;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum=4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF FE 00 01", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_NETPAR() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_NETPAR;
//	ef->sfi = 0xB;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum=4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x40;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_OPL() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_OPL;
	ef->sfi = 0x1A;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = LINEAR;
	ef->recordCnt = 4;
	ef->recordLen = 0x20;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("DD DD DD 00 00 FF FE 01", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_OPLMNwAcT() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_OPLMNwAcT;
	ef->sfi = 0x11;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum=4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x40;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	return ef;
}
FileDesc* creatEF_PL() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PL;
	ef->sfi = 0x5;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrRecordNum = 2;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_PLMNwAcT() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PLMNwAcT;
	ef->sfi = 0xA;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x40;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_PNN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PNN;
	ef->sfi = 0x19;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = LINEAR;
	ef->recordCnt = 4;
	ef->recordLen = 0x20;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("43 0D 52 45 44 54 45 41 20 4D 4F 42 49 4C 45 45 06 52 45 44 54 45 41", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	return ef;
}
FileDesc* creatEF_PSLOCI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PSLOCI;
	ef->sfi = 0xC;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF FF FF FF FE 00 01", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_SPDI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_SPDI;
	ef->sfi = 0x1B;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 3;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("A3 0B 80 09 64 F0 00 64 F0 10 64 F0 30", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_SPN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_SPN;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 1;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x20;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 80 7E A2 83 36 79 FB 52 A8 FF FF FF FF FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	return ef;
}
FileDesc* creatEF_START_HFN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_START_HFN;
	ef->sfi = 0x0F;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 00 00 00 00 00", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}
FileDesc* creatEF_THRESHOLD() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_THRESHOLD;
	ef->sfi = 0x10;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);
	return ef;
}
FileDesc* creatEF_UST() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_UST;
	ef->sfi = 0x4;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 3;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 00 0C 04 27 36 04 00 40", ef->data, 0);

	printFileContent(ef->data, ef->fileLen);

	return ef;
}

void charString2ByteString(u1* charString, u1* desBuf, u2 offset) {
	u2 strlength, buflen, i;
	u1* buf;
	u1 left, right;
	
	strlength = COS_STRLEN(charString);
	if(strlength < 3) {
		strlength = 3;
	}
	buflen = (strlength + 1) / 3;
	buf = COS_MALLOC(buflen);


	for(i = 0; i < strlength; i += 3) {
		left = hexToDec(*(charString + i));
		right = hexToDec(*(charString + i + 1));
		buf[i /3] = (left << 4) + right;
	}
	COS_MEMCPY(desBuf + offset, buf, buflen);
	COS_FREE(buf);
}

u1 hexToDec(u1 c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	if ('A' <= c && c <= 'F') {
		return c - 'A' + 10;
	}
	if ('a' <= c && c <= 'f') {
		return c - 'a' + 10;
	}
	return -1;
}

void printFileContent(u1* buff, u2 length) {
	u2 i;

	return;
	printf("File: ");
	for(i = 0; i < length; i ++) {
		printf("%02X", *(buff + i));
	}
	printf("\n");
}

