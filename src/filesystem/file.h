#ifndef __FILE_H__
#define __FILE_H__

#define INVALID_FILE			(FileDesc*)(-1)
#define INVALID_FILE_LIST	(FileList*)(-1)

#define ADF_USIM_AID		"A0000000871002FF86FFFF89FFFFFFFF"
#define ADF_USIM_AID_LEN	0x10

#define DF_MF			0x3F00
#define ADF_USIM			0x7FF0
#define DF_GSM_ACCESS	0x5F3B
#define DF_PHONEBOOK	0x5F3A
#define DF_TELECOM		0x7F10

#define EF_ACC			0x6F78
#define EF_ACL			0x6F57
#define EF_AD			0x6FAD
#define EF_ARR			0x2F06
#define EF_ARR_SUB		0x6F06
#define EF_DIR			0x2F00
#define EF_ECC			0x6FB7
#define EF_EHPLMN		0x6FD9
#define EF_EST			0x6F56
#define EF_FPLMN			0x6F7B
#define EF_HPLMNwAcT	0x6F62
#define EF_HPPLMN		0x6F31
#define EF_ICCID			0x2FE2
#define EF_IMSI			0x6F07
#define EF_Kc				0x4F20
#define EF_KcGPRS		0x4F52
#define EF_Keys			0x6F08
#define EF_KeysPS		0x6F09
#define EF_LI				0x6F05
#define EF_LOCI			0x6F7E
#define EF_NETPAR		0x6FC4
#define EF_OPL			0x6FC6
#define EF_OPLMNwAcT	0x6F61
#define EF_PL				0x2F05
#define EF_PLMNwAcT		0x6F60
#define EF_PNN			0x6FC5
#define EF_PSLOCI		0x6F73
#define EF_SPDI			0x6FCD
#define EF_SPN			0x6F46
#define EF_START_HFN	0x6F5B
#define EF_THRESHOLD	0x6F5C
#define EF_UST			0x6F38

#define FILE_CONTROL_PARAMETERS_TAG		0x62
#define FILE_SIZE_TAG						0x80
#define FILE_DESCRIPTOR_TAG					0x82
#define FILE_IDENTIFIER_TAG					0x83
#define DF_NAME_TAG							0x84
#define SHORT_FILE_IDENTIFIER_TAG			0x88
#define LIFE_CYCLE_STATUS_INTEGER_TAG		0x8A
#define SECURITY_ATTRIBUTES_TAG			0x8B
#define PROPRIETARY_INFORMATION_TAG		0xA5
#define PIN_STATUS_TEMPLATE_DO_TAG		0xC6
#define UICC_CHARACTERISTICS_TAG			0x80

#define PMLNS_SPLITER		(';')

typedef enum fileType {
	MF,
	ADF,
	DF,
	EF
} fileType;

typedef enum efType {
	TRANSPARENT,
	LINEAR,
	CIRCLE,
	BERSTUCT
} efType;

enum fileAccess {
	UNSHAREABLE,
	SHAREABLE
} fileAccess;


typedef struct AIDFileDes {
	u1* aid;
	u1 aidLen;
	struct FileDesc* file;
} AIDFileDes;

typedef struct ArrRef {
	u2 arrFid;
	u1 arrRecordNum;
} ArrRef;

typedef struct FileList {
	struct FileDesc *me;
	struct FileList *next;
} FileList;

typedef struct FileDesc {
	u2 fid;
	u1 sfi;
	u1 shareble;
	fileType filetype;
	efType eftype;
	struct ArrRef arrRef;
	u1* aid;
	struct FileDesc* parent;
	struct FileList* childEf;
	struct FileList* childDf;	
	
	u1* data;
	u2 fileLen;
	u1 recordLen;
	u1 recordCnt;
	u1 recordPointer;
} FileDesc;

typedef struct Profile {
	FileDesc* imsi;
	FileDesc* ki;
	FileDesc* opc;
	FileDesc* iccid;
	FileDesc* acc;
	FileDesc* spn;
	FileDesc* apn;	
	FileDesc* hplmn;
	FileDesc* ehplmn;
	FileDesc* loci;
	FileDesc* psloci;
	FileDesc* fplmn;
} Profile;

extern u1 isFileEF(FileDesc* file);

extern void initADF();
extern void getADFName(FileDesc* file, u1* resBuf);
extern void addAdfAid(u1 * aid, FileDesc* file, u1 index);
extern FileDesc* getAdfFileDes(u1* aid, u1 aidLen);
extern u1* getAdfAID(FileDesc* file, u1* aidLen);

extern void addChildFile(FileDesc* parent, FileDesc* file, u1 fileType);
extern void addChildEFs(FileDesc* parent, u2* fids, u2 len);

extern void getFCP(FileDesc* file, u1* resBuf);
extern void getFileDescriptor(FileDesc* file, u1* resBuf);
extern void getFileIdentifier(FileDesc* file, u1* resBuf);
extern void getDFname(FileDesc* file, u1* resBuf);
extern void getProprietaryInformation(FileDesc* file, u1* resBuf);
extern void getLifeCycleStatusInteger(FileDesc* file, u1* resBuf);
extern void getSecurityattributes(FileDesc* file, u1* resBuf);
extern void getFilesize(FileDesc* file, u1* resBuf);
extern void getTotalfilesize(FileDesc* file, u1* resBuf);
extern void getShortFileIdentifier(FileDesc* file, u1* resBuf);
extern void getPINStatusTemplateDO(FileDesc* file, u1* resBuf);

extern void configureProfile(	u1* imsi,
							u1* ki,
							u1* opc,
							u1* iccid,
							u1* acc,
							u1* spn,
							u1* hplmn,
							u1* ehplmn,
							u1* loci,
							u1* psloci,
							u1* fplmn );
extern void configIMSI(u1* imsi);
extern void configKI(u1* ki);
extern void configOPC(u1* opc);
extern void configICCID(u1* iccid);
extern void configACC(u1* acc);
extern void configSPN(u1* spn);
extern void configHPLMN(u1* hplmn);
extern void configEHPLMN(u1* ehplmn);
extern void configLOCI(u1* loci);
extern void configPSLOCI(u1* psloci);
extern void configFPLMN(u1* fplmn);

#endif

