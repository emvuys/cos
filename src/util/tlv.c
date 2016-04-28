#include "../inc/types.h"

TLV* tlv;

u2 getCurTLVTag() {
	return tlv->tag;
}

u2 getCurTLVOff() {
	return tlv->offset;
}

u2 getCurTLVLen() {
	return tlv->length;
}

u2 setCurTLVTag(u1 tag) {
	tlv->tag = tag;
}

u2 setCurTLVOff(u2 off) {
	tlv->offset = off;
}

u2 setCurTLVLen(u2 len) {
	tlv->length = len;
}

void appendTLByteV(u1* buffer, u1 tag, u1 val){
	u2 currLen = getCurTLVLen(), currOff = getCurTLVOff(tag);
	currLen += 3;
	buffer[currOff ++] = tag;
	buffer[currOff ++] = 1;
	buffer[currOff ++] = val;
	setCurTLVLen(currLen);
	setCurTLVOff(currOff);
}

void appendTLShortV(u1* buffer, u1 tag, u2 val){
	u2 currLen = getCurTLVLen(), currOff = getCurTLVOff(tag);
	currLen += 4;
	buffer[currOff ++] = tag;
	buffer[currOff ++] = 2;
	buffer[currOff ++] = val >> 8;
	buffer[currOff ++] = val & 0xFF;
	setCurTLVLen(currLen);
	setCurTLVOff(currOff);
}

void appendTLBufferV(u1* buffer, u1 tag, u1* valBuf, u1 valOff, u1 valLen){
	u2 currLen = getCurTLVLen(), currOff = getCurTLVOff(tag);
	currLen += (valLen + 2);
	buffer[currOff ++] = tag;
	buffer[currOff ++] = valLen;
	COS_MEMCPY(buffer + currOff, valBuf + valOff, valLen);
	currOff += valLen;
	setCurTLVLen(currLen);
	setCurTLVOff(currOff);
}

