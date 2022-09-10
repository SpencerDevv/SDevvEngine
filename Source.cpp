#include "Lua/lua.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <string>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <windows.h>
#include <new>

#include "LuaCppObject.h"
#include "Engine.h"

#undef main;

std::string getSourceOfFile(const char* name) {
	std::string LUA_FILE;

	std::ifstream myFile(name);
	if (myFile.good()) {
		while (myFile.good()) {
			std::string line;
			std::getline(myFile, line);

			if (!LUA_FILE.empty())
				LUA_FILE += "\n";
			LUA_FILE += line;
		}

		myFile.close();
	}
	else {
		std::cout << "Unable to open file\n";
		return "";
	};

	return LUA_FILE;
}

int main(int argc, char** argv) {
	lua_State* L = luaL_newstate();
	luaopen_base(L);
	luaL_requiref(L, LUA_TABLIBNAME, luaopen_table, 1);
	lua_pop(L, 1);
	luaL_requiref(L, LUA_STRLIBNAME, luaopen_string, 1);
	lua_pop(L, 1);
	luaL_requiref(L, LUA_COLIBNAME, luaopen_coroutine, 1);
	lua_pop(L, 1);
	luaL_requiref(L, LUA_OSLIBNAME, luaopen_os, 1);
	lua_pop(L, 1);

	LuaCppObject::Init(L);
	LuaCppObject::Register<Engine>(L, true);

	int r = luaL_dostring(L, getSourceOfFile("Source.lua").c_str());
	if (r != LUA_OK) {
		const char* errorMessage = lua_tostring(L, -1);
		std::cout << "Lua Fatal Error: " << errorMessage << std::endl;
	}

	lua_close(L);
	system("pause");
	return 0;
}