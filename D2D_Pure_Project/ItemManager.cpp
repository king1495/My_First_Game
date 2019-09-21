#include "stdafx.h"
#include "ItemManager.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
}

HRESULT ItemManager::Init(void)
{
	for (UINT i = 0; i < 30; ++i) {
		ItemClass* Temp = new ItemClass;
		vItems.push_back(Temp);
	}

	return S_OK;
}

void ItemManager::Release(void)
{
	for (UINT i = 0; i < vItems.size(); ++i) {
		SafeDeleteClass(vItems[i]);
	}
	vItems.clear();
}

void ItemManager::Update(void)
{
	for (ItemClass* i : vItems)
		i->Update();
}

void ItemManager::Render(void)
{
	for (ItemClass* i : vItems)
		i->Render();
}

void ItemManager::ActiveItem(tagItem _type, D2D_POINT_2F _pos)
{
	for (ItemClass* i : vItems) {
		if (i->GetisActive()) continue;
		i->Init(_type, _pos);
		return;
	}
}

void ItemManager::Reset(void)
{
	for (UINT i = 0; i < vItems.size(); ++i) {
		if (vItems[i]->GetisActive()) vItems[i]->SetisActive();
	}
}