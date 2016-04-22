void processSelect(char* apdu);
void processManageChannel(char* apdu);
void dispatcher(char* apdu);

char* buildFileSystem();

int getAvailableChannel();
