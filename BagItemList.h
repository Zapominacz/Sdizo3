#pragma once
#include "stdafx.h"
#include "BagItem.h"

/* Klasa zawieraj¹ca rzeczy wsadzone do plecaka */
class BagItemList {
private:
	struct BagItemNode {
		BagItemNode* next;
		BagItem* value;
		BagItemNode(BagItem* value) {
			this->value = value;
			next = NULL;
		}
	};
	BagItemNode* head;
	unsigned size;
public:
	void print();
	void addItem(BagItem*);
	BagItemList() {
		head = NULL;
		size = 0;
	}
	~BagItemList();
};