#include "common.h"
#include <string>
#include <cstdlib>
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

int strToInt(string source) {
	int num = -1;

	size_t source_len = source.length();
	
	for (size_t i = 0; i < source_len; i++) {
		if (source[i] >= '0' && source[i] <= '9') {
			if (num == -1) {
				num = 0;
			}
			num = num * 10 + source[i] - '0';
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

string viewCardColor(int point, uint16_t color) {
	string card_color;
	char buff[16];
	switch (color)
	{
	case CARDS_COLOR_SPADE:
		card_color = "黑桃  ";
		break;
	case CARDS_COLOR_PLUM:
		card_color = "梅花  ";
		break;
	case CARDS_COLOR_HEART:
		card_color = "红桃  ";
		break;
	case CARDS_COLOR_DIAMOND:
		card_color = "方块  ";
		break;
	default:
		card_color = "花色有误";
		break;
	}

	switch (point)
	{
	case 1:
		strncpy_s(buff, "A", sizeof(char));
		break;
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		_itoa_s(point, buff, 10);
		break;
	case 11:
		strncpy_s(buff, "J", sizeof("J"));
		break;
	case 12:
		strncpy_s(buff, "Q", sizeof("Q"));
		break;
	case 13:
		strncpy_s(buff, "K", sizeof("K"));
		break;
	default:
		strncpy_s(buff, "点数有误", sizeof("点数有误"));
		break;
	}
	card_color += buff;
	return card_color;
}

string viewRoleStatus(uint16_t status) {
	string card_status;

	switch (status)
	{
	case STATUS_MASTER:
		card_status = "主公  ";
		break;
	case STATUS_LOYAL:
		card_status = "忠臣  ";
		break;
	case STATUS_GUILTY:
		card_status = "内奸  ";
		break;
	case STATUS_REBEL:
		card_status = "反贼  ";
		break;
	default:
		card_status = "身份有误";
		return card_status;
	}
	return card_status;
}