#pragma once

#include "Timetable.h"                  //probably should be moved to TransportNode.cpp
#include "PriorityQueue.h"

class Route
{
public:
    int nodes_count = 0;
    int *nodes_ids = 0;
    int *connections_ids = 0;
    int ETA;
};

class TransportGraph
{
public:                                         //private
    class TransportNode
    {
    public:
        class Connection
        {
        public:
            int destination_id;
            Timetable TT;

            Connection *next = 0;

            Connection() = delete;
            Connection(int, int, int, int);
            ~Connection() = default;            //to be replaced
        };

        Connection *route_list = 0;
        Connection *last = 0;

        TransportNode() = default;
        ~TransportNode() = default;             //to be replaced
    };

public:                                         //to be replaced (should be private)
    int nodes_count;
    TransportNode *nodes_array;

public:
    TransportGraph() = default;
    TransportGraph(int count);
    TransportGraph(TransportGraph&&);
    ~TransportGraph() = default;                //to be replaced

    void AddConnection(int, int, int, int, int);
    void GetRoute(int, int, int, Route&);
};

#include "TransportGraph.cpp"
#include "TransportNode.cpp"