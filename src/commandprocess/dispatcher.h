short processSelect(u1* apdu, u1* responseBuf, u2* responseLen);

short processManageChannel(u1* apdu, u1* responseBuf, u2* responseLen);
void dispatcher(u1* apdu);

FileDesc* buildFileSystem();

int getAvailableChannel();
