#pragma once
#include "stdafx.h"
#include "Bag.h"
/*Klasa odpowiadaj�ca za algorytmy problemu plecakowego i ich obs�ugi*/
class KnapsackProblem {
private:
	Bag* knapsack;
	BagItem* itemsList; //tablica
public:
	KnapsackProblem();
	KnapsackProblem(BagItem*);
	~KnapsackProblem();
	void setItemsList(BagItem*);
	Bag* getKnapsack();

	void doFullCheckAlgoritm();
	void doGreedyAlgoritm();
	void doDynamicProgrammingAlgoritm();
	void loadBagItems();
	void generateBagItems();
};