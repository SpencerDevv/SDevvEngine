#include "Engine.h"
#include"RunService.h"

Engine::Engine() {
	services = new std::vector<Service*>();
	onRenderStepped = new std::vector<int>();

	SDL_Init(SDL_INIT_VIDEO);
	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, sizeX, sizeY, SDL_WINDOW_SHOWN);
	this->renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderPresent(renderer);

	initializeAllServices();
}

void Engine::initializeAllServices() {
	//LuaCppObject::Register<RunService>(L, true);
}

int Engine::new_lua_obj(lua_State* L)
{
	return make_lua_obj(L, new Engine);
}

void Engine::setTitle(std::string newTitle)
{
	this->title = newTitle;
	SDL_SetWindowTitle(window, title.c_str());
}

void Engine::setSize(int x, int y)
{
	this->sizeX = x;
	this->sizeY = y;
}

void Engine::fireCallbacks() {
	for (int i = 0; i < onRenderStepped->size(); i++) {
		int ref = onRenderStepped->at(i);

		lua_geti(L, ref, 1);
		STACKDUMP
	}
}

Engine::LuaInstanceMethod Engine::__getattr__(std::string& method_name)
{
	AttributeMap attr;
	attr["SetSize"] = _setSize_;
	attr["SetTitle"] = _setTitle_;
	attr["BindToRender"] = _bindToRender_;

	RETURN_ATTR_OR_CALL_SUPER(LuaCppObject);
}

int Engine::_bindToRender_(lua_State* L)
{
	Engine* self = checkarg<Engine>(L, 1);

	luaL_checktype(L, 2, LUA_TFUNCTION);
	lua_pushvalue(L, 1);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	self->onRenderStepped->push_back(ref);
	
	return 0;
}

int Engine::_setSize_(lua_State* L)
{
	Engine* self = checkarg<Engine>(L, 1);
	int x = luaL_checkinteger(L, 2);
	int y = luaL_checkinteger(L, 2);


	self->setSize(x, y);
	return 0;
}

int Engine::_setTitle_(lua_State* L)
{
	Engine* self = checkarg<Engine>(L, 1);
	const char* name = luaL_checkstring(L, 2);

	self->setTitle(name);
	return 0;
}

