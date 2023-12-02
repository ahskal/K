#include "stdafx.h"
#include "FieldItem.h"

void FieldItem::AddItem(const Item* newItem)
{
	auto it = std::find_if(items.begin(), items.end(), [&newItem](const Item* existingItem) {
		return existingItem->ItemName == newItem->ItemName;
		});

	if (it != items.end()) {
		(*it)->size++; // ���� �������� ������ ���� ����
	}
	else {
		Item* NewItem = new Item(*newItem);
		NewItem->size++;
		items.emplace_back(NewItem);
	}
}

void FieldItem::AddItem(const Item* newItem, Vector3 pos)
{
	Item* NewItem = new Item(*newItem);
	NewItem->state = ItemState::Drop;
	NewItem->actor->name += to_string(items.size());
	for (auto it : NewItem->actor->children) {
		it.second->name += to_string(items.size());
	}
	NewItem->actor->SetWorldPos(pos);
	NewItem->size++;
	items.emplace_back(NewItem);
}

void FieldItem::OpenList()
{
	for (auto inven : items) {
		cout << "[������ �̸�]\t[������ ���]\t[������ ����]" << endl;
		int size = inven->ItemName.size();
		if (inven->ItemName.size() > 8)
			cout << inven->ItemName << "\t" << inven->Cost << "\t\t" << inven->size << endl;
		else {
			cout << inven->ItemName << "\t\t" << inven->Cost << "\t\t" << inven->size << endl;
		}
	}
}

void FieldItem::Update()
{
	for (auto inven : items) {
		inven->Update();
	}
}

void FieldItem::Hierarchy()
{
	for (auto inven : items) {
		inven->actor->RenderHierarchy();
	}
}

void FieldItem::Render(shared_ptr<Shader> pShader)
{
	for (auto inven : items) {
		inven->Render(pShader);
	}
}