TransportGraph::TransportNode::Connection::Connection(int to_id, int interval, int duration, int offset)
{
    destination_id = to_id;
    TT.interval = interval;
    TT.duration = duration;
    TT.offset = offset;
}