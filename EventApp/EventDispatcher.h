#pragma once
#include <functional>
#include <vector>
#include <map>

class EventDispatcher
{
public:
	static const char* EVENT_1;
	static const char* EVENT_2;
	size_t getHash(const std::string& in_str);
	size_t getHash(const char* in_str);

private:
	struct Command
	{
		std::function<void(size_t)> func = {};
		intptr_t* ptr = nullptr;
	};

	EventDispatcher();
	~EventDispatcher();
	EventDispatcher* operator=(EventDispatcher&) = delete;
	EventDispatcher(EventDispatcher&) = delete;
	static EventDispatcher* _instance;
	static std::map < size_t, std::vector<Command> > _event_map;

public:
	static EventDispatcher* getInstance();
	static void releaseInstance();

	template<typename T>
	void addEventListener(std::function<void(size_t)> func, T*ptr, const char* event_name);
	template<typename T>
	void removeEventListener(T*ptr);
	void dispatch(const char* event, size_t arg);
};

template<typename T>
void EventDispatcher::addEventListener(std::function<void(size_t)> func, T*ptr, const char* event_name)
{
	Command listener;
	listener.func = func;
	listener.ptr = reinterpret_cast<intptr_t*>(ptr);
	size_t hash = getHash(event_name);
	auto find_it = _event_map.find(hash);
	if (find_it != _event_map.end())
	{
		std::vector<Command> command_list;
		command_list.push_back(listener);
		_event_map[hash] = command_list;
	}
	else
	{
		_event_map[hash].push_back(listener);
	}
}

template<typename T>
void EventDispatcher::removeEventListener(T*ptr)
{

}

