#pragma once
#include "Component.h"

class Transform : public Component, public enable_shared_from_this<Transform>
{
	using Super = Component;
public:
	Transform();
	virtual ~Transform();
private:
	shared_ptr<Transform>			_parent;
	vector<shared_ptr<Transform>>	_children;
	vector<TransformMetaData>		_transfromMetaDataList;
private:
	//local
	Vec3 _localScale = { 1.f,1.f,1.f };
	Vec3 _localRotation = { 0.f,0.f,0.f };
	Vec3 _localPosition = { 0.f,0.f,0.f };
	//world
	Vec3 _scale = { 1,1,1 };
	Vec3 _rotation = { 0,0,0 };
	Vec3 _position = { 0,0,0 };
private:
	Matrix _matLocal = Matrix::Identity;
	Matrix _matWorld = Matrix::Identity;
private:
	Vec3 QuatToEulerAngles(Quaternion q);
public:
	bool HasParent() { return _parent != nullptr; }
public:
	shared_ptr<Transform> GetParent() const { return _parent; }
	const vector<shared_ptr<Transform>>& GetChildren() { return _children; }
public:
	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	void AddChild(shared_ptr<Transform> child);
public:
	Vec3 GetLocalScale() const { return _localScale; }
	Vec3 GetLocalRotation() const { return _localRotation; }
	Vec3 GetLocalPosition() const { return _localPosition; }
	Vec3 GetScale() const { return _scale; }
	Vec3 GetRotation() const { return _rotation; }
	Vec3 GetPosition() const { return _position; }
	Matrix GetWorldMatrix() const { return _matWorld; }
public:
	Vec3 GetUpVector() const { return _matWorld.Up(); }
	Vec3 GetRightVector() const { return _matWorld.Right(); }
	Vec3 GetLookVector() const { return _matWorld.Backward(); }
public:
	//local
	void SetLocalScale(const Vec3& scale) { _localScale = scale; UpdateTransform(); }
	void SetLocalRotation(const Vec3& rot) { _localRotation = rot; UpdateTransform();}
	void SetLocalPosition(const Vec3& pos) { _localPosition = pos; UpdateTransform();}
	//world
	void SetScale(const Vec3& scale);
	void SetRotation(const Vec3& rot);
	void SetPosition(const Vec3& pos);
	void SetLookVector(const Vec3& look) { _matWorld.Backward() = look; }
public:
	void RotateAround(const Vec3& axis);
private:
	void PreorderTransfroms(const shared_ptr<Transform>& node, int32 localIndex, int32 parentIndex);
public:
	virtual void LoadMetaData(wstring& metaPath) override;
	virtual void SaveMetaData(wstring& metaPath) override;
public:
	virtual void Awake() override;
	virtual void Update() override;
	void UpdateTransform();
};

