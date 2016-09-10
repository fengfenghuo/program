#include "cardsInfoManagement.h"
#include <fstream>

cardsInfoManagement::cardsInfoManagement() {

}

cardsInfoManagement::~cardsInfoManagement() {

}

uint32_t cardsInfoManagement::count() {
	std::ifstream ifs;
	ifs.open("source/cards.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)){
		return 0;
	}

	Json::Value cards_value = root["cards"];
	ifs.close();
	return cards_value.size();
}

CARDSINFO * cardsInfoManagement::at(uint32_t index) {
	std::ifstream ifs;
	ifs.open("source/cards.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)) {
		ifs.close();
		return NULL;
	}

	Json::Value cards_value = root["cards"];
	CARDSINFO * cardsInfo = new CARDSINFO;
	memset(cardsInfo, 0, sizeof(cardsInfo));

	for (uint32_t i = 0; i < cards_value.size(); i++) {
		if (i == index){
			Json::Value temp_value = cards_value[i];
			cardsInfo->category = temp_value["category"].asUInt();
			cardsInfo->id = temp_value["id"].asUInt();
			//cardsInfo->spade_num = strToArray(temp_value["spade"].asCString(), cardsInfo->spade);
			//cardsInfo->plum_num = strToArray(temp_value["plum"].asCString(), cardsInfo->plum);
			//cardsInfo->heart_num = strToArray(temp_value["heart"].asCString(), cardsInfo->heart);
			//cardsInfo->diamond_num = strToArray(temp_value["diamond"].asCString(), cardsInfo->diamond);
			cardsInfo->hurt = temp_value["hurt"].asUInt();
			cardsInfo->recover = temp_value["recover"].asUInt();
			cardsInfo->range = temp_value["range"].asUInt();
			cardsInfo->distance = temp_value["distance"].asInt();
			cardsInfo->type = temp_value["type"].asUInt();
			cardsInfo->name = UTF8_To_string(temp_value["name"].asString().c_str());
			cardsInfo->desc = UTF8_To_string(temp_value["desc"].asString().c_str());
			ifs.close();
			return cardsInfo;
		}
	}
	ifs.close();
	return NULL;
}

CARDSINFO * cardsInfoManagement::findCardById(uint32_t id) {
	std::ifstream ifs;
	ifs.open("source/cards.json");

	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(ifs, root, false)) {
		ifs.close();
		return NULL;
	}

	Json::Value cards_value = root["cards"];
	CARDSINFO * cardsInfo = new CARDSINFO;
	memset(cardsInfo, 0, sizeof(cardsInfo));

	for (uint32_t i = 0; i < cards_value.size(); i++) {
		Json::Value temp_value = cards_value[i];
		if (id == temp_value["id"].asUInt()) {
			cardsInfo->category = temp_value["category"].asUInt();
			cardsInfo->id = temp_value["id"].asUInt();
			//cardsInfo->spade_num = strToArray(temp_value["spade"].asCString(), cardsInfo->spade);
			//cardsInfo->plum_num = strToArray(temp_value["plum"].asCString(), cardsInfo->plum);
			//cardsInfo->heart_num = strToArray(temp_value["heart"].asCString(), cardsInfo->heart);
			//cardsInfo->diamond_num = strToArray(temp_value["diamond"].asCString(), cardsInfo->diamond);
			cardsInfo->hurt = temp_value["hurt"].asUInt();
			cardsInfo->recover = temp_value["recover"].asUInt();
			cardsInfo->range = temp_value["range"].asUInt();
			cardsInfo->distance = temp_value["distance"].asInt();
			cardsInfo->type = temp_value["type"].asUInt();
			cardsInfo->name = UTF8_To_string(temp_value["name"].asString().c_str());
			cardsInfo->desc = UTF8_To_string(temp_value["desc"].asString().c_str());
			ifs.close();
			return cardsInfo;
		}
	}
	ifs.close();
	return NULL;
}


