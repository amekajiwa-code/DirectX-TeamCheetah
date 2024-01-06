#include "pch.h"
#include "ModelAnimation.h"

shared_ptr<ModelKeyframe> ModelAnimation::GetKeyframe(const wstring& name)
{
	auto findIter = keyframes.find(name);
	if (findIter == keyframes.end())
		return nullptr;

	return findIter->second;
}
