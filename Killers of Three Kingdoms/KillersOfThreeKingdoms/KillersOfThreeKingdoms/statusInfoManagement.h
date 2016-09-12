#pragma once
#include "status.h"
#include "json\json.h"

typedef class statusInfoManagement {
public:
	statusInfoManagement();
	uint32_t count();
	STATUSINFO * at(uint32_t index);
	STATUSINFO * findCardByNum(uint16_t role_num);
	~statusInfoManagement();
}STATUSINFOMANAGEMENT;

