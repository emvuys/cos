#ifndef __MULTICHANNEL_H__
#define __MULTICHANNEL_H__

#define CHANNEL_ID_MASK	(~0xFC)
#define CHANNEL_OPENNED	1
#define CHANNEL_CLOSED		0
#define CHANNEL_0			0
#define CHANNEL_1			1
#define CHANNEL_2			2
#define CHANNEL_3			3

#define INVALID_CHANNLE_ID	(u1)(-1)

#define CHANNEL_NUM		4

typedef struct ChannelInfo {
	u1 isOpen;
	FileDesc* curEF;
	FileDesc* curDF;
	FileDesc* curADF;
} ChannelInfo;

extern ChannelInfo channels[4];
extern u2 curChannelID;

extern void initChannel();
extern u4 getAvailableChannel();
extern u1 getCurChannelID() ;
extern void setCurChannelID(u1 cls);
extern ChannelInfo getChannelInfoFromChannelID(u1 channelID);
extern u1 isChannelIdOpen(u1 channelId);
extern void openChannelID(u1 channelId);
extern void closeChannelID(u1 channelId);

extern FileDesc* getMF();
extern FileDesc* getCurEF();
extern void setCurEF(FileDesc* pfile);
extern FileDesc* getCurDF();
extern void setCurDF(FileDesc* pfile);
extern void setCurDFonChn(FileDesc* pfile, u1 chn);
extern FileDesc* getCurADF();
extern void setCurADF(FileDesc* pfile);
extern void copyChannelInfo(u1 srcChn, u1 DesChn);
extern u1 getAvaibleChannlNum();

#endif
