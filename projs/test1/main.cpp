#include "xx_mempool.h"
#include "xx_list.h"
#include "xx_dict.h"
#include <iostream>

using namespace xx;

struct A;
struct B;
typedef MemPool<
	A, 
	B, 
	List<A*>,
	Dict<String*, A*, true>,
	String
> MP;

struct A : MPObject 
{
	virtual void ToString(String &str) const override
	{
		str.Append("a");
	}

};
struct B : MPObject
{
	A* a;
	B()
	{
		mempool<MP>().CreateTo(a);
	}
	~B()
	{
		a->Release();
	}
	virtual void ToString(String &str) const override
	{
		str.Append("b");
	}
};

void Dump(MP& mp, MPObject* o)
{
	auto s = mp.Create<String>();
	o->ToString(*s);
	std::cout << s->C_str() << std::endl;
	s->Release();
}

int main()
{
	MP mp;
	auto b = mp.Create<B>();
	b->Release();

	auto list = mp.Create<List<A*>>();
	list->Add(mp.Create<A>());
	list->Add(mp.Create<A>());
	list->Add(mp.Create<A>());
	list->Add(mp.Create<A>());

	Dump(mp, list);

	auto dict = mp.Create<Dict<String*, A*, true>>();
	auto key = mp.Create<String>("asdf");
	auto val = mp.Create<A>();
	auto result = dict->Add(key, val, false);
	key->Release();

	return 0;
}
