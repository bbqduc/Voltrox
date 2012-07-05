#include "error.h"

std::string TROLLOErrorString(TROLLOERROR e)
{
	switch(e)
	{
		case TROLLO_OK:
			return std::string("No error");
		case TROLLO_FILE_NOT_FOUND:
			return std::string("File not found");
		case TROLLO_INVALID_FILE_FORMAT:
			return std::string("Invalid file format");
		case TROLLO_INIT_FAILURE:
			return std::string("System init failure");
		default:
			return std::string("Unknown error code");
	}
}