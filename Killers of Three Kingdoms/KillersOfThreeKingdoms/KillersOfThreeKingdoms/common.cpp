#include "common.h"
#include <string>

uint8_t strToArray(const char *source, char *array) {
	uint8_t num = 0;
	if (source == NULL) return 0;

	size_t source_len = strlen(source);

	for (size_t i = 0, j = 0; i < source_len; i++) {
		if (source[i] > '0' && source[i] <= '9' || source[i] >= 'A' && source[i] <= 'Z' || source[i] >= 'a' && source[i] <= 'z') {
			if (source[i] == '1') {
				array[num++] = 10;
			}
			else {
				array[num++] = source[i];
			}
		}
	}

	return num;
}