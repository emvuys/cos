short processSelect(char* apdu, char* responseBuf, u2* responseLen);
void processManageChannel(char* apdu);
void dispatcher(char* apdu);

FileDesc* buildFileSystem();

int getAvailableChannel();
