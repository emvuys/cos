
#include <stdio.h>
#include "../inc/types.h"

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



#define OFFSET_CLS	0
#define OFFSET_INS	1
#define OFFSET_P1	2
#define OFFSET_P2	3
#define OFFSET_P3	4
#define OFFSET_DATA	5


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

typedef enum INS{
	INS_SELECT = 0xA4,
	INS_STATUS = 0xF2,
	INS_VERIFY_PIN = 0x20,
	INS_UNBLOCK_PIN = 0x2C,
	INS_MANAGE_CHANNEL = 0x70,
	INS_READ_BINARY = 0xB0,
	INS_UPDATE_BINARY = 0xD6,
	INS_READ_RECORD = 0xB2,
	INS_UPDATE_RECORD = 0xDC,
	INS_GET_DATA = 0xCA,
	INS_STORE_DATA = 0xE2,
	INS_AUTHENTICATE = 0x88
}INS;

typedef enum fileType {
	MF,
	ADF,
	DF,
	EF
}fileType;

typedef enum efType {
	TRANSPARENT,
	LINEAR,
	CIRCLE,
	BERSTUCT
}efType;

enum fileAccess {
	UNSHAREABLE,
	SHAREABLE
}fileAccess;

enum ErrorCode {
	NONE = 0x9000,
	UNKNOWN = 0x6F00,

	WRONG_LENGTH = 0x6700,
	INVALID_CLA = 0x6E00,
	INVALID_INS = 0x6D00,
	LOGICAL_CHANNEL_NOT_SUPPORTED = 0x6881,
	SECURE_MESSAGE_NOT_SUPPORTED = 0x6882,

	WRONG_PARAMS = 0x6A86,
	WRONG_DATA = 0x6A80,
	FILE_NOT_FOUND = 0x6A82,
	RECORD_NOT_FOUND = 0x6A83,

	SECURITY_NOT_SATISFIED = 0x6982,
	PIN_BLOCKED = 0x6983,
	NO_FILE_SELECTED = 0x6986,

	VERYFY_PIN_RETRY_LEFT_TIME = 0x6C03,
	UNBLOCK_PIN_RETRY_LEFT_TIME = 0x6C0A,

	AUTH_INCORRECT_MAC = 0x9862,
	AUTH_CONTEXT_NOT_SUPPORTED = 0x9864
}ErrorCode;

//struct ArrRef;
//struct FileList;
//struct FileDesc;

typedef struct TLV {
	u1 tag;
	u2 offset;
	u2 length;
}TLV;

typedef struct AIDFileDes {
	u1* aid;
	u1 aidLen;
	struct FileDesc* file;
}AIDFileDes;

typedef struct ArrRef {
	u2 arrFid;
	u1 arrRecordNum;
}ArrRef;


typedef struct FileList {
	struct FileDesc *me;
	struct FileList *next;
}FileList;

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
}FileDesc;


typedef struct ChannelInfo {
	u1 isOpen;
	FileDesc* curEF;
	FileDesc* curDF;
	FileDesc* curADF;
}ChannelInfo;


