#include <stdio.h>
#include <stdlib.h>
#include "filetype.h"
#include "fileSystem.h"

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
	FileDesc *mf, *teleDF, *adf, *phoneBook, *accessDF;
	mf = buildDFADF(DF_MF);
	
	teleDF = buildDFADF(DF_TELECOM);
	addChildDF(mf->childDf, teleDF);
	
	adf = buildDFADF(ADF_USIM);
	addChildDF(mf->childDf, adf);

	phoneBook = buildDFADF(DF_PHONEBOOK);
	addChildDF(adf->childDf, phoneBook);
	addChildDF(teleDF->childDf, phoneBook);

	accessDF = buildDFADF(DF_GSM_ACCESS);
	addChildDF(adf->childDf, accessDF);

	addChildEF(mf->childEf, EFs_MF, sizeof(EFs_MF) / 2);
	addChildEF(adf->childEf, EFs_ADF_USIM, sizeof(EFs_ADF_USIM) / 2);
	addChildEF(teleDF->childEf, EFs_TELECOM, sizeof(EFs_TELECOM) / 2);
	addChildEF(accessDF->childEf, EFs_ACCESS, sizeof(EFs_ACCESS) / 2);
	return mf;
}

FileDesc* buildDFADF(u2 fid) {
	FileDesc* df;
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
	FileDesc* mf = malloc(sizeof(FileDesc));
	FileDesc* df;
	mf->fid = 0x3F00;
	mf->arrRef.arrFid = 0x2F06;
	mf->arrRef.arrFid = 1;
	mf->filetype = MF;

	return mf;
}

FileDesc* buildDF_TELECOM() {
	FileDesc* df;

	return df;
}

FileDesc* buildDF_GSM_ACCESS() {
	FileDesc* df;

	return df;
}

FileDesc* buildDF_PHONEBOOK() {
	FileDesc* df;

	return df;
}

FileDesc* buildADF_USIM() {
	FileDesc* df;

	return df;
}


void addChildDF(FileList* pfileList, FileDesc* file) {
	return;
}

void addChildEF(FileList* pfileList, u2* fids, u2 len) {
	return;
}

