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
	EF_KIOPC,
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
FileDesc* MFRef;
FileDesc* AdfUsimRef;
Profile* profile;

FileDesc* buildFileSystem() {
	FileDesc *mf, *teleDF, *adf, *phoneBook, *accessDF, *phoneBook_adf, *phoneBook_teleDF;

	PRINT_FUNC_NAME();

	profile = COS_MALLOC(sizeof(Profile));

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

