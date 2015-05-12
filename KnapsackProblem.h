#pragma once
#include "stdafx.h"
#include "Bag.h"

class KnapsackProblem {
private:
	Bag* knapsack;
	BagItem* itemsList;
public:
	KnapsackProblem();
	KnapsackProblem(BagItem*);
	~KnapsackProblem();
	void setItemsList(BagItem*);
	Bag* getKnapsack();

	Bag* doFullCheckAlgoritm();
	Bag* doGreedyAlgoritm();
	Bag* doDynamicProgrammingAlgoritm();
};