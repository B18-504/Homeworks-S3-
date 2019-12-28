TransportGraph::TransportGraph(int count)
{
    nodes_count = count;
    nodes_array = new TransportNode[count];
}

TransportGraph::TransportGraph(TransportGraph &&a)
{
    nodes_count = a.nodes_count;
    nodes_array = a.nodes_array;
    a.nodes_array = 0;
}

void TransportGraph::AddConnection(int from_id, int to_id, int interval, int duration, int offset)
{
    if((from_id > -1)*(from_id < nodes_count)*(to_id > -1)*(to_id < nodes_count))
    {
        if(nodes_array[from_id].last)
        {
            nodes_array[from_id].last->next = new TransportGraph::TransportNode::Connection(to_id, interval, duration, offset);
            nodes_array[from_id].last = nodes_array[from_id].last->next;
        }
        else
        {
            nodes_array[from_id].route_list = new TransportGraph::TransportNode::Connection(to_id, interval, duration, offset);
            nodes_array[from_id].last = nodes_array[from_id].route_list;
        }
    }
    else
    {
        throw OoR();
    }
}

void TransportGraph::GetRoute(int from_id, int to_id, int start_time, Route &result)
{
    if((from_id > -1)*(from_id < nodes_count)*(to_id > -1)*(to_id < nodes_count))
    {
        int *ETAs = new int[nodes_count];
        int *prev_id = new int[nodes_count];
        int *prev_connetcion_id = new int[nodes_count];
        int *path_connections_count = new int[nodes_count];
        char *is_done = new char[nodes_count](0);

        ETAs[from_id] = start_time;
        path_connections_count[from_id] = 0;
        PriorityQueue<int, int> &pending = *new BPlusPriorityQueue<int, int>(50);

        int *curr_ETA = ETAs + from_id;
        int *curr_id = &from_id;
        while(*curr_id != to_id)
        {
            if(is_done[*curr_id] != 2)
            {
                TransportGraph::TransportNode::Connection *curr_connection = nodes_array[*curr_id].route_list;
                int connection_id = 0;

                while(curr_connection)
                {
                    if(is_done[curr_connection->destination_id] != 2)
                    {
                        int tested_ETA = curr_connection->TT.GetTime(*curr_ETA);

                        if((tested_ETA < ETAs[curr_connection->destination_id]) + (is_done[curr_connection->destination_id] == 0))
                        {
                            ETAs[curr_connection->destination_id] = tested_ETA;
                            is_done[curr_connection->destination_id] = 1;
                            path_connections_count[curr_connection->destination_id] = path_connections_count[*curr_id] + 1;
                            prev_id[curr_connection->destination_id] = *curr_id;
                            prev_connetcion_id[curr_connection->destination_id] = connection_id;

                            pending.Enqueue(tested_ETA, curr_connection->destination_id);
                        }
                    }

                    curr_connection = curr_connection->next;
                    connection_id++;
                }

                is_done[*curr_id] = 2;
            }

            if(pending.GetCount())
            {
                pending.Dequeue(curr_ETA, curr_id);
            }
            else
            {
                result.nodes_count = 0;
                result.nodes_ids = 0;
                result.connections_ids = 0;
                result.ETA = -1;

                return;
            }
        }

        result.nodes_count = path_connections_count[*curr_id] + 1;
        result.ETA = ETAs[*curr_id];
        result.nodes_ids = new int[result.nodes_count];
        result.connections_ids = new int[result.nodes_count - 1];

        result.nodes_ids[result.nodes_count - 1] = *curr_id;
        for(int i = result.nodes_count - 2; i > -1; i--)
        {
            result.connections_ids[i] = prev_connetcion_id[*curr_id];
            *curr_id = prev_id[*curr_id];
            result.nodes_ids[i] = *curr_id;
        }
    }
    else
    {
        throw OoR();
    }
}