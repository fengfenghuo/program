#pragma once
#include "common.h"

typedef struct status_info {
	uint32_t id;
	uint16_t num;
	uint16_t master;
	uint16_t loyal;
	uint16_t guilty;
	uint16_t rebel;
}STATUSINFO;