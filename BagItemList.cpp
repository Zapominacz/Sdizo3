#pragma once
#include "stdafx.h"
#include "BagItemList.h"
#include "Bag.h"


void BagItemList::addItem(BagItem* item) {
	if (head == NULL) {
		head = new BagItemNode(item);
	} else {
		BagItemNode* tmp = head;
		head = new BagItemNode(item);
		head->next = tmp;
	}
	size++;
}

BagItemList::~BagItemList() {
	while (head != NULL) {
		delete head;
		head = head->next;
	}
}

void BagItemList::printBag() {
	using namespace std;
	BagItemNode *tmp = head;
	cout << "Lista rzeczy:" << endl;
	while (tmp != NULL) {
		tmp->value->showItem();
		tmp->next;
	}
}