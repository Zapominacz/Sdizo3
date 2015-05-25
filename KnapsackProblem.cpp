#pragma once
#include "KnapsackProblem.h"

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
	for (int i = 0; i < itemsListSize; i++) {
		itemsList[i].print();
	}
}

void KnapsackProblem::doGreedyAlgoritm() {
	sortItems();
	int i = 0;
	//rzeczy jest zawsze wiecej niz pojemnosc plecaka
	while (!knapsack->isOverloaded()) {
		knapsack->addItem(&itemsList[i]);
		i++;
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
	for (int i = 0; i < itemsListSize; i++) {
		int j = i + 1;
		while (j < itemsListSize) {
			if (itemsList[j].getValueDensity() > itemsList[j - 1].getValueDensity()) {
				swap(itemsList[j], itemsList[j - 1]);
			}
			j++;
		}
	}
}

//³aduje z pliku
void KnapsackProblem::loadBagItems() {
	using namespace std;
	char patch[64];
	cout << "sciezka: ";
	cin >> patch;
	fstream file(patch, std::ios_base::in);
	int pojemnosc, liczba;
	file >> pojemnosc;
	file >> liczba;
	if (itemsList != NULL) {
		delete[] itemsList;
	}
	itemsList = new BagItem[liczba];

	if (knapsack != NULL) {
		delete knapsack;
	}
	knapsack = new Bag(pojemnosc);
	int waga, wartosc, i = 0;
	while (file >> waga) {
		file >> wartosc;
		file >> waga;
		itemsList[i] = BagItem(waga, wartosc);
		i++;
	}
	file.close();
}

//generuje
void KnapsackProblem::generateBagItems(int liczba, int pojemnosc) {
	if (itemsList != NULL) {
		delete[] itemsList;
	}
	itemsList = new BagItem[liczba];

	if (knapsack != NULL) {
		delete knapsack;
	}
	knapsack = new Bag(pojemnosc);

}