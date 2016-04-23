#include <stdio.h>
#include <stdlib.h>
#include "../filesystem/filetype.h"
#include "../filesystem/fileSystem.h"
#include "../inc/types.h"

void dispatcher(char* apdu) {
	unsigned char ins = apdu[1];

	PRINT_FUNC_NAME();

	switch(ins) {
		case 0xA4:
			processSelect(apdu);
			break;
		case 0x70:
			processManageChannel(apdu);
			break;
		default:
			PRINT_STR("Unkown command");
			break;
	}
}


void processSelect(char* apdu){
	PRINT_FUNC_NAME();
}

void processManageChannel(char* apdu){
	PRINT_FUNC_NAME();
}

