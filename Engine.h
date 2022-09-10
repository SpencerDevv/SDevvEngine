#pragma once
#include <SDL.h>
#include "LuaCppObject.h"
#include "Service.h"
#include <vector>

class Engine : public LuaCppObject {
private:
	std::string title = "SDevv Engine";
	int sizeX = 600;
	int sizeY = 600;

	SDL_Window* window;
	SDL_Renderer* renderer;
	std::vector<int>* onRenderStepped;

	std::vector<Service*>* services;

	bool running = false;
public:
	Engine();

	static int new_lua_obj(lua_State* L);

	void initializeAllServices();
	void fireCallbacks();
	void setTitle(std::string newTitle);
	void setSize(int x, int y);
protected:
	virtual LuaInstanceMethod __getattr__(std::string& method_name);
	static int _setSize_(lua_State* L);
	static int _setTitle_(lua_State* L);
	static int _bindToRender_(lua_State* L);
};