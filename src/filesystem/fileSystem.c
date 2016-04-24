#include <stdio.h>
#include <stdlib.h>
#include "filetype.h"
#include "fileSystem.h"
#include "../inc/types.h"

u2 EFs_ACCESS[] = {
	EF_Kc, 
	EF_KcGPRS
};
u2 EFs_TELECOM[] = {
	EF_ARR_SUB
};
u2 EFs_MF[] = {
	EF_DIR,
	EF_PL,
	EF_ARR,
	EF_ICCID,
	DF_TELECOM,
	ADF_USIM
};
u2 EFs_ADF_USIM[] = {
	EF_LI,
	EF_ARR_SUB,
	EF_IMSI,
	EF_Keys,
	EF_KeysPS,
	EF_HPPLMN,
	EF_UST,
	EF_SPN,
	EF_EST,
	EF_ACL,
	EF_START_HFN,
	EF_THRESHOLD,
	EF_PLMNwAcT,
	EF_OPLMNwAcT,
	EF_HPLMNwAcT,
	EF_PSLOCI,
	EF_ACC,
	EF_FPLMN,
	EF_LOCI,
	EF_AD,
	EF_ECC,
	EF_NETPAR,
	EF_PNN,
	EF_OPL,
	EF_SPDI,
	EF_EHPLMN
};


	
FileDesc* buildFileSystem() {
	FileDesc *mf, *teleDF, *adf, *phoneBook, *accessDF, *phoneBook_adf, *phoneBook_teleDF;

	PRINT_FUNC_NAME();

	mf = buildDFADF(DF_MF);
	
	teleDF = buildDFADF(DF_TELECOM);
	addChildFile(mf, teleDF, DF);
	
	adf = buildDFADF(ADF_USIM);
	addChildFile(mf, adf, DF);

	phoneBook_adf = buildDFADF(DF_PHONEBOOK);
	addChildFile(adf, phoneBook_adf, DF);
	phoneBook_teleDF = buildDFADF(DF_PHONEBOOK);
	addChildFile(teleDF, phoneBook_teleDF, DF);

	accessDF = buildDFADF(DF_GSM_ACCESS);
	addChildFile(adf, accessDF, DF);

	addChildEFs(mf, EFs_MF, sizeof(EFs_MF) / 2);
	addChildEFs(adf, EFs_ADF_USIM, sizeof(EFs_ADF_USIM) / 2);
	addChildEFs(teleDF, EFs_TELECOM, sizeof(EFs_TELECOM) / 2);
	addChildEFs(accessDF, EFs_ACCESS, sizeof(EFs_ACCESS) / 2);
	return mf;
}

FileDesc* buildDFADF(u2 fid) {
	FileDesc* df;
	PRINT_FUNC_NAME();
	switch (fid) {
		case DF_MF:
			df = buildDF_MF();
			break;
		case DF_TELECOM:
			df = buildDF_TELECOM();
			break;
		case DF_GSM_ACCESS:
			df = buildDF_GSM_ACCESS();
			break;
		case DF_PHONEBOOK:
			df = buildDF_PHONEBOOK();
			break;
		case ADF_USIM:
			df = buildADF_USIM();
			break;
	}
	
	return df;
}



FileDesc* buildDF_MF() {
	FileDesc* mf = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(mf, 0, sizeof(FileDesc));
	mf->fid = 0x3F00;
	mf->arrRef.arrFid = 0x2F06;
	mf->arrRef.arrFid = 1;
	mf->filetype = MF;

	return mf;
}

FileDesc* buildDF_TELECOM() {
	FileDesc* df = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(df, 0, sizeof(FileDesc));
	df->fid = DF_TELECOM;
	df->arrRef.arrFid = 0x2F06;
	df->arrRef.arrFid = 1;
	df->filetype = DF;
	return df;
}

FileDesc* buildDF_GSM_ACCESS() {
	FileDesc* df = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(df, 0, sizeof(FileDesc));
	df->fid = DF_GSM_ACCESS;
	df->arrRef.arrFid = 0x2F06;
	df->arrRef.arrFid = 1;
	df->filetype = DF;
	return df;
}

FileDesc* buildDF_PHONEBOOK() {
	FileDesc* df = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(df, 0, sizeof(FileDesc));
	df->fid = DF_PHONEBOOK;
	df->arrRef.arrFid = 0x2F06;
	df->arrRef.arrFid = 1;
	df->filetype = DF;
	return df;
}

FileDesc* buildADF_USIM() {
	FileDesc* df = COS_MALLOC(sizeof(FileDesc));
	PRINT_FUNC_NAME();
	
	COS_MEMSET(df, 0, sizeof(FileDesc));
	df->fid = ADF_USIM;
	df->arrRef.arrFid = 0x2F06;
	df->arrRef.arrFid = 1;
	df->filetype = ADF;
	return df;
}

void addChildEFs(FileDesc* parent, u2* fids, u2 len) {
	PRINT_FUNC_NAME();
#ifdef DEBUG_LEVEL2
	printf("fid num: %d\n", len);
#endif	
	buildEFs(parent,  fids, len);
}

void addChildFile(FileDesc* parent, FileDesc* file, u1 fileType) {
	FileList* p, *pNew, **pfileList;
	PRINT_FUNC_NAME();

	file->parent = parent;
	
	if(fileType == EF) {
		pfileList = &(parent->childEf);
	} else if(fileType == DF) {
		pfileList = &(parent->childDf);
	}
	
	if(*pfileList == NULL) {
		PRINT_STR("pfileList is NULL");
		pNew = COS_MALLOC(sizeof(FileList));
#ifdef DEBUG_LEVEL2		
		printf("COS_MALLOC addr[0x%4X]======\n", (int)pNew);
#endif		
		COS_MEMSET(pNew, 0, sizeof(FileList));
		pNew->me = file;
		pNew->next = NULL;
		*pfileList = pNew;
	}
	else {
		PRINT_STR("pfileList is NOT NULL");
		p = *pfileList;
#ifdef DEBUG_LEVEL2		
		printf("pfileList addr[0x%4X], fid[0x%02X]======\n", (int)p, p->me->fid);
#endif
		while(p->next!= NULL) {
#ifdef DEBUG_LEVEL2
			printf("pfileList addr next[0x%4X], fid[0x%02X]======\n", (int)(p->next), p->me->fid);
#endif
			p = p->next;
		}
		pNew = COS_MALLOC(sizeof(FileList));
#ifdef DEBUG_LEVEL2		
		printf("COS_MALLOC addr[0x%4X]======\n", (int)pNew);
#endif
		COS_MEMSET(pNew, 0, sizeof(FileList));
		pNew->me = file;
		pNew->next = NULL;
		p->next = pNew;
	}
}

void showFileSystem(FileDesc* mf) {

	PRINT_FUNC_NAME();

	if(mf == NULL) {
		PRINT_STR("MF is NULL");
	}
	
	PRINTGG();
	if(mf->childDf != NULL) {
		
		showChildDFEF(mf->childDf);
	}
	else {
		PRINT_STR("childDf is NULL");
	}

	PRINTGG();

	if(mf->childEf != NULL) {
		
		showChildDFEF(mf->childEf);
	}
	else {
		PRINT_STR("childEf is NULL");
	}

	PRINTGG();

}

void showChildDFEF(FileList* fileList) {
	FileDesc* pFile;
	FileList* pListNode = fileList;

	//PRINT_FUNC_NAME();
	
	while(pListNode != NULL) {
		pFile = pListNode->me;
		printf("fid: 0x%2X, type: %d, ", pFile->fid, pFile->filetype);
		if(pFile->parent != NULL) {
			printf("parentfid: 0x%2X, type: %d\n", pFile->parent->fid, pFile->parent->filetype);
		}
		else {
			printf("parent is NULL\n");
		}
		if((pListNode->me->filetype == DF) || (pListNode->me->filetype == ADF)) {
			if(pListNode->me->childDf != NULL) {
				showChildDFEF(pListNode->me->childDf);
			}
			if(pListNode->me->childEf != NULL) {
				showChildDFEF(pListNode->me->childEf);
			}
		}
		pListNode = pListNode->next;
	}
}

