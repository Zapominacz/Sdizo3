#pragma once
#include "stdafx.h"
#include "BagItem.h"

/* Klasa zawierająca rzeczy wsadzone do plecaka */
class BagItemList {
private:
	struct BagItemNode {
		BagItemNode* next;
		BagItem* value;
	};
	BagItemNode* head;
	unsigned size;
public:
	BagItemList() {
		head = NULL;
		size = 0;
	}
};