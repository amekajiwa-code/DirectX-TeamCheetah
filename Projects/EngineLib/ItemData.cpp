#include "pch.h"
#include "ItemData.h"
#include "CharacterInfo.h"
#include <filesystem>
#include "Utils.h"

ItemData::ItemData()
{
}

ItemData::~ItemData()
{
}

bool ItemData::LoadItemInformationFromFile(const wstring& loadPath)
{
    //Set LoadPath
    wstring LoadPath = wstring(loadPath);
    auto tempPath = filesystem::path(LoadPath);

    //Create Document
    shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

    //ErrorCheck & LoadFile
    ::XMLError errorCheck = document->LoadFile(tempPath.string().c_str());
    if (errorCheck != ::XML_SUCCESS)
    {
        return false;
    }
    else
    {
        ::XMLElement* root = document->FirstChildElement();
        ::XMLElement* itemNode = root->FirstChildElement();

        //Load Item Data
        {
            ItemInfo tempInfo;
            ZeroMemory(&tempInfo, sizeof(ItemInfo));

            //Find FirstNode
            ::XMLNode* node = document->FirstChild();

            //Find Element
            //Name
            ::XMLElement* element = node->FirstChildElement("Name");
            string temp;
            temp = element->GetText();
            tempInfo.Name = Utils::ToWString(temp);

            //ItemType
            element = node->FirstChildElement("ItemType");
            int iType = 0;
            element->QueryIntText(&iType);
            tempInfo.ItemType = static_cast<ItemType>(iType);

            //UsableType
            element = node->FirstChildElement("UsableType");
            int uType = 0;
            element->QueryIntText(&uType);
            tempInfo.UsableType = static_cast<UsableItemType>(uType);

            //HP
            element = node->FirstChildElement("HP");
            unsigned int hp = 0;
            element->QueryUnsignedText(&hp);
            tempInfo.HP = static_cast<uint32>(hp);

            //MP
            element = node->FirstChildElement("MP");
            unsigned int mp = 0;
            element->QueryUnsignedText(&mp);
            tempInfo.MP = static_cast<uint32>(mp);

            //ATK
            element = node->FirstChildElement("ATK");
            int atk = 0;
            element->QueryIntText(&atk);
            tempInfo.ATK = static_cast<uint16>(atk);

            //DEF
            element = node->FirstChildElement("DEF");
            int def = 0;
            element->QueryIntText(&def);
            tempInfo.DEF = static_cast<uint16>(def);

            //Price
            element = node->FirstChildElement("Price");
            unsigned int Price = 0;
            element->QueryUnsignedText(&Price);
            tempInfo.Price = static_cast<uint32>(Price);

            //MeshFilePath
            element = node->FirstChildElement("MeshFilePath");
            temp.clear();
            temp = element->GetText();
            tempInfo.MeshFilePath = Utils::ToWString(temp);

            //MaterialFilePath
            element = node->FirstChildElement("MaterialFilePath");
            temp.clear();
            temp = element->GetText();
            tempInfo.MaterialFilePath = Utils::ToWString(temp);

            //MeshFilePath
            element = node->FirstChildElement("ImageFilePath");
            temp.clear();
            temp = element->GetText();
            tempInfo.ImageFilePath = Utils::ToWString(temp);

            _itemInfo.Name = tempInfo.Name;
            _itemInfo.ItemType = tempInfo.ItemType;
            _itemInfo.UsableType = tempInfo.UsableType;
            _itemInfo.HP = tempInfo.HP;
            _itemInfo.MP = tempInfo.MP;
            _itemInfo.ATK = tempInfo.ATK;
            _itemInfo.DEF = tempInfo.DEF;
            _itemInfo.Price = tempInfo.Price;
            _itemInfo.MeshFilePath = tempInfo.MeshFilePath;
            _itemInfo.MaterialFilePath = tempInfo.MaterialFilePath;
            _itemInfo.ImageFilePath = tempInfo.ImageFilePath;
        }

        //Create Model Data
        {
            _itemMesh = make_shared<Model>();
            _itemMesh->ReadMaterial(_itemInfo.MaterialFilePath);
            _itemMesh->ReadModel(_itemInfo.MeshFilePath);    
        }

        //CreateImage Data
        {
            _itemImage = MANAGER_RESOURCES()->GetOrAddTexture(_itemInfo.Name, _itemInfo.ImageFilePath);
        }

    }

    return true;
}

bool ItemData::SaveItemInformationToFile(const wstring& savePath)
{
    //Set SavePath
    wstring SavePath = wstring(savePath);
    auto tempPath = filesystem::path(SavePath);

    //Create Document
    shared_ptr<tinyxml2::XMLDocument> document = make_shared<tinyxml2::XMLDocument>();

    //Create Save Data 
    {
        ::XMLNode* node = document->NewElement("ItemInfo");
        document->InsertFirstChild(node);

        ::XMLElement* element = document->NewElement("Name");
        element->SetText(Utils::ToString(_itemInfo.Name).c_str());
        node->InsertEndChild(element);

        element = document->NewElement("ItemType");
        element->SetText(static_cast<uint8>(_itemInfo.ItemType));
        node->InsertEndChild(element);

        element = document->NewElement("UsableType");
        element->SetText(static_cast<uint8>(_itemInfo.UsableType));
        node->InsertEndChild(element);

        element = document->NewElement("HP");
        element->SetText(static_cast<uint32>(_itemInfo.HP));
        node->InsertEndChild(element);

        element = document->NewElement("MP");
        element->SetText(static_cast<uint32>(_itemInfo.MP));
        node->InsertEndChild(element);

        element = document->NewElement("ATK");
        element->SetText(static_cast<uint16>(_itemInfo.ATK));
        node->InsertEndChild(element);

        element = document->NewElement("DEF");
        element->SetText(static_cast<uint16>(_itemInfo.DEF));
        node->InsertEndChild(element);

        element = document->NewElement("Price");
        element->SetText(static_cast<uint32>(_itemInfo.Price));
        node->InsertEndChild(element);

        element = document->NewElement("MeshFilePath");
        element->SetText(Utils::ToString(_itemInfo.MeshFilePath).c_str());
        node->InsertEndChild(element);

        element = document->NewElement("MaterialFilePath");
        element->SetText(Utils::ToString(_itemInfo.MaterialFilePath).c_str());
        node->InsertEndChild(element);

        element = document->NewElement("ImageFilePath");
        element->SetText(Utils::ToString(_itemInfo.ImageFilePath).c_str());
        node->InsertEndChild(element);
    }

    //Save Data
    ::XMLError errorCheck = document->SaveFile(tempPath.string().c_str());

    //ErrorCheck
    if (errorCheck != ::XML_SUCCESS)
    {
        return false;
    }

    return true;
}

bool ItemData::ItemEffectToSelf(bool active)
{
    return false;
}

bool ItemData::ItemEffectToTarget(const shared_ptr<GameObject>& target)
{
    return false;
}
