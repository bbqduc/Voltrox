#pragma once

#include <string>

void checkGLErrors(const char* functionName);
int init();

enum TROLLOERROR {TROLLO_OK, TROLLO_FILE_NOT_FOUND, TROLLO_INIT_FAILURE, TROLLO_INVALID_FILE_FORMAT};


std::string TROLLOErrorString(TROLLOERROR e);
