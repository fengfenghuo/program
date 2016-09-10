#pragma once
#include "roles.h"
#include "json\json.h"

typedef class rolesInfoManagement {
public:
	rolesInfoManagement();
	uint32_t count();
	ROLESINFO * at(uint32_t index);
	ROLESINFO * findRoleById(uint32_t id);
	~rolesInfoManagement();
}ROLESINFOMANAGEMENT;

