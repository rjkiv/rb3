#pragma once
#include "obj/Object.h"

class NetSync : public Hmx::Object {
public:
    NetSync();
    virtual ~NetSync();
    virtual DataNode Handle(DataArray*, bool);
};

extern NetSync* TheNetSync;