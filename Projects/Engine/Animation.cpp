#include "pch.h"
#include "Animation.h"
#include "Texture.h"

Animation::Animation() : Super(ResourceType::Animation)
{
}

Animation::~Animation()
{
}

void Animation::Load(const wstring& path)
{
	tinyxml2::XMLDocument doc;

	string pathStr = WTM(path);
	auto error = doc.LoadFile(pathStr.c_str());
	assert(error == XMLError::XML_SUCCESS);

	XMLElement* root = doc.FirstChildElement();
	string nameStr = root->Attribute("Name");
	_name = MTW(nameStr);
	_loop = root->BoolAttribute("Loop");
	string texPath = root->Attribute("TexturePath");
	_path = MTW(texPath);
	//load texture
	_texture = MANAGER_RESOURCES()->GetResource<Texture>(_path);

	XMLElement* node = root->FirstChildElement();
	for (; node != nullptr; node = node->NextSiblingElement())
	{
		Keyframe keyframe;

		keyframe.offset.x = node->FloatAttribute("OffsetX");
		keyframe.offset.y = node->FloatAttribute("OffsetY");
		keyframe.size.x = node->FloatAttribute("SizeX");
		keyframe.size.y = node->FloatAttribute("SizeY");
		keyframe.time = node->FloatAttribute("Time");

		AddKeyframe(keyframe);
	}
}

void Animation::Save(const wstring& path)
{
	tinyxml2::XMLDocument doc;

	XMLElement* root = doc.NewElement("Animation");
	doc.LinkEndChild(root);

	string nameStr = WTM(GetName());
	root->SetAttribute("Name", nameStr.c_str());
	root->SetAttribute("Loop", _loop);
	if (_texture)
	{
		_path = _texture->GetPath();
	}
	root->SetAttribute("TexturePath", WTM(_path).c_str());

	for (const auto& keyframe : _keyframes)
	{
		XMLElement* node = doc.NewElement("Keyframe");
		root->LinkEndChild(node);

		node->SetAttribute("OffsetX", keyframe.offset.x);
		node->SetAttribute("OffsetY", keyframe.offset.y);
		node->SetAttribute("SizeX", keyframe.size.x);
		node->SetAttribute("SizeY", keyframe.size.y);
		node->SetAttribute("Time", keyframe.time);
	}

	string savePath = WTM(path);
	auto result = doc.SaveFile(savePath.c_str());
	assert(result == XMLError::XML_SUCCESS);
}

Vec2 Animation::GetTextureSize() const
{
	return _texture->GetSize();
}

const Keyframe& Animation::GeyKeyframe(int32 index)
{
	return _keyframes[index];
}

int32 Animation::GetKeyframeCount()
{
	return static_cast<int32>(_keyframes.size());
}

void Animation::AddKeyframe(const Keyframe& keyframe)
{
	_keyframes.push_back(keyframe);
}
