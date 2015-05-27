#pragma once
#include "stdafx.h"
#include "KnapsackProblem.h"
#include <random>


KnapsackProblem::KnapsackProblem() {
	knapsack = NULL;
	itemsList = NULL;
	itemsListSize = 0;
}
KnapsackProblem::~KnapsackProblem() {
	if (knapsack != NULL) {
		delete knapsack;
		knapsack = NULL;
	}
	if (itemsList != NULL) {
		delete itemsList;
		itemsList = NULL;
	}
}

void KnapsackProblem::printKnapsack() {
	knapsack->showContents();
}

void KnapsackProblem::printItems() {
	for (unsigned i = 0; i < itemsListSize; i++) {
		itemsList[i].showItem();
	}
}

//Algorytm typu "Brute force"
void KnapsackProblem::doFullCheckAlgoritm() {
	if (!knapsack->isEmpty()) {
		knapsack->clear();
	}

	unsigned long long table = 1;
	unsigned long long bestTable = 0;
	unsigned long long endOfTable = (1 << itemsListSize);
	unsigned bestValue = 0;
	while (table < endOfTable) {
		unsigned long long tmp = 1;
		unsigned tmpValue = 0;
		unsigned tmpWeight = 0;
		for (unsigned i = 0; i < itemsListSize; i++) {
			bool isSet = table & tmp;
			if (isSet) {
				tmpWeight += itemsList[i].getWeight();
				tmpValue += itemsList[i].getValue();
			}
			tmp = tmp << 1;
		}
		if (tmpWeight <= knapsack->getMaxWeight() && tmpValue > bestValue) {
			bestTable = table;
			bestValue = tmpValue;
		}
		table++;
	}
	unsigned long long tmp = 1;
	for (unsigned i = 0; i < itemsListSize; i++) {
		bool isSet = bestTable & tmp;
		if (isSet) {
			knapsack->addItem(&itemsList[i]);
		}
		tmp = tmp << 1;
	}
}

void KnapsackProblem::doGreedyAlgoritm() {
	if (!knapsack->isEmpty()) {
		knapsack->clear();
	}

	sortItems();
	//rzeczy jest zawsze wiecej niz pojemnosc plecaka
	for (unsigned i = 0; i < itemsListSize; i++) {
		if (itemsList[i].getWeight() + knapsack->getCurrWeight() < knapsack->getMaxWeight()) {
			knapsack->addItem(&itemsList[i]);
		}
	}
}

// Zamiana rzeczy
void swap(BagItem &first, BagItem &second) {
	BagItem tmp = first;
	first = second;
	second = tmp;
}
//Insertion sort
void KnapsackProblem::sortItems() {
	for (unsigned i = 0; i < itemsListSize; i++) {
		unsigned j = i + 1;
		while (j > 0) {
			if (itemsList[j].getValueDensity() > itemsList[j - 1].getValueDensity()) {
				swap(itemsList[j], itemsList[j - 1]);
			}
			j--;
		}
	}
}

void KnapsackProblem::doDynamicProgrammingAlgoritm() {
	if (!knapsack->isEmpty()) {
		knapsack->clear();
	}

	unsigned** bestTable = new unsigned*[itemsListSize + 1];
	for (unsigned i = 0; i < itemsListSize + 1; i++) {
		bestTable[i] = new unsigned[knapsack->getMaxWeight() + 1];
		for (unsigned j = 0; j <= knapsack->getMaxWeight(); j++) {
			if (i == 0 || j == 0) {
				bestTable[i][j] = 0;
			}
			else if (itemsList[i - 1].getWeight() <= j) {
				bestTable[i][j] = max(itemsList[i - 1].getValue() + bestTable[i - 1][j - itemsList[i - 1].getWeight()],
					bestTable[i - 1][j]);
			}
			else {
				bestTable[i][j] = bestTable[i - 1][j];
			}
		}
	}
	//czy indeksy sa ok?
	unsigned w = knapsack->getMaxWeight();
	for (unsigned i = itemsListSize; i > 0; i--) {
		if (bestTable[i][w] != bestTable[i - 1][w]) {
			knapsack->addItem(&itemsList[i - 1]);
			w -= itemsList[i - 1].getWeight();
		}
	}

	for (unsigned i = 0; i < itemsListSize; i++) {
		delete[] bestTable[i];
	}
	delete bestTable;
}

//³aduje z pliku
void KnapsackProblem::loadBagItems() {
	using namespace std;
	char patch[64];
	cout << "sciezka: ";
	cin >> patch;
	fstream file(patch, ios_base::in);
	int pojemnosc, liczba;
	file >> pojemnosc;
	file >> liczba;
	if (itemsList != NULL) {
		delete[] itemsList;
	}
	itemsList = new BagItem[liczba];
	itemsListSize = liczba;
	if (knapsack != NULL) {
		delete knapsack;
	}
	knapsack = new Bag(pojemnosc);
	unsigned waga, wartosc, i = 0;
	while (file >> waga) {
		file >> wartosc;
		itemsList[i] = BagItem(waga, wartosc);
		i++;
	}
	file.close();
}

//generuje
void KnapsackProblem::generateBagItems(unsigned liczba, unsigned pojemnosc, unsigned maxWaga, unsigned maxWartosc) {
	using namespace std;
	if (itemsList != NULL) {
		delete[] itemsList;
	}
	itemsList = new BagItem[liczba];
	itemsListSize = liczba;
	if (knapsack != NULL) {
		delete knapsack;
	}
	knapsack = new Bag(pojemnosc);
	random_device rand_dev;
	mt19937 generator(rand_dev());
	uniform_int_distribution<int> weightDistr(0, maxWaga);
	uniform_int_distribution<int> valueDistr(0, maxWartosc);
	for (unsigned i = 0; i < liczba; i++) {
		itemsList[i] = BagItem(weightDistr(generator), valueDistr(generator));
	}
}