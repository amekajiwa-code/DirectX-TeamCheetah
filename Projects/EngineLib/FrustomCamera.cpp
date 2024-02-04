#include "pch.h"
#include "FrustomCamera.h"
void FrustomCamera::Update()
{
	frustomBox->Create(Camera::S_MatView , Camera::S_MatProjection);
}
