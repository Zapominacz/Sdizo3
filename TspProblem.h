#pragma once
#include "stdafx.h"


class KnapsackProblem {
private:
	Gra* knapsack;
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