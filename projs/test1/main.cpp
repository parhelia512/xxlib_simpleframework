#include "xx_luahelper.h"
#include <iostream>
#ifdef _WIN32
#include <Windows.h>	// Sleep
#include <mmsystem.h>	// timeBeginPeriod at winmm.lib
#pragma comment(lib, "winmm.lib") 
#endif

#include "scene.h"
#include "fsmlua.h"
#include "monster.h"

typedef xx::MemPool<
	FSMLua,
	Scene,
	MonsterBase,
	Monster1,
	Monster2,
	SceneBase,
	SceneObjBase,
	xx::List<FSMBase*>,
	xx::List<SceneObjBase*, true>,
	xx::String
> MP;

#include "scene.hpp"
#include "fsmlua.hpp"
#include "monster.hpp"

int main()
{
	MP mp;
	auto scene = mp.Create<Scene>(R"##(
local self = scene
for i = 1, 5 do
	local s = os.clock()
	for j = 1, 450000 do
		local m = self:CreateMonster2()
		self:Release( m )
	end
	local e = os.clock()
	print( "self:ticks() = ".. self:ticks() .. ", elapsed sec = "..(e-s) )
	coroutine.yield()
end
)##");
	auto rtv = scene->Run();
	if (rtv)
	{
		std::cout << "err code = " << rtv << ", err msg = " << scene->err->C_str() << std::endl;
	}
	mp.Release(scene);
	return rtv;
}


/*

for j = 1, 100 do
	for i = 1, 100000 do
		self:CreateMonster1( [[
			--print( "m]]..i..[[ created" )
			--for i = 1, 5 do
				--coroutine.yield()
			--end
			--print( "m]]..i..[[ dead" )
		]] )
	end
	print( "lua print: self:ticks() = ", self:ticks() )
	coroutine.yield()
end

*/