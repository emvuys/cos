#include "../inc/types.h"

void charString2ByteString(u1* charString, u1* desBuf, u2 offset, u1 flag) {
	u2 strlength, buflen, i;
	u1* buf;
	u1 left, right, space = 2;

	if (flag & STRING_SPACE) {
		space = 3;
	}
	
	strlength = COS_STRLEN(charString);
	if (strlength < space) {
		strlength = space;
	}
	buflen = (strlength + 1) / space;
	buf = COS_MALLOC(buflen);

	for (i = 0; i < strlength; i += space) {
		left = hexToDec(*(charString + i));
		right = hexToDec(*(charString + i + 1));
		if (flag & flag & STRING_WAPE) {
			buf[i /space] = (right << 4) + left;
		} else {
			buf[i /space] = (left << 4) + right;
		}
	}
	COS_MEMCPY(desBuf + offset, buf, buflen);
	COS_FREE(buf);
}

void convetPLMNs(u1* plmns, u1* desBuf, u1 spliter) {
	u1 len = COS_STRLEN(plmns), i, j, k, off = 0;
	u1 buf[6];
	for (i = 0; i < len;) {
		for (j = 0; j < 6; j ++) {
			if (plmns[i + j] == spliter) {
				break;
			}
		}
		if(j == 5) {
			COS_MEMCPY(buf, plmns + i, 3);
			buf[3] = 'F';
			COS_MEMCPY(buf + 3, plmns + i + 3, 2);
		} else if(j == 6) {
			COS_MEMCPY(buf, plmns + i, j);
		} else {
			return; // invalid mccmnc
		}
		charString2ByteString(buf, desBuf, off, STRING_WAPE);
		i += (j + 1);
	}
}

u1 hexToDec(u1 c) {
	if ('0' <= c && c <= '9') {
		return c - '0';
	}
	if ('A' <= c && c <= 'F') {
		return c - 'A' + 10;
	}
	if ('a' <= c && c <= 'f') {
		return c - 'a' + 10;
	}
	return -1;
}

u1* aidString2Buffer(u1* aid, u1* aidlen) {
	u1* buf, left, right, i;
	u1 strlength  = COS_STRLEN(aid);
	u1 buflen = strlength / 2;

	PRINT_FUNC_NAME();
	printf("aid[%s], len[%02X]\n", aid, buflen);
	
	buf = COS_MALLOC(buflen);

	for (i = 0; i < strlength; i += 2) {
		left = hexToDec(*(aid + i));
		right = hexToDec(*(aid + i + 1));
		buf[i /2] = (left << 4) + right;
	}
	*aidlen = buflen;
	return buf;
}

void printFileContent(FileDesc* file) {
	u2 i;
	u1* buff = file->data;
	u2 length = file->fileLen;

	//return;
	printf("Fid[%02X] ", file->fid);
	for (i = 0; i < length; i ++) {
		printf("%02X", *(buff + i));
	}
	printf("\n");
}

void printADF() {
	u1 len, index = 0, i = 0;
	
	len = aidFile[index].aidLen;
	printf("len[%02X], index[%d], aidMember: ", len, index);
	if (len != 0) {
		while (len --) {
			printf("%02X",  *(aidFile[index].aid + (i ++)));
		}
		i = 0;
	}
	
	index ++;
	len = aidFile[index].aidLen;
	printf("len[%02X], index[%d], aidMember: ", len, index);
	if (len != 0) {
		while (len --) {
			printf("%02X",  *(aidFile[index].aid + (i ++)));
		}
		i = 0;
	}
}

void printAPDU(u1* apdu) {
	u2 i = 0, p3 = getP3(apdu);
	
	printf("APDU< %02X%02X%02X%02X%02X", 
		getCLS(apdu),
		getINS(apdu),
		getP1(apdu),
		getP2(apdu),
		getP3(apdu)
		);

	while (p3 --) {
		printf("%02X",  *(apdu + OFFSET_DATA + (i ++)));
	}
	printf(" >\n");
}

void showFS() {
	showFileSystem(MFRef);
}

void showFileSystem(FileDesc* mf) {

	PRINT_FUNC_NAME();

	if (mf == INVALID_FILE) {
		PRINT_STR("MF is INVALID_FILE");
	}
	
	PRINTGG();
	if (mf->childDf != INVALID_FILE_LIST) {
		showChildDFEF(mf->childDf);
	} else {
		PRINT_STR("childDf is INVALID_FILE");
	}

	PRINTGG();

	if (mf->childEf != INVALID_FILE_LIST) {
		showChildDFEF(mf->childEf);
	} else {
		PRINT_STR("childEf is INVALID_FILE");
	}

	PRINTGG();

}

void showChildDFEF(FileList* fileList) {
	FileDesc* pFile;
	FileList* pListNode = fileList;

	PRINT_FUNC_NAME();
	
	while (pListNode != INVALID_FILE_LIST) {
		pFile = pListNode->me;
		printf("fid: 0x%2X, type: %d, ", pFile->fid, pFile->filetype);
		if (pFile->parent != INVALID_FILE) {
			printf("parentfid: 0x%2X, type: %d\n", pFile->parent->fid, pFile->parent->filetype);
		} else {
			printf("parent is INVALID_FILE\n");
		}
		if ((pListNode->me->filetype == DF) || (pListNode->me->filetype == ADF)) {
			if (pListNode->me->childDf != INVALID_FILE_LIST) {
				showChildDFEF(pListNode->me->childDf);
			}
			if (pListNode->me->childEf != INVALID_FILE_LIST) {
				showChildDFEF(pListNode->me->childEf);
			}
		}
		pListNode = pListNode->next;
	}
}

