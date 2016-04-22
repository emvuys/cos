
extern FileDesc* buildFileSystem();
extern FileDesc* buildMF();
extern FileDesc* buildDF(u2 fid);
extern FileDesc* buildADF();
extern void addChild();



extern FileDesc* buildDFADF(u2 fid);

extern FileDesc* buildDF_MF();

extern FileDesc* buildDF_TELECOM();

extern FileDesc* buildDF_GSM_ACCESS();

extern FileDesc* buildDF_PHONEBOOK();

extern FileDesc* buildADF_USIM();

void addChildDF(FileList* pfileList, FileDesc* file);
void addChildEF(FileList* pfileList, u2* fids, u2 len);
