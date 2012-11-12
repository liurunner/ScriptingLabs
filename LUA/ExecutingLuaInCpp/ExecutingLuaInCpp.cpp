// ExecutingLuaInCpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>

#pragma comment (lib, "lua5.1.lib")
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

int health = 100;

int set_health(lua_State *L)
{
	//gets the number of arguments entered in lua
	int args = lua_gettop(L);

	//We want atleast one argument as it'll be used to set our healths value
	if(args >= 1)
	{
		//Make sure that it's a number that we've entered
		if(lua_isnumber(L, -args))
		{
			health = lua_tonumber(L, -args);
		}
	}
	return 0;
}
int get_health(lua_State *L)
{
	//Feed the health value to lua
	lua_pushnumber(L, health);

	return 1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//Create an start our enviroment
	lua_State * L = lua_open();

	//Load libs
	luaL_openlibs(L);
	lua_register(L, "set_health", set_health);
	lua_register(L, "get_health", get_health);

	luaL_dostring(L, "print(\"Hello from Lua!\")");
	luaL_dofile(L, "Test.lua");

	lua_getglobal(L, "s");
	std::string str = lua_tostring(L, -1);
	std::cout << "S is a string: " << str.c_str() << std::endl;

	lua_getglobal(L, "x");
	if(lua_isnumber(L, lua_gettop(L)))
	{
		int x = lua_tonumber(L, lua_gettop(L));
		std::cout << "X is a number: " << x << std::endl;
	}
	else 
	{
		std::cout << "X is not a number!" << std::endl;
	}


	luaL_dofile(L, "TestFunc.lua");

	std::cout << health << std::endl;

	//Close our enviroment
	lua_close(L);

	//Get a character
	std::cin.get();

	//Return the integer 0 for no errors
	return 0;
}

