#include "common.h"
#include <string>
#include <windows.h>

uint16_t strToArray(const char *source, uint16_t *array) {
	uint16_t num = 0;
	if (source == NULL) return 0;

	size_t source_len = strlen(source);
	uint16_t point = 0;

	for (size_t i = 0; i < source_len; i++) {
		if (source[i] >= '0' && source[i] <= '9') {
			point = point * 10 + source[i] - '0';
		}
		if ((source[i] == ',' || i+1 == source_len) && point != 0) {
			array[num++] = point;
			point = 0;
		}
	}

	return num;
}

std::string UTF8_To_string(const std::string & str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴
	memset(pwBuf, 0, nwLen * 2 + 2);

	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

	char * pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);

	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string retStr = pBuf;

	delete[]pBuf;
	delete[]pwBuf;

	pBuf = NULL;
	pwBuf = NULL;

	return retStr;
}