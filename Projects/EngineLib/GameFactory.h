#pragma once

class GameFactory
{
	using ComponentMap = map<string, shared_ptr<Component>>;
private:
	ComponentMap _comMap;
public:
	void					AddComponent(shared_ptr<Component> component);
	shared_ptr<Component>	Getcomponent(string comName);
};