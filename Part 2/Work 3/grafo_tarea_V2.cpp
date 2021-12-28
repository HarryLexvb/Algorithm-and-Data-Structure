#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <thread>
#include <limits>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;

template <typename weight_type>
struct Neighbor
{
    int vertex;
    weight_type weight;
    explicit Neighbor(int v) : vertex(v) {}
    Neighbor(int v, weight_type w) : vertex(v), weight(w) {}
};

template <typename vertex_type, typename weight_type>
class CGraph
{
private:
    void operator=(const CGraph&) = delete; // protect assignment
    CGraph(const CGraph&) = delete;  // protect copy constructor

public:
    CGraph() = default;
    virtual ~CGraph() = default;

    virtual int V() const =0; // returns the number of vertices in the graph
    virtual int E() const =0; // returns the number of edges in the graph

    virtual bool adjacent(int x, int y) const =0; // tests whether there is an edge from node "x" to node "y"
    virtual vector< Neighbor<weight_type> > neighbors(int x) const =0; // return list of all vertices which have edge with "x"

    virtual void InsEdge(int x, int y) =0; // adds to graph the edge from x to y, if it is not there
    virtual void RemEdge(int x, int y) =0; // removes the edge from x to y, if it is there

    virtual vertex_type get_node_value(int x) const =0; // returns the value associated with the node x
    virtual void set_node_value(int x, vertex_type value) =0; // sets the value associated with the node x to a

    virtual weight_type get_edge_value(int x, int y) =0; // returns the value associated to the edge (x,y)
    virtual void set_edge_value(int x, int y, weight_type v) =0; // sets the value associated to the edge (x,y) to v
};

/// Adjacency list-based implementation of graph ADT test 1
template <typename vertex_type, typename weight_type>
class ListGraph : public CGraph<vertex_type, weight_type>
{
private:
    int Number_Vertex, Number_Edge;
    vector< vector<Neighbor<weight_type> > > AdjacencyList;
    vector<vertex_type> vertices; // store nodes values

public:
    ListGraph() {}
    ListGraph(int numVert) : Number_Vertex(numVert), Number_Edge(0)
    {
        vertices.reserve(Number_Vertex);
        AdjacencyList.reserve(Number_Vertex);

        for (int i = 0; i < Number_Vertex; i++)
        {
            AdjacencyList.push_back(vector< Neighbor<weight_type> >());
            AdjacencyList[i].reserve(Number_Vertex);
        }
    }
    ~ListGraph() { }

    int V() const { return Number_Vertex; }
    int E() const { return Number_Edge; }

    bool adjacent(int x, int y) const
    {
        return find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
            return elem.vertex == y;
        }) != AdjacencyList[x].end();
    }

    vector<Neighbor<weight_type> > neighbors(int x) const
    {
        return AdjacencyList[x];
    }

    void InsEdge(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        InsEdge(x, y, weight_type()); // cannot predict default value for "weight_type", use possible default constructor
        // it's assumed weight_type = double, it's just 0.0
    }

    // overloaded version with edge value for 3rd argument
    void InsEdge(int x, int y, weight_type w)
    {
        assert(x >= 0 || y >= 0 || w >= 0);
        for (auto &it : AdjacencyList[x])
        {
            if (it.vertex == y)
            {
                it.weight = w;
                return;
            }
        }
        Number_Edge++;
        AdjacencyList[x].push_back(Neighbor<weight_type>(y,w));
    }

    void RemEdge(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        // look for the "y" vertex in the adj list
        auto nit = find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
            return elem.vertex == y;
        });
        if (nit != AdjacencyList[x].end()) // if find - erase
        {
            Number_Edge--;
            AdjacencyList[x].erase(nit);
        }
    }

    vertex_type get_node_value(int x) const
    {
        assert(x >= 0);
        return vertices[x];
    }

    void set_node_value(int x, vertex_type value)
    {
        if (x >= 0) return;
        vertices[x] = value;
    }

    weight_type get_edge_value(int x, int y)
    {
        assert(x >= 0 || y >= 0);
        auto nit = find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
            return elem.vertex == y;
        });
        if (nit != AdjacencyList[x].end())
            return nit->weight;
        return weight_type(); // return 0.0 if there's no edge
    }

    void set_edge_value(int x, int y, weight_type w)
    {
        assert(x >= 0 || y >= 0);
        auto nit = find_if(AdjacencyList[x].begin(), AdjacencyList[x].end(), [&y](Neighbor<weight_type> elem){
            return elem.vertex == y;
        });
        if (nit != AdjacencyList[x].end())
            nit->weight = w;
    }

    void print()
    {
        cout << "\n--------------------graph-----------------------\n\n";
        /*cout << "Number of vertices: " << Number_Vertex << endl;
        cout << "Number of edges: " << Number_Edge << endl;*/
        for (int i = 0; i < Number_Vertex; i++)
        {
            cout << "V" << i << ": ";
            for (auto &elem : AdjacencyList[i])
                cout << "[V" << elem.vertex << ", w" << elem.weight << "] ";
            cout << endl;
        }
    }
};

/// Class containing implementation of Dijkstra algorithm
template <typename vertex_type, typename weight_type>
class Shortest_Path
{
    CGraph<vertex_type, weight_type> *g;
    vector<weight_type> min_distance; // store distances from source veritice
    vector<int> previous; // store history of visiting, helps to restore the shortest path
    vector<int> _path; // store shortest path
public:
    Shortest_Path(CGraph<vertex_type, weight_type> *_g) : g(_g) {}

    // Dijkstra algorithm implementation
    vector< int > path(int source, int target)
    {
        int n = g->V(); // number of vertices
        min_distance.clear();
        min_distance.resize(n, numeric_limits<double>::infinity()); // set distances to infinity
        min_distance[source] = 0;

        previous.clear();
        previous.resize(n, -1); // store vertices to reproduce the shortest path
        _path.clear();

        priority_queue< pair<weight_type, int>,
                vector<pair<weight_type, int> >,
                greater<pair<weight_type, int> > > vertex_queue; // min-heap
        vertex_queue.push(make_pair(min_distance[source], source)); // put the start vertice to queue

        // iterate until queue is empty
        while (!vertex_queue.empty())
        {
            weight_type dist = vertex_queue.top().first; // distance
            int u = vertex_queue.top().second; // vertex
            vertex_queue.pop();

            if (dist < min_distance[u])
                continue;

            const vector<Neighbor<weight_type>> &neighbors = g->neighbors(u); // get all neighbors of "u"
            for (auto &neighbor : neighbors) // iterate over neighbors
            {
                int v = neighbor.vertex;
                weight_type weight = neighbor.weight;
                weight_type distance_through_u = dist + weight; // calcualate the cost
                if (distance_through_u < min_distance[v])
                {
                    min_distance[v] = distance_through_u;
                    previous[v] = u;
                    vertex_queue.push(make_pair(min_distance[v], v)); // push on top of heap the most "effective" vertex
                }
            }
        }
        // retrieve the path vertices
        int targetVertex = target;
        for (; target != -1; target = previous[target])
        {
            _path.push_back(target);
        }
        reverse(_path.begin(), _path.end()); // set correct order for path vertices
        if (_path.size() < 2)
            cout << "";
        //cout << "There's no path to " << targetVertex << ".\n";
        return _path;
    }

    // Calculate the cost as sum of distances between path vertices
    weight_type path_size(int source, int target)
    {
        path(source, target);
        weight_type sum = 0;

        for (int i = 0; i < _path.size() - 1; i++)
        {
            sum += g->get_edge_value(_path[i], _path[i+1]);
        }
        if (sum == 0) return -1;
        return sum;
    }
};

template<class T>
void cal(ListGraph<int,double> &g, T num_v){

    cout << "---------------MATRIX-----------------------------\n\n";
    Shortest_Path<int, double> sp(reinterpret_cast<CGraph<int, double> *>(&g));
    cout << "    | origen\t|    destino |  peso |  ruta\n";
    /*for(int i=1; i<6; ++i) {
        for (int j = 1; j <6; ++j) {
            auto path = sp.path(i, j);
            if(i == j) {
                cout << "\t" << i << "\t-\t" << j << "\t" << sp.path_size(i, j);
                cout << "\t -1" << endl;
            }else {
                cout << "\t" << i << "\t-\t" << j << "\t" << sp.path_size(i, j);cout << "\t";
                copy(path.begin(), path.end(), ostream_iterator<int>(cout, "->"));
                cout << endl;
            }
        }
    } // */
    int arr[(num_v-1)^2][2]; //arr[(vertices-1)^2][2]
    for(int i=1; i<num_v; ++i){ //(int i=1; i<vantidad de vertices; ++i
        for(int j=1; j<num_v; ++j){ //(int j=1; j<vantidad de vertices; ++i
            auto path = sp.path(i, j);
            arr[i][j]=sp.path_size(i, j);
            if(i == j) {
                cout << "\t" << i << "\t-\t" << j << "\t" << arr[i][j];
                cout << "\t -1" << endl;
            }else {
                cout << "\t" << i << "\t-\t" << j << "\t" << arr[i][j]; cout << "\t";
                copy(path.begin(), path.end(), ostream_iterator<int>(cout, "->")); cout << endl;
            }
        }
        cout << endl;
    }
    int o , d;
    vector<int> a;
    cout << "ingrese origen: "; cin >> o;
    cout << "ingrese destino: "; cin >> d;
    auto path = sp.path(o, d);
    cout << "\nla distancia de " << o << " a " << d << " es de: "; cout << arr[o][d] << endl;
    cout << "\nY la ruta que debes tomar es: "; copy(path.begin(), path.end(), ostream_iterator<int>(cout, "->")); //*/

}

template <class T>
void test()
{
    int num_v = 6;  //number of vertices
    ListGraph<int,double> g(num_v);
    // 0
    g.InsEdge(1, 2, 2);
    g.InsEdge(1, 5, 10);
    // 1
    g.InsEdge(2, 3, 3);
    g.InsEdge(2, 5, 7);
    // 2
    g.InsEdge(3, 1, 4);
    g.InsEdge(3, 4, 4);
    // 3
    g.InsEdge(4, 5, 5);
    // 4
    g.InsEdge(5, 3, 3);
    g.print();
    cal<int>(g, num_v);//graph, origin, destiny, number of vertices

}

int main()
{
    /*int o , d;
    cout << "ingrese origen: "; cin >> o;
    cout << "ingrese destino: "; cin >> d;*/

    thread t(test<int>);
    t.join(); // */

    /*cout << "    | origen\t|    destino |  peso |  ruta\n";
    for(int i=1; i<6; i++) {
        for (int j = 1; j < 6; j++) {
            thread t(test<int>, i, j);
            t.join();
        }
    }*/

    return 0;
}