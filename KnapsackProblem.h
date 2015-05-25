#pragma once
#include "stdafx.h"
#include "Bag.h"
/*Klasa odpowiadaj¹ca za algorytmy problemu plecakowego i ich obs³ugi*/
class KnapsackProblem {
private:
	Bag* knapsack;
	BagItem* itemsList; //tablica
	unsigned itemsListSize;
	void sortItems();

	//Klasa pomocnicza do pe³nego przeszukiwania
	class Solution {
	public:
		unsigned long long bitMask; //korzystam z 64 bit pola do zapisu bitowego: 0 - przedmiot nei nalezy, 1 - nalezy
		unsigned value; //ogranicza to rozwi¹zania do 64 przedmiotów, co pokrywa siê z treœci¹ projektu
		Solution(unsigned long long bitMask, unsigned value) {
			this->bitMask = bitMask;
			this->value = value;
		}
		Solution() {
			this->bitMask = 0;
			this->value = 0;
		}
	};
	void fullCheck(unsigned, int, Solution&);
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