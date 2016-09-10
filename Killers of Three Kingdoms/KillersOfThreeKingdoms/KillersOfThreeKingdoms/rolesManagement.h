#pragma once
#include "roles.h"
#include "json\json.h"

typedef class rolesManagement {
public:
	rolesManagement();
	uint32_t count();
	ROLESINFO * at(uint32_t index);
	~rolesManagement();
}ROLESMANAGEMENT;

