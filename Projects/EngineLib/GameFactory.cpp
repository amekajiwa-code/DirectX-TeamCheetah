#include "pch.h"
#include "GameFactory.h"

void GameFactory::AddComponent(shared_ptr<Component> component)
{
	if (component)
	{
		string comName = component->GetComponentName();

		_comMap.insert(make_pair(comName, component));
	}

	assert(false);
}

shared_ptr<Component> GameFactory::Getcomponent(string comName)
{
	auto findIter = _comMap.find(comName);

	if (findIter != _comMap.end())
	{

	}

	return nullptr;
}
