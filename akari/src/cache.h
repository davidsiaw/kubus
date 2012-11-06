#ifndef CACHE_H
#define CACHE_H

#include <map>
#include <functional>
template<typename T>
class cache
{
	std::map<std::string, T> store;
public:
	cache()
	{}

	T get(std::string identifier, std::function<T()> loader)
	{
		if (store.find(identifier) == store.end())
		{
			store[identifier] = loader();
		}
		return store[identifier];
	}

};

#endif // CACHE_H
