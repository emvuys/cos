#include <stdio.h>

void processSelect(char* apdu);
void processManageChannel(char* apdu);

void dispatcher(char* apdu) {
    unsigned char ins = apdu[1];
	
	printf("dispatcher\n");

    switch(ins) {
        case 0xA4:
            processSelect(apdu);
            break;
        case 0x70:
            processManageChannel(apdu);
            break;
        default:
			printf("Unkown command\n");
            break;
    }
}


void processSelect(char* apdu){
	printf("processSelect\n");
}

void processManageChannel(char* apdu){
	printf("processManageChannel\n");
}

