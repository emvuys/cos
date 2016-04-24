#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef char s1;
typedef short s2;
typedef int s4;


#define COS_MALLOC(size)			malloc(size)
#define COS_FREE(s)				free(s)
#define COS_MEMSET(buf, val, size)	memset(buf, val, size)
#define COS_MEMCPY(buf, val, size)	memcpy(buf, val, size)
#define COS_STRLEN(s)			strlen(s)


#define DEBUG_LEVLE	1



#if DEBUG_LEVLE==2
#define PRINT_FUNC_NAME()	{printf("Func: ");printf(__FUNCTION__);printf("\n");}
#define PRINT_STR(s)			{printf("%s\n", s);}
#define PRINTGG()			{PRINT_STR("########");}
#else
#define PRINT_FUNC_NAME()	{}
#define PRINT_STR(s)			{}
#define PRINTGG()			{}
#endif


#define CHANNEL_ID_MASK	0xFC
#define CHANNEL_OPENNED	1
#define CHANNEL_CLOSED		0
#define CHANNEL_0			0
#define CHANNEL_1			1
#define CHANNEL_2			2
#define CHANNEL_3			3



