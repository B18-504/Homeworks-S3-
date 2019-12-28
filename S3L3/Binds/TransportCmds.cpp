void InputTransportGraph(void ***argv)
{
    if(!(*(argv[0])))
    {
        *(argv[0]) = new TransportGraph;
    }

    Input(*(TransportGraph*)(*(argv[0])));
}

void PrintRoute(void ***argv)
{
    if(*(argv[0]))
    {
        Print(*(Route*)(*(argv[0])));
    }

    else
    {
        throw NPE();
    }
}

void GetRoute(void ***argv)
{
    if(*(argv[0]))
    {
        if(!(*(argv[1])))
        {
            *(argv[1]) = new Route;
        }

        ((TransportGraph*)(*(argv[0])))->GetRoute(*(int*)(argv[2]), *(int*)(argv[3]), *(int*)(argv[4]), *(Route*)(*(argv[1])));
    }
    else
    {
        throw NPE();
    }
}