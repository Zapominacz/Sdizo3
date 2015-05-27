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
		BagItemNode *tmp = head;
		head = head->next;
		delete tmp;
	}
	head = NULL;
}

void BagItemList::printBag() {
	using namespace std;
	BagItemNode *tmp = head;
	cout << "Lista rzeczy:" << endl;
	while (tmp != NULL) {
		tmp->value->showItem();
		tmp = tmp->next;
	}
}