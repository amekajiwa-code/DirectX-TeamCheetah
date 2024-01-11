#include "pch.h"
#include "Transform.h"

Transform::Transform() : Super(ComponentType::Transform)
{
}

Transform::~Transform()
{
}

Vec3 Transform::QuatToEulerAngles(Quaternion q)
{
	Vec3 angle;

	//x roll
	double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
	double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
	angle.x = std::atan2(sinr_cosp, cosr_cosp);
	//y pitch
	double sinp = std::sqrt(1 + 2 * (q.w * q.y - q.x * q.z));
	double cosp = std::sqrt(1 - 2 * (q.w * q.y - q.x * q.z));
	angle.y = std::atan2(sinp, cosp) - PI;
	//z yaw
	double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
	double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
	angle.z = std::atan2(siny_cosp, cosy_cosp);

	return angle;
}

void Transform::AddChild(shared_ptr<Transform> child)
{
	child->SetParent(shared_from_this());
	_children.push_back(child);
}

void Transform::SetScale(const Vec3& scale)
{
	if (HasParent())
	{
		Vec3 pScale = _parent->GetScale();
		Vec3 lScale = scale;
		lScale.x /= pScale.x;
		lScale.y /= pScale.y;
		lScale.z /= pScale.z;
		SetLocalScale(lScale);
	}
	else
	{
		SetLocalScale(scale);
	}
}

void Transform::SetRotation(const Vec3& rot)
{
	if (HasParent())
	{
		Matrix pMat = _parent->GetWorldMatrix().Invert();
		Vec3 rotation;
		rotation.TransformNormal(rot, pMat);
		 
		SetLocalRotation(rotation);
	}
	else
	{
		SetLocalRotation(rot);
	}
}

void Transform::SetPosition(const Vec3& pos)
{
	if (HasParent())
	{
		Matrix pMat = _parent->GetWorldMatrix().Invert();
		Vec3 lPos;
		lPos.Transform(pos, pMat);

		SetLocalPosition(lPos);
	}
	else
	{
		SetLocalPosition(pos);
	}
}

void Transform::PreorderTransfroms(const shared_ptr<Transform>& node, int32 localIndex, int32 parentIndex)
{
	if (node == nullptr)
		return;
	
	//Data
	TransformMetaData matData;

	//Index
	matData.parentIndex = parentIndex;
	matData.index = localIndex;

	//Local
	matData.local.position = node->GetLocalPosition();
	matData.local.rotation = node->GetLocalRotation();
	matData.local.scale = node->GetLocalScale();

	//Push Data
	_transfromMetaDataList.push_back(matData);

	//Preorder Search
	auto children = node->GetChildren();

	for (auto& child : children)
	{
		PreorderTransfroms(child, _transfromMetaDataList.size(), localIndex);
	}
}

void Transform::LoadMetaData(wstring& metaPath)
{
}

void Transform::SaveMetaData(wstring& metaPath)
{
	PreorderTransfroms(shared_from_this(), 0, -1);

	Vec3 temp;
}

void Transform::Awake()
{
}

void Transform::Update()
{
}

void Transform::UpdateTransform()
{
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRot = Matrix::CreateRotationX(_localRotation.x);
	matRot *= Matrix::CreateRotationY(_localRotation.y);
	matRot *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	_matLocal = matScale * matRot * matTranslation;

	if (HasParent())
	{
		_matWorld = _matLocal * _parent->GetWorldMatrix();
	}
	else
	{
		_matWorld = _matLocal;
	}

	Quaternion quat;
	_matWorld.Decompose(_scale, quat, _position);
	_rotation = QuatToEulerAngles(quat);

	for (const shared_ptr<Transform>& child : _children)
	{
		child->UpdateTransform();
	}
}
