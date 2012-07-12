#pragma once
#include "types.h"
#include "message.h"

const ct_t CT_POSITION = 0;
const ct_t CT_PHYSICS = 1;
const ct_t CT_RENDERABLE = 2;

namespace CTFlags
{
    const ct_t POSITION = 1 << CT_POSITION;
    const ct_t PHYSICS = 1 << CT_PHYSICS;
    const ct_t RENDERABLE = 1 << CT_RENDERABLE;
}


class ISystem
{
    public:
        virtual rsp_t handleMessage(Message) = 0;
        const ct_t id;
    protected:
        ISystem(ct_t id_):id(id_) {}
};
