#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#ifndef __TYPES_H__
#define __TYPES_H__

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef u1 s1;
typedef short s2;
typedef int s4;

#define RETURN_OK		0
#define RETURN_ERR		1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include <Android/log.h>

#include "../filesystem/file.h"
#include "../util/util.h"
#include "../multichannel/multiChannel.h"
#include "../commandprocess/dispatcher.h"
#include "../filesystem/fileSystem.h"
#include "../authenticate/auth.h"

#endif

