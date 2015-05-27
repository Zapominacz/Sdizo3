#pragma once
#include "stdafx.h"
#include "Bag.h"
/*Klasa odpowiadaj�ca za algorytmy problemu plecakowego i ich obs�ugi*/
class KnapsackProblem {
private:
	Bag* knapsack;
	BagItem* itemsList; //tablica
	unsigned itemsListSize;
	void sortItems();
public:
	KnapsackProblem();
	~KnapsackProblem();
	void setItemsList(BagItem* list) { this->itemsList = list; }
	Bag* getKnapsack() { return knapsack; }
	void setKnapsack(Bag* knapsack) { this->knapsack = knapsack; }
	void printKnapsack();
	void printItems();

	void doFullCheckAlgoritm();
	void doGreedyAlgoritm();
	void doDynamicProgrammingAlgoritm();
	void loadBagItems();
	void generateBagItems(unsigned, unsigned, unsigned, unsigned);
};