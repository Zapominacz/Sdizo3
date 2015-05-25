#pragma once
#include "stdafx.h"
#include "Bag.h"
#include "BagItemList.h"

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

void BagItemList::print() {
	using namespace std;
	BagItemNode *tmp = head;
	cout << "Lista rzeczy:" << endl;
	while (tmp != NULL) {
		tmp->value->print();
		tmp->next;
	}
}