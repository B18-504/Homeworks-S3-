#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Graph.h"
#include "Sorts.h"

bool comporator(Rib a, Rib b) {
    return a.weight >= b.weight;
} 

template<typename T>
Graph<T> frame(Graph<T> innerGraph) {

    arraySequence<Rib> temp = innerGraph.getRibs();
    Sequence<Rib>* ribs = &temp;

    ribs = binSort(ribs, comporator);

    int marked[innerGraph.nodes()];
    for (int i = 0; i < innerGraph.nodes(); i++) marked[i] = 0;
    int markedCounter = 0;

    Graph<T>* resultGraph = new Graph<T>;
    for (int i = 0; i < innerGraph.nodes(); i++) resultGraph->addNode(0);
    
    if (innerGraph.nodes() < 3) return innerGraph;

    Rib firstRib = ribs->get(0);
    marked[firstRib.pointA] = 1;
    marked[firstRib.pointB] = 1;
    markedCounter += 2;
    resultGraph->createRib(firstRib.pointA, firstRib.pointB, firstRib.weight);

    for (int i = 1; i < ribs->GetLength(); i++){
        Rib currentRib = ribs->get(i);
        //std::cout << "Rib " << i << ": " << ribs->get(i).pointA << " " << ribs->get(i).pointB << " " << ribs->get(i).weight << "\n";
        if ((marked[currentRib.pointA] && !marked[currentRib.pointB]) || (marked[currentRib.pointB] && !marked[currentRib.pointA])){
            //std::cout << "Yessss\n";
            marked[currentRib.pointB] = 1;
            marked[currentRib.pointA] = 1;
            markedCounter++;
            resultGraph->createRib(currentRib.pointA, currentRib.pointB, currentRib.weight);
        }

        if (markedCounter == innerGraph.nodes()) break;
    }

    return *resultGraph;
}


template<typename T>
arraySequence<int> minLengthPredict(Graph<T> innerGraph, int currentNode, Sequence<int>* map){
    arraySequence<arraySequence<int>>* table = innerGraph.getTable();

    const int INF = 100000000;
    arraySequence<int>* result = new arraySequence<int>;
    int used[innerGraph.nodes()];

    for (int i = 0; i < innerGraph.nodes(); i++) used[i] = 0;

    for (int i = 0; i < innerGraph.nodes(); i++){
        if (i == currentNode){
            result->Append(0);
            map->Append(-1);
            continue;
        }

        result->Append(INF);
        map->Append(-1);
    }

    for (int k = 0; k < innerGraph.nodes(); k++){
        used[currentNode] = 1;

        //std::cout << currentNode << "\n";

        for (int i = 0; i < innerGraph.nodes(); i++){
            if (!used[i] && table->get(currentNode).get(i) != -1 && result->get(currentNode) + table->get(currentNode).get(i) < result->get(i)) {
                result->set(i, result->get(currentNode) + table->get(currentNode).get(i));
                map->set(i, currentNode);
            }
        }

        int myInt = INF;

        for (int i = 0; i < result->GetLength(); i++) {
            if (!used[i] && myInt > result->get(i)){
                myInt = result->get(i);
                currentNode = i;
            }
        }

        if (myInt == INF) break;
    } 

    return *result;
}

#endif //ALGORITHM_H