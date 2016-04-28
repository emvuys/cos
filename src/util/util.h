#ifndef __UTIL_H__
#define __UTIL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define OFFSET_CLS	0
#define OFFSET_INS	1
#define OFFSET_P1	2
#define OFFSET_P2	3
#define OFFSET_P3	4
#define OFFSET_DATA	5

typedef struct TLV {
	u1 tag;
	u2 offset;
	u2 length;
}TLV;

#define COS_MALLOC(size)				malloc(size)
#define COS_FREE(s)					free(s)
#define COS_MEMSET(buf, val, size)		memset(buf, val, size)
#define COS_MEMCPY(buf, val, size)		memcpy(buf, val, size)
#define COS_MEMCMP(buf1, buf2, len)	memcmp(buf1, buf2, len)
#define COS_STRLEN(s)				strlen(s)

#define DEBUG_LEVLE	1

#if DEBUG_LEVLE>=2
#define PRINT_FUNC_NAME()	{printf("Func: ");printf(__FUNCTION__);printf("\n");}
#define PRINT_FUNC_DONE()	{printf("Func: ");printf(__FUNCTION__);printf(" DONE\n");}
#define PRINT_STR(s)			{printf("%s\n", s);}
#define PRINTGG()			{PRINT_STR("########");}
#else
#define PRINT_FUNC_NAME()	{}
#define PRINT_FUNC_DONE()	{}
#define PRINT_STR(s)			{}
#define PRINTGG()			{}
#endif

extern TLV* tlv;

extern u1* aidString2Buffer(u1* aid, u1* aidlen);
extern void charString2ByteString(u1* charString, u1* desBuf, u2 offset);
extern u1 hexToDec(u1 c);

extern u1 getCLS(u1* apdu);
extern u1 getINS(u1* apdu);
extern u1 getP1(u1* apdu);
extern u1 getP2(u1* apdu);
extern u1 getP3(u1* apdu) ;
extern u1* getData(u1* apdu);
extern u2 getDataByte(u1* apduData);
extern u2 getDataShort(u1* apduData);

extern u2 getCurTLVTag();
extern u2 getCurTLVOff();
extern u2 getCurTLVLen();
extern u2 setCurTLVTag(u1 tag);
extern u2 setCurTLVOff(u2 off);
extern u2 setCurTLVLen(u2 len);
extern void appendTLByteV(u1* buffer, u1 tag, u1 val);
extern void appendTLShortV(u1* buffer, u1 tag, u2 val);
extern void appendTLBufferV(u1* buffer, u1 tag, u1* valBuf, u1 valOff, u1 valLen);

extern void showFS();
extern void showFileSystem(FileDesc* mf);
extern void showChildDFEF(FileList* fileList);
extern void printFileContent(u1* buff, u2 length);
extern void printAPDU(u1* apdu);
extern void printADF();

#endif

