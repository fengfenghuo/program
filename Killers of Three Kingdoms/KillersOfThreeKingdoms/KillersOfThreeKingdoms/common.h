#pragma once

#include <iostream>
using namespace std;

#define CARDS_NUM 16
#define CARDS_NAME 16
#define CARDS_DESC 256

uint8_t strToArray(const char *source, uint8_t *array);

std::string UTF8_To_string(const std::string & str);