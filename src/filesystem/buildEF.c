#include "../inc/types.h"

FileDesc* buildEFs(FileDesc* parent, u2* fids, u1 len) {
	u2 fid;
	u1 index = 0;
	FileDesc* ef = INVALID_FILE;

	if (len == 0) {
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
				profile->acc = ef;
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
				profile->ehplmn= ef;
				break;
			case EF_EST:
				ef = creatEF_EST();
				break;
			case EF_FPLMN:
				ef = creatEF_FPLMN();
				profile->fplmn= ef;
				break;
			case EF_HPLMNwAcT:
				ef = creatEF_HPLMNwAcT();
				break;
			case EF_HPPLMN:
				ef = creatEF_HPPLMN();
				profile->hplmn= ef;
				break;
			case EF_ICCID:
				ef = creatEF_ICCID();
				profile->iccid= ef;
				break;
			case EF_IMSI:
				ef = creatEF_IMSI();
				profile->imsi= ef;
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
				profile->loci= ef;
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
				profile->psloci= ef;
				break;
			case EF_SPDI:
				ef = creatEF_SPDI();
				break;
			case EF_SPN:
				ef = creatEF_SPN();
				profile->spn= ef;
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
#ifdef KIOPC_FILE				
			case EF_KIOPC:
				ef = creatEF_KIOPC();
				profile->ki = ef;
				profile->opc = ef;
				break;
#endif				
			default:
				break;
		}
		if (ef != INVALID_FILE) {
			addChildFile(parent, ef, EF);
		}
	} while (index ++ < (len - 1));
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
	ef->fileLen = 2;  //31102, 4.2.15
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 01", ef->data, 0, STRING_SPACE_NOWAPE);
	
	printFileContent(ef);
		
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
	ef->fileLen = 0xC8; // telecom
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("01 DD 00", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
	
	return ef;
}

FileDesc* creatEF_AD() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_AD;
	ef->sfi = 0x03;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 4; // ?
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 00 00 02", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
	

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
	ef->recordCnt = 0x10;
	ef->recordLen = 0x2E; // ?
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("80 01 01 90 00 80 01 1A A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)), STRING_SPACE_NOWAPE);
	charString2ByteString("80 01 01 90 00 80 01 02 A4 06 83 01 01 95 01 08 80 01 18 A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)), STRING_SPACE_NOWAPE);

	printFileContent(ef);
	
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
	ef->recordCnt =0x10;
	ef->recordLen = 0x2E; // ?
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	
	charString2ByteString("80 01 01 90 00 80 01 1A A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)), STRING_SPACE_NOWAPE);
	charString2ByteString("80 01 01 90 00 80 01 02 A4 06 83 01 01 95 01 08 80 01 18 A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)), STRING_SPACE_NOWAPE);
	charString2ByteString("80 01 01 A4 06 83 01 01 95 01 08 80 01 1A A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)), STRING_SPACE_NOWAPE);
	charString2ByteString("80 01 03 A4 06 83 01 01 95 01 08 80 01 18 A4 06 83 01 0A 95 01 08", 
		ef->data, (ef->recordLen * (index ++)), STRING_SPACE_NOWAPE);

	printFileContent(ef);

	return ef;
}

FileDesc* creatEF_DIR() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_DIR;
	ef->sfi = 0x1E;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 1;
	ef->filetype = EF;
	ef->eftype = LINEAR;
	ef->recordCnt = 4;
	ef->recordLen = 0x26; // ?
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("61 1A 4F 10 A0 00 00 00 87 10 02 FF 86 FF FF 89 FF FF FF FF 50 06 52 45 44 54 45 41", 
		ef->data, (ef->recordLen * (index ++)), STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->recordLen = 20;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
	
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
	ef->fileLen = 0x0C;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
	
	return ef;
}

FileDesc* creatEF_EST() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_EST;
	ef->sfi = 0x05;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x1;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 0x0C;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF FF FF FF FF", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00 00", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 1;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("50", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 10;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("98 58 02 00 00 00 00 00 00 04", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 9;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString(DEFAULT_IMIS, ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 9;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF 07", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

	return ef;
}

FileDesc* creatEF_KcGPRS() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_KcGPRS;
	ef->sfi = 0x2;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum= 4;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 9;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF 07", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
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
	ef->fileLen = 33;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("07 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF",
		ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 33;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("07 FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF", 
		ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 4;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 11;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF FE 00 01", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	charString2ByteString("FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF FF",
		ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->recordLen = 0x40;
	ef->fileLen = ef->recordCnt * ef->recordLen;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("DD DD DD 00 00 FF FE 01", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 0x0DAC;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00", 
		ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
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
	ef->fileLen = 4;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 0x28;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00 FF FF FF 00 00",
		ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	charString2ByteString("43 0D 52 45 44 54 45 41 20 4D 4F 42 49 4C 45 45 06 52 45 44 54 45 41", 
		ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
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
	ef->fileLen = 14;
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF FF FF FF FF FF FF FF FF FE 00 01", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	charString2ByteString("A3 0B 80 09 64 F0 00 64 F0 10 64 F0 30", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 17; //31102, 4.2.12
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 80 7E A2 83 36 79 FB 52 A8 FF FF FF FF FF FF FF", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
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
	ef->fileLen = 6; //31102, 4.2.51
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 00 00 00 00 00", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

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
	ef->fileLen = 3;  //31102, 4.2.52
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("FF FF FF", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);
	
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
	ef->fileLen = 10; // telecom
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString("00 00 0C 04 27 36 04 00 40", ef->data, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

	return ef;
}
#ifdef KIOPC_FILE
FileDesc* creatEF_KIOPC() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	u1* buf, index = 0;
	u2 len;
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_KIOPC;
	ef->shareble = SHAREABLE;
	ef->arrRef.arrFid = 0x6F06;
	ef->arrRef.arrRecordNum = 3;
	ef->filetype = EF;
	ef->eftype = TRANSPARENT;
	ef->fileLen = 0x20; // telecom
	ef->data = COS_MALLOC(ef->fileLen);
	COS_MEMSET(ef->data, 0xFF, ef->fileLen);
	charString2ByteString(DEFAULT_KI, ef->data, 0, STRING_SPACE_NOWAPE);
	charString2ByteString(DEFAULT_OPC, ef->data + LENGTH_KI, 0, STRING_SPACE_NOWAPE);

	printFileContent(ef);

	return ef;
}
#endif

