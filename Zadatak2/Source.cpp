#include <iostream>
#include <vector>
#include <string>
#include <list>

#include <limits> // for numeric_limits
#include <cmath>
#include <queue>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <thread>
#include <chrono>

using namespace std;

typedef int vertex_t;
typedef double weight_t;

//SIRINA I VISINA POLJA
/*
Ako zelim promjeniti da mi je tablica veca ili manja, moram promjeniti i uvjete za
gdje se nalazi zid, jer sam ih postavio fiksno.
*/
const int REDAK = 20;

const weight_t max_weight = std::numeric_limits<double>::infinity();

struct neighbor {
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }
};


struct Kordinata {
    int x, y;
};

typedef std::vector<std::vector<neighbor> > adjacency_list_t;
typedef std::pair<weight_t, vertex_t> weight_vertex_pair_t;

void DijkstraComputePaths(vertex_t source,
    const adjacency_list_t& adjacency_list,
    std::vector<weight_t>& min_distance,
    std::vector<vertex_t>& previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    // we use greater instead of less to turn max-heap into min-heap
    std::priority_queue<weight_vertex_pair_t,
        std::vector<weight_vertex_pair_t>,
        std::greater<weight_vertex_pair_t> > vertex_queue;
    vertex_queue.push(std::make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.top().first;
        vertex_t u = vertex_queue.top().second;
        vertex_queue.pop();

        // Because we leave old copies of the vertex in the priority queue
        // (with outdated higher distances), we need to ignore it when we come
        // across it again, by checking its distance against the minimum distance
        if (dist > min_distance[u])
            continue;

        // Visit each edge exiting u
        const std::vector<neighbor>& neighbors = adjacency_list[u];
        for (std::vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
            neighbor_iter != neighbors.end();
            neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) {
                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.push(std::make_pair(min_distance[v], v));

            }

        }
    }
}

void sredivanjeIgraca(int path, char grid[REDAK][REDAK]) {
    int x = path;
    int y = path / 20;
    int pocetno = 0;
    for (int i = 0; i < REDAK; i++)
    {
        for (int j = 0; j < REDAK; j++)
        {
            if (x == pocetno && y == i)
            {
                cout << "*";
                pocetno++;
        
            }
            else
            {
                cout << grid[i][j] << " ";
                pocetno++;
            }
        }
        cout << endl;
    }
}

void crtanje(char grid[REDAK][REDAK]) {
    for (size_t i = 0; i < REDAK; i++)
    {
        for (size_t j = 0; j < REDAK; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

std::list<vertex_t> DijkstraGetShortestPathTo(
    vertex_t vertex, const std::vector<vertex_t>& previous)
{
    std::list<vertex_t> path;
    for (; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}


int main()
{
    // remember to insert edges both ways for an undirected graph
    /*
    0   1   2  3
    4  |5|  6  7
    8   9   10 11
    12  13  14 15


    0 1 2 3 4 5 6 7 8 |9| 10 11 12 13 14 15 17 18 19 
    
    */

    /*
    0: i-> 0, j->-1 REDAK->4
    J*REDAK+I >= 0

    12: i->12 j->1 REDAK->4
    16 17 18 19

    */

    /*
    ZID: 10 20 30 40 50 60
    */



    adjacency_list_t adjacency_list(REDAK * REDAK);

    int A[2];
    int B[2];

    std::cout << "Unesite A.x: ";
    std::cin >> A[0];
    std::cout << "Unesite A.y: ";
    std::cin >> A[1];

    std::cout << "Unesite B.x: ";
    std::cin >> B[0];
    std::cout << "Unesite B.Y: ";
    std::cin >> B[1];

    char grid[REDAK][REDAK];

    //Inicijalizacija polja
    for (int i = 0; i < REDAK; i++)
    {

        for (int j = 0; j < REDAK; j++)
        {
            if (A[0] - 1 == j && A[1] - 1 == i)
            {
                grid[i][j] = 'A';
            }
            else if (B[0] - 1 == j && B[1] - 1 == i)
            {
                grid[i][j] = 'B';
            }
            else if ((j == 9 && i == 0) || (j == 9 && i == 1) || (j == 9 && i == 2) || (j == 9 && i == 3) || (j == 9 && i == 4) || (j == 9 && i == 5))
            {
                grid[i][j] = '#';
            }
            else
            {
                grid[i][j] = '-';
            }
        }

    }

    crtanje(grid);

    std::cout << std::endl;


    //Pronalazak puta
    for (size_t i = 0; i < adjacency_list.size(); i++)
    {
        if (i == 9 || i == 29 || i == 49 ||i == 69 || i == 89 ||i == 109)
        {
            adjacency_list[i].push_back(neighbor(i, 99));
        }
        else
        {
            for (int j : { -1, 1 }) {

                if (i % REDAK == 0)
                {
                    if (j == 1)
                    {
                        adjacency_list[i].push_back(neighbor(i + j, 1));
                    }
                }
                else if (i % REDAK == REDAK - 1)
                {
                    if (j == -1)
                    {
                        adjacency_list[i].push_back(neighbor(i + j, 1));
                    }
                }
                else
                {
                    adjacency_list[i].push_back(neighbor(i + j, 1));

                }
                int v = j * REDAK;

                if (v + i >= 0 && v + i < adjacency_list.size())
                {
                    adjacency_list[i].push_back(neighbor(v + i, 1));
                }
            }
        }
        
        
    }


   /* for (int i = 0; i < adjacency_list.size(); i++) {
        std::vector<neighbor> n = adjacency_list[i];
        std::cout << i << ":\t";
        for (size_t j = 0; j < n.size(); j++) {

            std::cout << n[j].target << "\t";
        }
        std::cout << std::endl;
    }*/
    int pathTo;
    int from;


    from = (((A[1] - 1) * REDAK) + A[0] - 1);
    pathTo = (((B[1] - 1) * REDAK) + B[0] - 1);
     


    //Vizazalizacija polja
  /*  int v = 0;
    cout << "FROM: " << from << "\t TO: " << pathTo << endl;

    for (size_t i = 0; i < REDAK; i++)
    {
        for (int j = 0; j < REDAK; j++)
        {
            cout << v << "\t";
            v++;
        }
        cout << endl;
    }*/

    std::vector<weight_t> min_distance;
    std::vector<vertex_t> previous;
    DijkstraComputePaths(from, adjacency_list, min_distance, previous);
    std::cout << "Distance from 0 to " << pathTo << ": " << min_distance[pathTo] << std::endl;
    std::list<vertex_t> path = DijkstraGetShortestPathTo(pathTo, previous);
    std::cout << "Path : ";
    std::copy(path.begin(), path.end(), std::ostream_iterator<vertex_t>(std::cout, " "));
    std::cout << std::endl;


  
 
    for (auto it = path.begin(); it != path.end(); ++it)
    {
     cout << endl << endl;
     this_thread::sleep_for(chrono::milliseconds(150));
     system("cls");
     int v = *it;
     sredivanjeIgraca(v, grid);
     }

    

    return 0;
}