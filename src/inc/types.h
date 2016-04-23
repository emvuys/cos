#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef char s1;
typedef short s2;
typedef int s4;


#define COS_MALLOC(size)			malloc(size)
#define COS_MEMSET(buf, val, size)	memset(buf, val, size)
#define COS_MEMCPY(buf, val, size)	memcpy(buf, val, size)


#define DEBUG_LEVLE	1

#if DEBUG_LEVLE==1
#define DEBUG_LEVEL1
#elif  DEBUG_LEVLE==2
#define DEBUG_LEVEL2
#endif

#ifdef DEBUG_LEVEL2
#defile DEBUG_LEVEL1
#endif



#ifdef DEBUG_LEVEL2
#define PRINT_FUNC_NAME()	{printf("Func: ");printf(__FUNCTION__);printf("\n");}
#define PRINT_STR(s)			{printf("%s\n", s);}
#define PRINTGG()			{PRINT_STR("########");}
#else
#define PRINT_FUNC_NAME()	{}
#define PRINT_STR(s)			{}
#define PRINTGG()			{}
#endif



