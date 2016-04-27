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


AIDFileDes aidFile[AID_COUNT];

	
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

	PRINT_FUNC_DONE();
		
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
	mf->childDf = INVALID_FILE_LIST;
	mf->childEf = INVALID_FILE_LIST;
	mf->parent = INVALID_FILE;

	MFRef = mf;

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
	df->childDf = INVALID_FILE_LIST;
	df->childEf = INVALID_FILE_LIST;
	
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
	df->childDf = INVALID_FILE_LIST;
	df->childEf = INVALID_FILE_LIST;
	
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
	df->childDf = INVALID_FILE_LIST;
	df->childEf = INVALID_FILE_LIST;
	
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
	df->childDf = INVALID_FILE_LIST;
	df->childEf = INVALID_FILE_LIST;
	
	addAdfAid(ADF_USIM_AID, df, 0);

	AdfUsimRef = df;
	
	return df;
}

void addChildEFs(FileDesc* parent, u2* fids, u2 len) {
	PRINT_FUNC_NAME();
#if DEBUG_LEVLE > 2	
	printf("fid num: %d\n", len);
#endif	
	buildEFs(parent,  fids, len);
}

void addChildFile(FileDesc* parent, FileDesc* file, u1 fileType) {
	FileList* p, *pNew, **pfileList;
	PRINT_FUNC_NAME();

#if DEBUG_LEVLE > 2		
		printf("addChildFile: [0x%2X]======\n", file->fid);
#endif		

	file->parent = parent;
	
	if(fileType == EF) {
		pfileList = &(parent->childEf);
	} else if(fileType == DF) {
		pfileList = &(parent->childDf);
	}
	
	if(*pfileList == INVALID_FILE_LIST) {
		PRINT_STR("pfileList is INVALID_FILE_LIST");
		pNew = COS_MALLOC(sizeof(FileList));
#if DEBUG_LEVLE > 2			
		printf("COS_MALLOC addr[0x%4X]======\n", (int)pNew);
#endif		
		COS_MEMSET(pNew, 0, sizeof(FileList));
		pNew->me = file;
		pNew->next = INVALID_FILE_LIST;
		*pfileList = pNew;
	}
	else {
		PRINT_STR("pfileList is NOT INVALID_FILE_LIST");
		p = *pfileList;
#if DEBUG_LEVLE > 2	
		printf("pfileList addr[0x%4X], fid[0x%02X]======\n", (int)p, p->me->fid);
#endif
		while(p->next!= INVALID_FILE_LIST) {
#if DEBUG_LEVLE > 2		
			printf("pfileList addr next[0x%4X], fid[0x%02X]======\n", (int)(p->next), p->me->fid);
#endif
			p = p->next;
		}
		pNew = COS_MALLOC(sizeof(FileList));
#if DEBUG_LEVLE > 2		
		printf("COS_MALLOC addr[0x%4X]======\n", (int)pNew);
#endif
		COS_MEMSET(pNew, 0, sizeof(FileList));
		pNew->me = file;
		pNew->next = INVALID_FILE_LIST;
		p->next = pNew;
	}
}

void showFileSystem(FileDesc* mf) {

	PRINT_FUNC_NAME();

	if(mf == INVALID_FILE) {
		PRINT_STR("MF is INVALID_FILE");
	}
	
	PRINTGG();
	if(mf->childDf != INVALID_FILE_LIST) {
		showChildDFEF(mf->childDf);
	}
	else {
		PRINT_STR("childDf is INVALID_FILE");
	}

	PRINTGG();

	if(mf->childEf != INVALID_FILE_LIST) {
		showChildDFEF(mf->childEf);
	}
	else {
		PRINT_STR("childEf is INVALID_FILE");
	}

	PRINTGG();

}

void showChildDFEF(FileList* fileList) {
	FileDesc* pFile;
	FileList* pListNode = fileList;

	PRINT_FUNC_NAME();
	
	while(pListNode != INVALID_FILE_LIST) {
		pFile = pListNode->me;
		printf("fid: 0x%2X, type: %d, ", pFile->fid, pFile->filetype);
		if(pFile->parent != INVALID_FILE) {
			printf("parentfid: 0x%2X, type: %d\n", pFile->parent->fid, pFile->parent->filetype);
		}
		else {
			printf("parent is INVALID_FILE\n");
		}
		if((pListNode->me->filetype == DF) || (pListNode->me->filetype == ADF)) {
			if(pListNode->me->childDf != INVALID_FILE_LIST) {
				showChildDFEF(pListNode->me->childDf);
			}
			if(pListNode->me->childEf != INVALID_FILE_LIST) {
				showChildDFEF(pListNode->me->childEf);
			}
		}
		pListNode = pListNode->next;
	}
}

u1* getAdfAID(FileDesc* file, u1* aidLen) {
	u1 i = 0;
	while(i ++ < sizeof(aidFile)) {
		if(file == aidFile[i].file) {
			*aidLen = aidFile[i].aidLen;
			return aidFile[i].aid;
		}
	}
	return NULL;
}

FileDesc* getAdfFileDes(u1* aid, u1 aidLen) {
	FileDesc* file = INVALID_FILE;
	u1 index = 0, i = 0, len = aidLen;

	PRINT_FUNC_NAME();

#if DEBUG_LEVLE > 2	
	printf("len[%02X], aid: ", len);
	while(len --) {
		printf("%02X",  *(aid + (i ++)));
	}
	printf("\n");
	i = 0;
#endif

	do{
#if DEBUG_LEVLE > 2		
		len = aidFile[index].aidLen;
		if(aidFile[index].file != INVALID_FILE) {
			printf("len[%02X], index[%d], fid[%02X], aidMember: ", len, index,  aidFile[index].file->fid);
		}
		else {
			printf("len[%02X], index[%d], aidMember: ", len, index);
		}
		if(len != 0) {
			while(len --) {
				printf("%02X",  *(aidFile[index].aid + (i ++)));
			}
			i = 0;
		}
		printf("\n");
#endif
		if((aidFile[index].aidLen != 0) &&
			(aidFile[index].aidLen == aidLen) && 
			(COS_MEMCMP(aidFile[index].aid, aid, aidLen) == 0) &&
			(aidFile[index].file != INVALID_FILE)) {
			file = aidFile[index].file;
			break;
		}
	}while(index ++ < (AID_COUNT - 1));

	if(file != INVALID_FILE) {
		printf("ADF found: fid[%02X]\n", file->fid);
	}
	
	return file;
}

void addAdfAid(u1 * aid, FileDesc* file, u1 index) {
	u1* buf, len;
	buf = aidString2Buffer(aid, &len);
	aidFile[index].aid = buf;
	aidFile[index].aidLen = len;
	aidFile[index].file = file;

	PRINT_FUNC_NAME();
	printf("aid[%s], len[%02X], index[%d], fid[%02X]\n", aid, len, index, file->fid);
}

u1* aidString2Buffer(u1* aid, u1* aidlen) {
	u1* buf, left, right, i;
	u1 strlength  = COS_STRLEN(aid);
	u1 buflen = strlength / 2;

	PRINT_FUNC_NAME();
	printf("aid[%s], len[%02X]\n", aid, buflen);
	
	buf = COS_MALLOC(buflen);

	for(i = 0; i < strlength; i += 2) {
		left = hexToDec(*(aid + i));
		right = hexToDec(*(aid + i + 1));
		buf[i /2] = (left << 4) + right;
	}
	*aidlen = buflen;
	return buf;
}

