#pragma once
#include <vector>
#include "ItemClass.h"

class ItemManager
{
	vector<ItemClass*> vItems;

public:
	ItemManager();
	~ItemManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void Reset(void);

	void ActiveItem(tagItem _type, D2D_POINT_2F _pos);

	vector<ItemClass*> GetItems(void) { return vItems; }
};

