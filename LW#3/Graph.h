#ifndef GRAPH_H
#define GRAPH_H

#include "arraySequence.cpp"

struct Rib{
    int pointA;
    int pointB;
    int weight;
};

template<typename T>
class Graph {
    public:
        void addNode(T item){
            this->graphItems->Append(item);

            for (int i = 0; i < this->numberOfNodes; i++){
                arraySequence<int>* currentNode = this->graph->GetPtr(i);
                currentNode->Append(-1);
            }

            arraySequence<int>* lastRow = new arraySequence<int>;
            this->numberOfNodes++;
            for(int i = 0; i < this->numberOfNodes; i++){
                lastRow->Append(-1);
            }

            this->graph->Append(*lastRow);
        }

        void createRib(int pointA, int pointB, int weight){
            this->graph->GetPtr(pointA)->set(pointB, weight);
            this->graph->GetPtr(pointB)->set(pointA, weight);

            Rib newRib;
            newRib.pointA = pointA;
            newRib.pointB = pointB;
            newRib.weight = weight;

            this->ribs->Append(newRib);
        }

        void addRib(Rib rib){
            this->graph->GetPtr(rib.pointA)->set(rib.pointB, rib.weight);
            this->graph->GetPtr(rib.pointB)->set(rib.pointA, rib.weight);
            this->ribs->Append(rib);
        }

        void removeRib(int pointA, int pointB){
            this->graph->GetPtr(pointA)->set(pointB, -1);
            this->graph->GetPtr(pointB)->set(pointA, -1);
        }

        arraySequence<arraySequence<int>>* getTable(){
            return this->graph;
        }

        arraySequence<Rib> getRibs(){
            return *(this->ribs);
        }

        int nodes(){
            return this->numberOfNodes;
        }

        int ribsN(){
            return this->numberOfRibs;
        }
    private:
        arraySequence<arraySequence<int>>* graph = new arraySequence<arraySequence<int>>;
        arraySequence<T>* graphItems = new arraySequence<T>;
        arraySequence<Rib>* ribs = new arraySequence<Rib>;
        int numberOfNodes = 0;
        int numberOfRibs = 0;
};

template<typename T>
class OrGraph {
    public:
        void addNode(T item){
            this->graphItems->Append(item);

            for (int i = 0; i < this->numberOfNodes; i++){
                arraySequence<int>* currentNode = this->graph->GetPtr(i);
                currentNode->Append(0);
            }

            arraySequence<int>* lastRow = new arraySequence<int>;
            this->numberOfNodes++;
            for(int i = 0; i < this->numberOfNodes; i++){
                lastRow->Append(0);
            }

            this->graph->Append(*lastRow);
        }

        void createRib(int pointA, int pointB){
            this->graph->GetPtr(pointA)->set(pointB, 1);
        }

        void removeRib(int pointA, int pointB){
            this->graph->GetPtr(pointA)->set(pointB, 0);
        }

        arraySequence<arraySequence<int>>* getTable(){
            return this->graph;
        }
    private:
        arraySequence<arraySequence<int>>* graph = new arraySequence<arraySequence<int>>;
        arraySequence<T>* graphItems = new arraySequence<T>;
        int numberOfNodes = 0;
        int numberOfRibs = 0;
};

#endif //GRAPH_H