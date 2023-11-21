#pragma once

class GameObject;

class Component
{
public:
	Component(){}
	virtual ~Component(){}
protected:
	shared_ptr<GameObject> _owner;
public:
	shared_ptr<GameObject> GetGameObject() { return _owner; }
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
};

