#pragma once
#include "stdafx.h"
#include "Bag.h"
#include "BagItem.h"

Bag::~Bag() {
	delete bagItemList;
	bagItemList = NULL;
}

void Bag::showContents() {
	bagItemList->printBag();
}

void Bag::addItem(BagItem* item) {
	bagItemList->addItem(item);
}