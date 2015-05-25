#pragma once
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
		itemsList[i].print();
	}
}

//Algorytm typu "Brute force"
void KnapsackProblem::doFullCheckAlgoritm() {
	Solution solution = Solution(0, 0); //rozwiazanie

	fullCheck(knapsack->getMaxWeight(), itemsListSize - 1, solution); //rekurencyjne odwo³ania
	for (unsigned i = 0; i < itemsListSize; i++) {
		if ((solution.bitMask & (1 << i)) == 1) { //zgodnei z bitami wsadzam rzeczy do plecaka wynikowego
			knapsack->addItem(&itemsList[i]);
		}
	}
}



void KnapsackProblem::fullCheck(unsigned weight, int index, Solution& solution) {
	if (index < 0) {
		solution.bitMask = 0; //warunek terminujacy rekurencje
		solution.value = 0;
	} else if (weight < itemsList[index].getWeight()) {
		fullCheck(weight, index - 1, solution); //gdy waga rzeczy wieksza, nie ma sensu 2 przypadku
	} else {
		Solution s1, s2;
		fullCheck(weight, index - 1, s1); //drzewiascie odwo³uje siê do ni¿szych indeksów
		fullCheck(weight - itemsList[index].getWeight(), index - 1, s2);

		//wystarczy przypisac jednemu, drugi bêdzie przy zwijaniu rekurencji
		s2.value += itemsList[index].getValue();
		s2.bitMask |= (1 << index);

		//wieksza wartosc jest rozwiazaniem
		solution = s1;
		if (solution.value < s2.value) {
			solution = s2;
		}
	}
}


void KnapsackProblem::doGreedyAlgoritm() {
	sortItems();
	unsigned i = 0;
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
	itemsListSize = liczba;
	if (knapsack != NULL) {
		delete knapsack;
	}
	knapsack = new Bag(pojemnosc);
	unsigned waga, wartosc, i = 0;
	while (file >> waga) {
		file >> wartosc;
		file >> waga;
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
	for (int i = 0; i < liczba; i++) {
		itemsList[i] = BagItem(weightDistr(generator), valueDistr(generator));
	}
}