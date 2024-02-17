#include "pch.h"
#include "HeightGetter.h"

void HeightGetter::GetHeight()
{
	auto position = GetGameObject()->GetTransform()->GetLocalPosition();
	_height = _terrain->GetHeight(position.x, position.z);
}

void HeightGetter::FixedUpdate()
{
}

void HeightGetter::Update()
{
	GetHeight();
	auto transforms = GetGameObject()->GetTransform();
	auto position = transforms->GetLocalPosition();
	if (position.y < _height) {
		position.y = _height;
	}
	transforms->SetLocalPosition(position);
}

void HeightGetter::LateUpdate()
{
}
