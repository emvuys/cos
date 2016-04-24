#include <stdio.h>
#include <stdlib.h>
#include "filetype.h"
#include "fileSystem.h"



FileDesc* buildEFs(FileDesc* parent, u2* fids, u1 len) {
	u2 fid;
	u1 index = 0;
	FileDesc* ef = NULL;

	if(len == 0) {
		return NULL;
	}
	
	do{
		fid = fids[index];
#ifdef DEBUG_LEVEL2		
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
				ef = creatEF_SPN();
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
		if(ef != NULL) {
			addChildFile(parent, ef, EF);
		}
	}while(index ++ < (len - 1));
}


FileDesc* creatEF_ACC() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ACC;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_ACL() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ACL;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_AD() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_AD;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_ARR() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ARR;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_ARR_SUB() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ARR_SUB;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_DIR() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_DIR;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_ECC() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ECC;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_EHPLMN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_EHPLMN;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_EST() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_EST;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_FPLMN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_FPLMN;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_HPLMNwAcT() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_HPLMNwAcT;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_HPPLMN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_HPPLMN;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_ICCID() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_ICCID;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_IMSI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_IMSI;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_Kc() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_Kc;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_KcGPRS() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_KcGPRS;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_Keys() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_Keys;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_KeysPS() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_KeysPS;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_LI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_LI;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_LOCI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_LOCI;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_NETPAR() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_NETPAR;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_OPL() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_OPL;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_OPLMNwAcT() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_OPLMNwAcT;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_PL() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PL;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_PLMNwAcT() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PLMNwAcT;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_PNN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PNN;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_PSLOCI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_PSLOCI;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_SPDI() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_SPDI;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_SPN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_SPN;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_START_HFN() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_START_HFN;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_THRESHOLD() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_THRESHOLD;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}
FileDesc* creatEF_UST() {
	FileDesc* ef = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(ef, 0, sizeof(FileDesc));
	ef->fid = EF_UST;
	ef->arrRef.arrFid = 0x2F06;
	ef->arrRef.arrFid = 1;
	ef->filetype = EF;

	return ef;
}


