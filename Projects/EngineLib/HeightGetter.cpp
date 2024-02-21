#include "pch.h"
#include "HeightGetter.h"
#include "PlayerController.h"
#include "AIController.h"

float HeightGetter::GetHeight()
{
	auto position = GetGameObject()->GetTransform()->GetLocalPosition();
	_height = _terrain->GetHeight(position.x, position.z);

	return _height;
}

void HeightGetter::FixedUpdate()
{

}

void HeightGetter::Update()
{
	//GetHeight();
	//auto transforms = GetGameObject()->GetTransform();
	//auto position = transforms->GetLocalPosition();

	//position.y = _height;
	//transforms->SetLocalPosition(position);
}

void HeightGetter::LateUpdate()
{
}
