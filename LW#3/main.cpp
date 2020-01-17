#include <iostream>
#include "Interface.h"
#include "Graph.h"
#include "algorithm.h"
#include <time.h>

void createNewGraphIPerformer(void* pointer){
	Interface* interface = (Interface*)pointer;

	Graph<int>* graph = new Graph<int>;
	
	int nodes;
	int ribs;

	std::cout << "Число узлов: ";
	std::cin >> nodes;

	std::cout << "Число рёбер: ";
	std::cin >> ribs;

	for (int i = 0; i < nodes; i++) graph->addNode(0);
	std::cout << "\nРёбра (начало, конец, вес):\n";
	for (int i = 0; i < ribs; i++) {
		std::cout << "Ребро " << i+1 << ": ";
		Rib newRib;
		std::cin >> newRib.pointA >> newRib.pointB >> newRib.weight;
		graph->addRib(newRib);
	}

	interface->restoreDataSet((void*)graph, 0);
}


void addNodesIPerformer(void* pointer){
	Interface* interface = (Interface*)pointer;

	Graph<int>* graph = (Graph<int>*)interface->getDataSet(0);

	std::cout << "Число вершин: ";
	int n;
	std::cin >> n;

	for (int i = 0; i < n; i++) graph->addNode(0);
}


void addRibsIPerformer(void* pointer){
	Interface* interface = (Interface*)pointer;

	Graph<int>* graph = (Graph<int>*)interface->getDataSet(0);

	int ribs;

	std::cout << "Число рёбер: ";
	std::cin >> ribs;

	std::cout << "\nРёбра (начало, конец, вес):\n";
	for (int i = 0; i < ribs; i++) {
		std::cout << "Ребро " << i+1 << ": ";
		Rib newRib;
		std::cin >> newRib.pointA >> newRib.pointB >> newRib.weight;
		graph->addRib(newRib);
	}
}


void showGraphIPerformer(void* pointer){
	Interface* interface = (Interface*)pointer;

	Graph<int>* graph = (Graph<int>*)interface->getDataSet(0);

	arraySequence<arraySequence<int>>* table = graph->getTable();
	
	std::string outputType = interface->getMultiState("Формат вывода полученного графа");

	if (outputType == "Matrix"){
		for (int i = 0; i < table->GetLength(); i++){
			for (int j = 0; j < table->GetLength(); j++){
				std::cout << " " << table->get(i).get(j);
			}

			std::cout << "\n";
		}

		return;
	}

	for (int i = 0; i < table->GetLength(); i++){
		for (int j = i; j < table->GetLength(); j++){
			if (table->get(i).get(j) != -1) std::cout << "(" << i << ", " << j << ")\n";
		}
	}
}


void buildFrameIPerformer(void* pointer){
	Interface* interface = (Interface*)pointer;

	Graph<int>* graph = (Graph<int>*)interface->getDataSet(0);
	clock_t time;

	time = clock();
	Graph<int> result = frame(*graph);
	time = clock() - time;

	arraySequence<arraySequence<int>>* table = result.getTable();

	std::string outputType = interface->getMultiState("Формат вывода полученного графа");
	std::string showTime = interface->getYnState("Показывать время выполнения алгоритма");

	std::cout << "Остов графа: \n\n";

	if (outputType == "Matrix"){
		for (int i = 0; i < table->GetLength(); i++){
			for (int j = 0; j < table->GetLength(); j++){
				std::cout << " " << table->get(i).get(j);
			}

			std::cout << "\n";
		}

		if(showTime == "yes")std::cout << "\nВремя выполнения алгоритма: " << (double)time/CLOCKS_PER_SEC;
		return;
	}

	for (int i = 0; i < table->GetLength(); i++){
		for (int j = i; j < table->GetLength(); j++){
			if (table->get(i).get(j) != -1) std::cout << "(" << i << ", " << j << ")\n";
		}
	}
	if(showTime == "yes")std::cout << "\nВремя выполнения алгоритма: " << (double)time/CLOCKS_PER_SEC << "s";
}


void buildShortRouteIPerformer(void* pointer){
	Interface* interface = (Interface*)pointer;

	Graph<int>* graph = (Graph<int>*)interface->getDataSet(0);
	std::string showTime = interface->getYnState("Показывать время выполнения алгоритма");

	int startNode;
	clock_t time;
	std::cout << "Начальная вершина графа: ";
	std::cin >> startNode;

	if (startNode < 0 || startNode >= graph->nodes()){
		std::cout << "Всё плохо, такой вершины нет :(";
		return;
	}

	arraySequence<int>* map = new arraySequence<int>;
	
	time = clock();
	arraySequence<int> result = minLengthPredict(*graph, startNode, map);
	time = clock() - time;

	std::cout << "Минимальные стоимости и пути:\n\n";

	for (int i = 0; i < result.GetLength(); i++){
		std::cout << "До вершины " << i << ":\n Минимальная стоимость пути: " << result.get(i) << "\n";
		std::cout << " Восстановленный путь: ";
		int currentNode = i;
		while(currentNode != startNode){
			std::cout << currentNode << " <- ";
			currentNode = map->get(currentNode);
		}

		std::cout << startNode << "\n\n";
	}

	if(showTime == "yes")std::cout << "\nВремя выполнения алгоритма: " << (double)time/CLOCKS_PER_SEC << "s";
}

int main(){


	Interface* interface = new Interface;
	Graph<int>* graph = new Graph<int>;
	interface->addDataSet((void*)graph);
	
	InterfaceItem createNewGraph;
	createNewGraph.name = "Создать новый граф";
	createNewGraph.performer = createNewGraphIPerformer;

	InterfaceItem addNodes;
	addNodes.name = "Добавить n вершин в граф";
	addNodes.performer = addNodesIPerformer;

	InterfaceItem addRibs;
	addRibs.name = "Добавить n рёбер в граф";
	addRibs.performer = addRibsIPerformer;

	InterfaceItem showGraph;
	showGraph.name = "Показать граф";
	showGraph.performer = showGraphIPerformer;

	InterfaceItem buildFrame;
	buildFrame.name = "Построить остов графа";
	buildFrame.performer = buildFrameIPerformer;

	InterfaceItem buildShortRoute;
	buildShortRoute.name = "Построить кротчайший путь между вершинами";
	buildShortRoute.performer = buildShortRouteIPerformer;

	InterfaceItem showTime;
	showTime.name = "Показывать время выполнения алгоритма";
	showTime.type = "YesNo";

	InterfaceItem showFormat;
	showFormat.name = "Формат вывода полученного графа";
	showFormat.type = "MultiState";
	std::string formats[2] = {"Matrix", "List"};
	showFormat.states = formats;
	showFormat.statesLength = 2;

	interface->addItem(createNewGraph);
	interface->addItem(addNodes);
	interface->addItem(addRibs);
	interface->addItem(showGraph);
	interface->addItem(buildFrame);
	interface->addItem(buildShortRoute);
	interface->addItem(showTime);
	interface->addItem(showFormat);

	interface->drawMenu();
	interface->start();

	return 0;
}
