#include "../inc/types.h"


ChannelInfo channels[CHANNEL_NUM];
u2 curChannelID = 0xFF;

void initChannel() {
	u1 i;
	
	for (i = 0; i < 4; i ++) {
		closeChannelID(i);
		channels[i].curEF = INVALID_FILE;
		channels[i].curDF = INVALID_FILE;
		channels[i].curADF = INVALID_FILE;
	}
	openChannelID(CHANNEL_0);
	setCurChannelID(CHANNEL_0);
	setCurDF(MFRef);
}

u4 getAvailableChannel() {
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

void setCurDFonChn(FileDesc* pfile, u1 chn) {
	channels[chn].curDF = pfile;
}

FileDesc* getCurADF() {
	return channels[getCurChannelID()].curADF;
}

void setCurADF(FileDesc* pfile) {
	channels[getCurChannelID()].curADF = pfile;
}

u1 getAvaibleChannlNum() {
	u1 i;
	while (i ++ < CHANNEL_NUM) {
		printf("chn[%02d], status[%02d]\n", i -1, isChannelIdOpen(i - 1));
		if (isChannelIdOpen(i - 1)) {
			continue;
		} else {
			break;
		}
	}
	if (i == CHANNEL_NUM) {
		return INVALID_CHANNLE_ID;
	} else {
		return (i - 1);
	}
}

void copyChannelInfo(u1 srcChn, u1 desChn) {
	channels[desChn].isOpen = channels[srcChn].isOpen;
	channels[desChn].curEF = channels[srcChn].curEF;
	channels[desChn].curDF = channels[srcChn].curDF;
	channels[desChn].curADF = channels[srcChn].curADF;
}

