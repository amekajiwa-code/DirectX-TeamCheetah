#pragma once
#include "Component.h"

class Transform : public Component
{
	using Super = Component;
public:
	Transform();
	virtual ~Transform();
private:
	shared_ptr<Transform> _parent;
	vector<shared_ptr<Transform>> _children;
private:
	Vec3 _localScale = { 1.f,1.f,1.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localPosition = { 0.f,0.f,0.f };
	Vec3 _scale;
	Vec3 _rotation;
	Vec3 _position;
private:
	Vec3 _up;
	Vec3 _right;
	Vec3 _look;
private:
	Matrix _matLocal = Matrix::Identity;
	Matrix _matWorld;
public:
	bool HasParent() { return _parent != nullptr; }
public:
	shared_ptr<Transform> GetParent() const { return _parent; }
public:
	Vec3 GetLocalScale() const { return _localScale; }
	Vec3 GetLocalRotation() const { return _localRotation; }
	Vec3 GetLocalPosition() const { return _localPosition; }
	Vec3 GetScale() const { return _scale; }
	Vec3 GetRotation() const { return _rotation; }
	Vec3 GetPosition() const { return _position; }
	Matrix GetWorldMatrix() const { return _matWorld; }
public:
	void SetLocalScale(const Vec3& scale) { _localScale = scale; }
	void SetLocalRotation(const Vec3& rot) { _localRotation = rot; }
	void SetLocalPosition(const Vec3& pos) { _localPosition = pos; }
	void SetScale(const Vec3& scale) { _scale = scale; }
	void SetRotation(const Vec3& rot) { _rotation = rot; }
	void SetPosition(const Vec3& pos) { _position = pos; }
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void UpdateTransform();
};

