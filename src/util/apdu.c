#include "../inc/types.h"

APDU apduCommand;

u1 getCLS() {
	return apduCommand.cla;
}

u1 getINS() {
	return apduCommand.ins;
}

u1 getP1() {
	return apduCommand.p1;
}

u1 getP2() {
	return apduCommand.p2;
}

u1 getLc() {
	return apduCommand.lc;
}

u1 getLe() {
	return apduCommand.le & 0xFF;
}

u1* getData() {
	return apduCommand.data;
}

u2 getDataByte() {
	return *(getData());
}

u2 getDataShort() {
	return ((*(getData()) << 8) & 0xFF00) | (*(getData() + 1) & 0xFF);
}

