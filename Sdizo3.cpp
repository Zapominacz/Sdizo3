#pragma once
#include "stdafx.h"
#include "TspProblem.h"
#include "KnapsackProblem.h"
#include "Timer.h"

void presentation() {
	using namespace std;
	int problem = -1;

	char ch;
	int tmp, tmp2, tmp3, tmp4;
	TspProblem *tsp = new TspProblem();
	KnapsackProblem *knapsack = new KnapsackProblem();
	do {
		if (problem == 1) {
			
			cout << "Problem Komiwojazera" << endl
				<< "1. Wczytaj miasta" << endl
				<< "2. Generuj miasta" << endl
				<< "3. Przegl¹d zupe³ny" << endl
				<< "4. Algorytm zach³anny" << endl
				<< "5. Algorytm przeszukiwania lokalnego" << endl
				<< "6. Pokaz wynik" << endl
				<< "7. Pokaz miasta" << endl
				<< "q. wyjdz" << endl;
			cin >> ch;
			switch (ch) {
			case'1':
				tsp->loadCityGraph();
				break;
			case'2':
				cout << "Ilosc miast: " << endl;
				cin >> tmp;
				cout << "Max waga: " << endl;
				cin >> tmp2;
				tsp->generateCityGraph(tmp, tmp2);
				break;
			case'3':
				tsp->doFullCheckAlgoritm();
				break;
			case'4':
				tsp->doGreedyAlgoritm();
				break;
			case'5':
				tsp->doDynamicProgrammingAlgoritm();
				break;
			case'6':
				tsp->getWay()->printMatrixGraph();
				tsp->getWay()->printListGraph();
				break;
			case'7':
				tsp->getCitiesMap()->printMatrixGraph();
				tsp->getCitiesMap()->printListGraph();
				break;
			case'q':
				problem = -1;
				break;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		} else if (problem == 2) {
			cout << "Problem Plecakowy" << endl
				<< "1. Wczytaj przedmioty" << endl
				<< "2. Generuj przedmioty" << endl
				<< "3. Przegl¹d zupe³ny" << endl
				<< "4. Algorytm zach³anny" << endl
				<< "5. Algorytm dynamiczny" << endl
				<< "6. Pokaz plecak" << endl
				<< "7. Pokaz przedmioty" << endl
				<< "q. wyjdz" << endl;
			cin >> ch;
			switch (ch) {
			case'1':
				knapsack->loadBagItems();
				break;
			case'2':
				cout << "Ilosc rzeczy: " << endl;
				cin >> tmp;
				cout << "Pojemnosc: " << endl;
				cin >> tmp2;
				cout << "Max ciezar: " << endl;
				cin >> tmp3;
				cout << "Max wartosc: " << endl;
				cin >> tmp4;
				knapsack->generateBagItems(tmp, tmp2, tmp3, tmp4);
				break;
			case'3':
				knapsack->doFullCheckAlgoritm();
				break;
			case'4':
				knapsack->doGreedyAlgoritm();
				break;
			case'5':
				knapsack->doDynamicProgrammingAlgoritm();
				break;
			case'6':
				knapsack->printKnapsack();
				break;
			case'7':
				knapsack->printItems();
				break;
			case'q':
				problem = -1;
				break;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		} else {
			cout << "Wybierz algorytm: " << endl
				<< "1. Problem komiwojazera" << endl
				<< "2. Problem plecakowy" << endl
				<< "q. Wyjdz" << endl;
			cin >> ch;
			switch (ch) {
			case '1':
				problem = 1;
				break;
			case '2':
				problem = 2;
				break;
			case 'q':
				problem = -2;
				break;
			default:
				cout << "Zly wybor!" << endl;
				continue;
			}
		}
	} while (problem > -2);

	delete knapsack;
	delete tsp;

}

void testKnapsack() {
	using namespace std;
	int items[] = { 25, 33, 35 };
	int sizes[] = { 10, 20, 30 };
	int times[] = { 5, 1, 1, 1};
	fstream fileF("knapsackFull.txt", ios_base::app);
	fstream fileG("knapsackGreedy.txt", ios_base::app);
	fstream fileD("knapsackDynamic.txt", ios_base::app);
	KnapsackProblem *knapsack = new KnapsackProblem();
	Bag* result = NULL;
	for (int i = 0; i < 5; i++) {
		knapsack->generateBagItems(items[i], 1, 50, 20);
		for (int j = 0; j < 3; j++) {
			Timer *timerF = new Timer();
			Timer *timerG = new Timer();
			Timer *timerD = new Timer();
			for (int k = 0; k < times[i]; k++) {
				timerF->startTimer();
				knapsack->doFullCheckAlgoritm();
				timerF->stopTimer();
				result = knapsack->getKnapsack();
				timerG->startTimer();
				knapsack->doGreedyAlgoritm();
				timerG->stopTimer();
				result = knapsack->getKnapsack();
				timerD->startTimer();
				knapsack->doDynamicProgrammingAlgoritm();
				timerD->stopTimer();
				result = knapsack->getKnapsack();

				timerF->nextMeasure();
				timerG->nextMeasure();
				timerD->nextMeasure();
				cout << items[i] << " - " << sizes[j] << " - " << k << endl;
			}
			
			fileF << items[i] << " - " << sizes[j] << " - " << timerF->getAvgTime() << endl;
			fileG << items[i] << " - " << sizes[j] << " - " << timerG->getAvgTime() << endl;
			fileD << items[i] << " - " << sizes[j] << " - " << timerD->getAvgTime() << endl;
			fileF.flush();
			fileG.flush();
			fileD.flush();
			delete timerF;
			delete timerG;
			delete timerD;
		}
	}
	delete knapsack;
	fileF.close();
	fileG.close();
	fileD.close();
}

void testTsp() {
	using namespace std;
	int cities[] = { 5, 6, 7, 8, 9};
	int times[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	fstream fileF("tspFull.txt", ios_base::app);
	fstream fileG("tspGreedy.txt", ios_base::app);
	fstream fileD("tspDynamic.txt", ios_base::app);
	TspProblem *tsp = new TspProblem();
	CityGraph *graph = NULL;
	for (int i = 0; i < 5; i++) {
		tsp->generateCityGraph(cities[i], 50);
		Timer *timerF = new Timer();
		Timer *timerG = new Timer();
		Timer *timerD = new Timer();
		for (int k = 0; k < times[i]; k++) {
			timerF->startTimer();
			tsp->doFullCheckAlgoritm();
			timerF->stopTimer();
			graph = tsp->getWay();
			timerG->startTimer();
			tsp->doGreedyAlgoritm();
			timerG->stopTimer();
			graph = tsp->getWay();
			timerD->startTimer();
			tsp->doDynamicProgrammingAlgoritm();
			timerD->stopTimer();
			graph = tsp->getWay();

			timerF->nextMeasure();
			timerG->nextMeasure();
			timerD->nextMeasure();
			cout << cities[i] << " - " << k << endl;
		}

		fileF << cities[i] << " - " << timerF->getAvgTime() << endl;
		fileG << cities[i] << " - " << timerG->getAvgTime() << endl;
		fileD << cities[i] << " - " << timerD->getAvgTime() << endl;
		fileF.flush();
		fileG.flush();
		fileD.flush();
		delete timerF;
		delete timerG;
		delete timerD;
	}
	delete tsp;
	fileF.close();
	fileG.close();
	fileD.close();
}


int _tmain(int argc, _TCHAR* argv[]) {
	//presentation();
	testTsp();
	testKnapsack();
	return 0;
}

