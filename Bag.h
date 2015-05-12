#pragma once
#include "stdafx.h"
#include "BagItemList.h"

/* Klasa reprezentuj¹ca plecak */
class Bag {
public:
	unsigned getMaxWeight() { return maxWeight; }
	unsigned getCurrValue() { return currValue; }
	unsigned getCurrWeight() { return currWeight; }
	bool isOverloaded() { return maxWeight < currWeight; };

	Bag(unsigned maxWeight) {
		bagItemList = new BagItemList();
		currValue = 0;
		currWeight = 0;
		this->maxWeight = maxWeight;
	}
private:
	unsigned maxWeight;
	unsigned currValue;
	unsigned currWeight;

	BagItemList* bagItemList;
};