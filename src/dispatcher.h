void processSelect(char* apdu);
void processManageChannel(char* apdu);
void dispatcher(char* apdu);

FileDesc* buildFileSystem();

int getAvailableChannel();
