#pragma once

struct Message
{
	msg_t mType;
	eid_t entity;
	void* data;
};
