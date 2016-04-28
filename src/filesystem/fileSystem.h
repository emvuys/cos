#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#define AID_COUNT	2

extern AIDFileDes aidFile[AID_COUNT];
extern FileDesc* MFRef;
extern FileDesc* AdfUsimRef;
extern Profile* profile;

extern FileDesc* buildFileSystem();
extern FileDesc* buildDFADF(u2 fid);
extern FileDesc* buildDF_MF();
extern FileDesc* buildDF_TELECOM();
extern FileDesc* buildDF_GSM_ACCESS();
extern FileDesc* buildDF_PHONEBOOK();
extern FileDesc* buildADF_USIM();

extern FileDesc* buildEFs(FileDesc* parent, u2* fids, u1 len);
extern FileDesc* creatEF_ACC();
extern FileDesc* creatEF_ACL();
extern FileDesc* creatEF_AD();
extern FileDesc* creatEF_ARR();
extern FileDesc* creatEF_ARR_SUB();
extern FileDesc* creatEF_DIR();
extern FileDesc* creatEF_ECC();
extern FileDesc* creatEF_EHPLMN();
extern FileDesc* creatEF_EST();
extern FileDesc* creatEF_FPLMN();
extern FileDesc* creatEF_HPLMNwAcT();
extern FileDesc* creatEF_HPPLMN();
extern FileDesc* creatEF_ICCID();
extern FileDesc* creatEF_IMSI();
extern FileDesc* creatEF_Kc();
extern FileDesc* creatEF_KcGPRS();
extern FileDesc* creatEF_Keys();
extern FileDesc* creatEF_KeysPS();
extern FileDesc* creatEF_LI();
extern FileDesc* creatEF_LOCI();
extern FileDesc* creatEF_NETPAR();
extern FileDesc* creatEF_OPL();
extern FileDesc* creatEF_OPLMNwAcT();
extern FileDesc* creatEF_PL();
extern FileDesc* creatEF_PLMNwAcT();
extern FileDesc* creatEF_PNN();
extern FileDesc* creatEF_PSLOCI();
extern FileDesc* creatEF_SPDI();
extern FileDesc* creatEF_SPN();
extern FileDesc* creatEF_START_HFN();
extern FileDesc* creatEF_THRESHOLD();
extern FileDesc* creatEF_UST();

#endif

