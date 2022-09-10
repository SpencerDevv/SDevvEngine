#pragma once
#include "LuaCppObject.h"

class Service : public LuaCppObject {
private:
	std::string name;
public:
	Service(): name("NoName") {};
	virtual ~Service() { }

	void set_name(std::string ns) { name = ns; }
	std::string get_name() { return name; }
protected:
	virtual LuaInstanceMethod __getattr__(std::string& method_name) {
		AttributeMap attr;
		attr["GetName"] = _getName_;

		RETURN_ATTR_OR_CALL_SUPER(LuaCppObject)
	}

	static int _getName_(lua_State* L) {
		Service* self = checkarg<Service>(L, 1);
		lua_pushstring(L, self->get_name().c_str());
		return 1;
	}
};