short processSelect(char* apdu, char* responseBuf, u2* responseLen);
short processManageChannel(char* apdu);

extern FileDesc* buildFileSystem();
extern FileDesc* buildDFADF(u2 fid);
extern FileDesc* buildDF_MF();
extern FileDesc* buildDF_TELECOM();
extern FileDesc* buildDF_GSM_ACCESS();
extern FileDesc* buildDF_PHONEBOOK();
extern FileDesc* buildADF_USIM();

void addChildFile(FileDesc* parent, FileDesc* file, u1 fileType);
void addChildEFs(FileDesc* parent, u2* fids, u2 len);
FileDesc* buildEFs(FileDesc* parent, u2* fids, u1 len);

FileDesc* creatEF_ACC();
FileDesc* creatEF_ACL();
FileDesc* creatEF_AD();
FileDesc* creatEF_ARR();
FileDesc* creatEF_ARR_SUB();
FileDesc* creatEF_DIR();
FileDesc* creatEF_ECC();
FileDesc* creatEF_EHPLMN();
FileDesc* creatEF_EST();
FileDesc* creatEF_FPLMN();
FileDesc* creatEF_HPLMNwAcT();
FileDesc* creatEF_HPPLMN();
FileDesc* creatEF_ICCID();
FileDesc* creatEF_IMSI();
FileDesc* creatEF_Kc();
FileDesc* creatEF_KcGPRS();
FileDesc* creatEF_Keys();
FileDesc* creatEF_KeysPS();
FileDesc* creatEF_LI();
FileDesc* creatEF_LOCI();
FileDesc* creatEF_NETPAR();
FileDesc* creatEF_OPL();
FileDesc* creatEF_OPLMNwAcT();
FileDesc* creatEF_PL();
FileDesc* creatEF_PLMNwAcT();
FileDesc* creatEF_PNN();
FileDesc* creatEF_PSLOCI();
FileDesc* creatEF_SPDI();
FileDesc* creatEF_SPN();
FileDesc* creatEF_START_HFN();
FileDesc* creatEF_THRESHOLD();
FileDesc* creatEF_UST();

void showFileSystem(FileDesc* mf);
void showChildDFEF(FileList* fileList);

void charString2ByteString(u1* charString, u1* desBuf, u2 offset);
u1 hexToDec(u1 c);

void printFileContent(u1* buff, u2 length);

void insertCard(u1* iccid, u1* imsi, u1* ki);

void showFS();


u1 getCLS(char* apdu);
u1 getINS(char* apdu);
u1 getP1(char* apdu);
u1 getP2(char* apdu);
u1 getP3(char* apdu) ;
u1* getData(char* apdu);
u2 getDataByte(char* apduData);
u2 getDataShort(char* apduData);


FileDesc* selectFId(u2 fid);
FileDesc* selectChildDf();
FileDesc* selectParentDf();
FileDesc* selectbyAID(u1* aidBuf, u1 len, u1 terminal);
FileDesc* selectByPathFromMf(u1* fidPath, u1 len);
FileDesc* selectByPathFromCurrentDf(u1* fidPath, u1 len);

extern ChannelInfo channels[4];
extern u2 curChannelID;


