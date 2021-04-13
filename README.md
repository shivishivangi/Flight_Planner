# CS225 Final Project: What's the Shortest Flight From A to B?

## Group Members: Angeline Prabakar, Sohini Roy, Shivangi Sharma 

### What does Our Project do?

For our final project, we constructed a graph using Airports from all over the world and their distances from each other to determine the shortest path from an Airport A to Airport B. Through using our program, the user can input source and destination Airport IATA codes and be shown the shortest path of connecting flights to the destination they desire.

### DataSet Used:

Using 2 data sets (one providing flight routes and the other providing the latitudes and longitudes of an airports), our group parsed through the 2 datasets and constructed the graph. The Airports became vertexes with the routes acting as an edge. The distances between the routes became the distance. We connected the datasets by comparing the IATA codes which were provided in both datasets. Included below are the datasets we used:

Airports DataSet: https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat

Routes DataSet: https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat

### Algorithms Used:

In our implementation of finding the shortest flight from the user's source to their destination, we used Breadth First Search using Dijkstra's Algorithm. Dijkstra's algorithm, similar to Prim's algorithm of the minimum spanning tree, generates the shortest path from Vertex A to Vertex B using the weights of the edges provided. By storing the "edges" into a priority queue, we determined the path that would get us to the specific user destination in the shortest amount of time via airplane.

### Visual Model:

For our project, we visually recreated the graph we coded using the latitudes and longitudes of the airports as coordinates for our vertexes. By creating lines from the vertexes, we also added edges to our image. Finally, by using the user's source and destination IATA code, we created the highlighted shortest path.


