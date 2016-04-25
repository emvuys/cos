#include <stdio.h>
#include <stdlib.h>
#include "../filesystem/filetype.h"
#include "../filesystem/fileSystem.h"
#include "../inc/types.h"



ChannelInfo channels[4];
u2 curChannelID = 0xFF;

void initChannel() {
	u1 i;
	
	for(i = 0; i < 4; i ++) {
		closeChannelID(i);
		channels[i].curEF = INVALID_FILE;
		channels[i].curDF = INVALID_FILE;
		channels[i].curADF = INVALID_FILE;
	}
	
	openChannelID(CHANNEL_0);
	setCurChannelID(CHANNEL_0);
	setCurDF(MFRef);
}

int getAvailableChannel(){
    return 1;
}

u1 getCurChannelID() {
	return curChannelID;
}

void setCurChannelID(u1 cls) {
	curChannelID = cls & CHANNEL_ID_MASK;
}

ChannelInfo getChannelInfoFromChannelID(u1 channelID) {
	return channels[curChannelID];
}

u1 isChannelIdOpen(u1 channelId) {
	return channels[channelId].isOpen == CHANNEL_OPENNED;
}
void openChannelID(u1 channelId) {
	channels[channelId].isOpen = CHANNEL_OPENNED;
}
void closeChannelID(u1 channelId) {
	channels[channelId].isOpen = CHANNEL_CLOSED;
}
FileDesc* getMF() {
	return MFRef;
}
FileDesc* getCurEF() {
	return channels[getCurChannelID()].curEF;
}
void setCurEF(FileDesc* pfile) {
	channels[getCurChannelID()].curEF = pfile;
}
FileDesc* getCurDF() {
	return channels[getCurChannelID()].curDF;
}
void setCurDF(FileDesc* pfile) {
	channels[getCurChannelID()].curDF = pfile;
}
FileDesc* getCurADF() {
	return channels[getCurChannelID()].curADF;
}
void setCurADF(FileDesc* pfile) {
	channels[getCurChannelID()].curADF = pfile;
}


