#pragma once

#include <string>
#include <exception>

void checkGLErrors(const char* functionName);
int init();

struct TrolloException : public std::exception
{
	std::string msg;
	TrolloException(const char* msg_) : msg(msg_) {}
	
	virtual const char* what() const throw() { return msg.c_str(); }
	virtual ~TrolloException() throw() {}
};
