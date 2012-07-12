#pragma once

const msg_t ADD = 0;
const msg_t REMOVE = 1;
const msg_t PHYS_ADD_LINK = 2;
const msg_t LAST_BASE_MSG = 2;

const rsp_t MSG_DONE = 0;
const rsp_t MSG_IGNORED = 1;
const rsp_t LAST_BASE_RSP = 1;

struct Message
{
	msg_t mType;
	eid_t entity;
	void* data;
};