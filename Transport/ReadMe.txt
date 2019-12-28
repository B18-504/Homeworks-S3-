Transport.exe is a kinda shell with a set of commands for finding the best route transport graphs.

Transport graph is an array of nodes. Nodes have list of (one-way) connections with other nodes. A connection has such props as destination
node, timetable and local id (to identify it among all the other connections of a node). Timetable is just a set of three ints - interval
between deparutures, duration of trip and an offset.

Example: node 0 has 2 connections. Connection 0 of node 0 has destination = 1, interval = 10, duration = 20 and offset = 5.
It means that at node 0 there is a route, that departs at T = 5 (offset) + n*10 (interval) minutes (n can be /any/ int) and arrives at the next stop (node 1) 20
mins after (T = 5 + n*10 + 20).

Shell operates data with a set of commands. Available data types to store as 'variables' are int, TransportGraph and Route.
Before working with data, you have to declare it. Use the command 'create [data_type] [var_name]'.

Ints can be operated with cmds 'Print [int_name]' that prints the value of chosen int, 'Input [int_name]' which waits for your input and
converts it to an int.

--> create int a
--> Input a
3			//your input
--> Print a
3			//programm's response
-->

For TransportGraph, there is another Input command. It starts interactive input of the graph. First, you are supposed to enter the number
of nodes to be present in the graph and the overall number of connections between nodes (multiple connections between same nodes also
count). Then a cycle that requests connections data is launched (input where the connection goes from, to and its timetabe settings).
Note: connection's (local) id is determined when it is added. They are enumerated in the order they have been added.

To find the fastest route between points x -> y, which starts at time t use GetRoute [TG_name] [Route_name] [x] [y] [t]

--> create TransportGraph TG
--> Input TG
...
...
...
--> create int from
--> create int to
--> create int start_time
--> Input from
//input starting point
--> Input to
//input where you are going to
--> Input start_time
//input when you can start the route
--> create Route R
--> GetRoute TG R from to start_time
--> Print r

You will get an output with a list of strings formatted X: Y -> Z. It means once you are at node X, get to node Z via connection Y.
The last string tells you the ETA for the route.

You can also create TransportGraph TG, input it and print 'exec FindRoute.spt'. Then you will be supposed to enter x, y, t. Provided
that you've called the TransporGraph as 'TG', the programm will print you the result.