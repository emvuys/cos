
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



typedef enum fileType {
	MF,
	ADF,
	DF,
	EF
}fileType;

typedef enum efType {
	TRANSPARENT,
	LINEAR,
	CIRCLE
}efType;

enum fileAccess {
    UNSHAREABLE,
    SHAREABLE
}fileAccess;

struct ArrRef;
struct FileList;
struct FileDesc;

typedef struct ArrRef{
	u2 arrFid;
	u1 arrRecordNum;
}ArrRef;


typedef struct FileList{
	struct FileDesc *me;
	struct FileList *next;
}FileList;

typedef struct FileDesc{
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




