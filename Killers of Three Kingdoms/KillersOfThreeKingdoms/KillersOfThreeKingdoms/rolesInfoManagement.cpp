#include "rolesInfoManagement.h"
#include <fstream>

rolesInfoManagement::rolesInfoManagement() {

}

rolesInfoManagement::~rolesInfoManagement() {

}

uint32_t rolesInfoManagement::count() {
	std::ifstream ifs;
	ifs.open("source/roles.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)){
		return 0;
	}

	Json::Value cards_value = root["roles"];
	ifs.close();
	return cards_value.size();
}

ROLESINFO * rolesInfoManagement::at(uint32_t index) {
	std::ifstream ifs;
	ifs.open("source/roles.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)) {
		ifs.close();
		return NULL;
	}

	Json::Value cards_value = root["roles"];
	ROLESINFO * rolesInfo = new ROLESINFO;
	memset(rolesInfo, 0, sizeof(rolesInfo));
	rolesInfo->skill_num = 0;

	for (uint32_t i = 0; i < cards_value.size(); i++) {
		if (i == index){
			Json::Value temp_value = cards_value[i];
			rolesInfo->id = temp_value.isMember("id") ? temp_value["id"].asUInt() : 0;
			rolesInfo->identity = temp_value.isMember("identity") ? temp_value["identity"].asUInt() : 0;
			rolesInfo->name = temp_value.isMember("name") ? UTF8_To_string(temp_value["name"].asString().c_str()) : 0;
			rolesInfo->blood = temp_value.isMember("blood") ? temp_value["blood"].asUInt() : 0;
			rolesInfo->sex = temp_value.isMember("sex") ? temp_value["sex"].asBool() : 1;
			rolesInfo->power = temp_value.isMember("power") ? UTF8_To_string(temp_value["power"].asString().c_str()) : 0;

			if (temp_value.isMember("skill1")) {
				rolesInfo->skill[rolesInfo->skill_num++] = UTF8_To_string(temp_value["skill1"].asString().c_str());
			}

			if (temp_value.isMember("skill2")) {
				rolesInfo->skill[rolesInfo->skill_num++] = UTF8_To_string(temp_value["skill2"].asString().c_str());
			}
			ifs.close();
			return rolesInfo;
		}
	}
	ifs.close();
	return NULL;
}

ROLESINFO * rolesInfoManagement::findRoleById(uint32_t id) {
	std::ifstream ifs;
	ifs.open("source/roles.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)) {
		ifs.close();
		return NULL;
	}

	Json::Value cards_value = root["roles"];
	ROLESINFO * rolesInfo = new ROLESINFO;
	memset(rolesInfo, 0, sizeof(rolesInfo));
	rolesInfo->skill_num = 0;

	for (uint32_t i = 0; i < cards_value.size(); i++) {
		Json::Value temp_value = cards_value[i];
		if (id == temp_value["id"].asUInt()) {
			rolesInfo->id = id;
			rolesInfo->identity = temp_value.isMember("identity") ? temp_value["identity"].asUInt() : 0;
			rolesInfo->name = temp_value.isMember("name") ? UTF8_To_string(temp_value["name"].asString().c_str()) : 0;
			rolesInfo->blood = temp_value.isMember("blood") ? temp_value["blood"].asUInt() : 0;
			rolesInfo->power = temp_value.isMember("power") ? UTF8_To_string(temp_value["power"].asString().c_str()) : 0;

			if (temp_value.isMember("skill1")) {
				rolesInfo->skill[rolesInfo->skill_num++] = UTF8_To_string(temp_value["skill1"].asString().c_str());
			}

			if (temp_value.isMember("skill2")) {
				rolesInfo->skill[rolesInfo->skill_num++] = UTF8_To_string(temp_value["skill2"].asString().c_str());
			}
			ifs.close();
			return rolesInfo;
		}
	}
	ifs.close();
	return NULL;
}

ROLESINFO * rolesInfoManagement::findRoleByIdentity(uint16_t identity){
	std::ifstream ifs;
	ifs.open("source/roles.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)) {
		ifs.close();
		return NULL;
	}

	Json::Value cards_value = root["roles"];
	ROLESINFO * rolesInfo = new ROLESINFO;
	memset(rolesInfo, 0, sizeof(rolesInfo));
	rolesInfo->skill_num = 0;

	for (uint32_t i = 0; i < cards_value.size(); i++) {
		Json::Value temp_value = cards_value[i];
		if (identity == temp_value["identity"].asUInt()) {
			rolesInfo->id = temp_value.isMember("id") ? temp_value["id"].asUInt() : 0;
			rolesInfo->identity = temp_value.isMember("identity") ? temp_value["identity"].asUInt() : 0;
			rolesInfo->name = temp_value.isMember("name") ? UTF8_To_string(temp_value["name"].asString().c_str()) : 0;
			rolesInfo->blood = temp_value.isMember("blood") ? temp_value["blood"].asUInt() : 0;
			rolesInfo->power = temp_value.isMember("power") ? UTF8_To_string(temp_value["power"].asString().c_str()) : 0;

			if (temp_value.isMember("skill1")) {
				rolesInfo->skill[rolesInfo->skill_num++] = UTF8_To_string(temp_value["skill1"].asString().c_str());
			}

			if (temp_value.isMember("skill2")) {
				rolesInfo->skill[rolesInfo->skill_num++] = UTF8_To_string(temp_value["skill2"].asString().c_str());
			}
			ifs.close();
			return rolesInfo;
		}
	}
	ifs.close();
	return NULL;
}


