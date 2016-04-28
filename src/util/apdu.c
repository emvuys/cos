#include "../inc/types.h"

u1 getCLS(u1* apdu) {
	return *(apdu + OFFSET_CLS);
}

u1 getINS(u1* apdu) {
	return *(apdu + OFFSET_INS);
}

u1 getP1(u1* apdu) {
	return *(apdu + OFFSET_P1);
}

u1 getP2(u1* apdu) {
	return *(apdu + OFFSET_P2);
}

u1 getP3(u1* apdu) {
	return *(apdu + OFFSET_P3);
}

u1* getData(u1* apdu) {
	return apdu + OFFSET_DATA;
}

u2 getDataByte(u1* apduData) {
	return *(apduData);
}

u2 getDataShort(u1* apduData) {
	return ((*(apduData + OFFSET_DATA) << 8) & 0xFF00) | (*(apduData + OFFSET_DATA + 1) & 0xFF);
}
