#include "statusInfoManagement.h"
#include <fstream>

statusInfoManagement::statusInfoManagement() {

}

statusInfoManagement::~statusInfoManagement() {

}

uint32_t statusInfoManagement::count() {
	std::ifstream ifs;
	ifs.open("source/status.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)){
		return 0;
	}

	Json::Value status_value = root["status"];
	ifs.close();
	return status_value.size();
}

STATUSINFO * statusInfoManagement::at(uint32_t index) {
	std::ifstream ifs;
	ifs.open("source/status.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)) {
		ifs.close();
		return NULL;
	}

	Json::Value status_value = root["status"];
	STATUSINFO * statusInfo = new STATUSINFO;
	memset(statusInfo, 0, sizeof(statusInfo));

	for (uint32_t i = 0; i < status_value.size(); i++) {
		if (i == index){
			Json::Value temp_value = status_value[i];
			statusInfo->id = temp_value.isMember("id") ? temp_value["id"].asUInt() : 0;
			statusInfo->master = temp_value.isMember("master") ? temp_value["master"].asUInt() : 0;
			statusInfo->num = temp_value.isMember("num") ? temp_value["num"].asUInt() : 0;
			statusInfo->loyal = temp_value.isMember("loyal") ? temp_value["loyal"].asUInt() : 0;
			statusInfo->guilty = temp_value.isMember("guilty") ? temp_value["guilty"].asUInt() : 0;
			statusInfo->rebel = temp_value.isMember("rebel") ? temp_value["rebel"].asUInt() : 0;
			ifs.close();
			return statusInfo;
		}
	}
	ifs.close();
	return NULL;
}

STATUSINFO * statusInfoManagement::findCardByNum(uint16_t role_num) {
	std::ifstream ifs;
	ifs.open("source/status.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)) {
		ifs.close();
		return NULL;
	}

	Json::Value status_value = root["status"];
	STATUSINFO * statusInfo = new STATUSINFO;
	memset(statusInfo, 0, sizeof(statusInfo));

	for (uint32_t i = 0; i < status_value.size(); i++) {
		Json::Value temp_value = status_value[i];
		if (temp_value["num"].asUInt() == role_num) {
			statusInfo->id = temp_value.isMember("id") ? temp_value["id"].asUInt() : 0;
			statusInfo->master = temp_value.isMember("master") ? temp_value["master"].asUInt() : 0;
			statusInfo->num = role_num;
			statusInfo->loyal = temp_value.isMember("loyal") ? temp_value["loyal"].asUInt() : 0;
			statusInfo->guilty = temp_value.isMember("guilty") ? temp_value["guilty"].asUInt() : 0;
			statusInfo->rebel = temp_value.isMember("rebel") ? temp_value["rebel"].asUInt() : 0;
			ifs.close();
			return statusInfo;
		}
	}
	ifs.close();
	return NULL;
}


