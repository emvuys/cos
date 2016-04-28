#ifndef __DISPATCH_H__
#define __DISPATCH_H__

typedef enum INS{
	INS_SELECT = 0xA4,
	INS_STATUS = 0xF2,
	INS_VERIFY_PIN = 0x20,
	INS_UNBLOCK_PIN = 0x2C,
	INS_MANAGE_CHANNEL = 0x70,
	INS_READ_BINARY = 0xB0,
	INS_UPDATE_BINARY = 0xD6,
	INS_READ_RECORD = 0xB2,
	INS_UPDATE_RECORD = 0xDC,
	INS_GET_DATA = 0xCA,
	INS_STORE_DATA = 0xE2,
	INS_AUTHENTICATE = 0x88
} INS;

enum ErrorCode {
	NONE = 0x9000,
	UNKNOWN = 0x6F00,

	WRONG_LENGTH = 0x6700,
	INVALID_CLA = 0x6E00,
	INVALID_INS = 0x6D00,
	LOGICAL_CHANNEL_NOT_SUPPORTED = 0x6881,
	SECURE_MESSAGE_NOT_SUPPORTED = 0x6882,

	WRONG_PARAMS = 0x6A86,
	WRONG_DATA = 0x6A80,
	FILE_NOT_FOUND = 0x6A82,
	RECORD_NOT_FOUND = 0x6A83,

	SECURITY_NOT_SATISFIED = 0x6982,
	PIN_BLOCKED = 0x6983,
	NO_FILE_SELECTED = 0x6986,

	VERYFY_PIN_RETRY_LEFT_TIME = 0x6C03,
	UNBLOCK_PIN_RETRY_LEFT_TIME = 0x6C0A,

	AUTH_INCORRECT_MAC = 0x9862,
	AUTH_CONTEXT_NOT_SUPPORTED = 0x9864
} ErrorCode;

extern void insertCard(	u1* imsi,
						u1* ki,
						u1* opc,
						u1* iccid,
						u1* acc,
						u1* spn,
						u1* apn,
						u1* hplmn,
						u1* ehplmn,
						u1* loci,
						u1* psloci,
						u1* fplmn );
extern short processSelect(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processStatus(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processVerifyPIN(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processUnBlockPIN(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processManageChannel(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processReadBin(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processUpdateBin(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processReadRecord(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processUpdateRecord(u1* apdu, u1* responseBuf, u2* responseLen);
extern short processAuth(u1* apdu, u1* responseBuf, u2* responseLen);

extern FileDesc* selectChild(FileDesc* df, u2 fid);
extern FileDesc* selectChildDf(FileDesc* df, u2 fid);
extern FileDesc* selectChildEf(FileDesc* df, u2 fid);
extern FileDesc* selectFId(u2 fid);
extern FileDesc* selectBySfi(u1 fid);
extern FileDesc* selectParentDf(u2 fid);
extern FileDesc* selectbyAID(u1* aidBuf, u1 len, u1 terminal);
extern FileDesc* selectByPath(FileDesc* df, u1* fidPath, u1 len);
extern FileDesc* selectByPathFromMf(u1* fidPath, u1 len);
extern FileDesc* selectByPathFromCurrentDf(u1* fidPath, u1 len);
extern FileDesc* selectChildSfi(FileDesc* df, u1 sfi);
extern FileDesc* selectChildDfSfi(FileDesc* df, u1 sfi);
extern FileDesc* selectChildEfSfi(FileDesc* df, u1 sfi);
extern u1 openChannel(u1 srcChnId);
extern u1 closeChannel(u1 sChnId);
extern short updateBinary(FileDesc* file, u2 offset, u1* data, u1 len);
extern short readBinary(FileDesc* file, u2 offset, u2 size, u1* responseBuf, u2* responseLen);
extern void readNextRecord(FileDesc* file, u1* responseBuf);
extern void readPreviousRecord(FileDesc* file, u1* responseBuf);
extern void readRecordAbs(FileDesc* file, u1 recordNum, u1* responseBuf);
extern void updateNextRecord(FileDesc* file, u1* apduData);
extern void updatePreviousRecord(FileDesc* file, u1* apduData);
extern void updateRecordAbs(FileDesc* file, u1 recordNum, u1* apduData);

#endif
