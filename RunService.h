#pragma once
#include "Service.h"

class RunService : public Service
{
protected:
    virtual LuaInstanceMethod __getattr__(std::string& method_name)
    {
        AttributeMap attr;
        RETURN_ATTR_OR_CALL_SUPER(Service);
    }
public:
    static int new_lua_obj(lua_State* L)
    {
        return make_lua_obj(L, new RunService);
    }
};

