#include<iostream>
#include<deque>
#include<list>

using namespace std;

#define INFINITY 9999

template<class G>
struct CNode
{
    typedef typename G::Edge    Edge;
    typedef typename G::N       N;

    N value;
    std::list<Edge*> edges;
};

template<class G>
struct CEdge
{
    typedef typename G::Node    Node;
    typedef typename G::E       E;

    E value;
    Node* nodes[2];
    bool dir; // 0 -> bidireccional, 1 -> [0]->[1]
};

template<class _N, class _E>
class CGraph
{
public:
    typedef CGraph<_N,_E>   G;
    typedef CNode<G>        Node;
    typedef CEdge<G>        Edge;
    typedef _N              N;
    typedef _E              E;

    Node* InsNode(N n);
    void InsEdge(Node* a, Node* b, E e, bool d);
    void adj_matrix(std::list<N> &valor);
    void Path(Node *a, Node *b,std::list<N> &road);
    void PrintPath(std::list<N> &road);
    void print();
    void dijkstra_algorithm(int **G, int sizee, int start, std::list<N> &path);

    std::deque<Node*> nodes;
};

template<class _N, class _E>
typename CGraph<_N,_E>::Node* CGraph<_N,_E>::InsNode(N n)
{
    Node* tmp = new Node;
    tmp->value = n;
    nodes.push_back(tmp);
    return tmp;

    return 0;
}

template<class _N, class _E>
void CGraph<_N,_E>::InsEdge(Node* a, Node* b, E e, bool d)
{
    Edge *tmp = new Edge;
    tmp->nodes[0]= a;
    tmp->nodes[1]= b;
    tmp->value = e;
    tmp->dir = d;

    a->edges.push_back(tmp);
    b->edges.push_back(tmp);
}

template<class _N, class _E>
void CGraph<_N,_E>::dijkstra_algorithm(int **G, int sizee, int start, std::list<N> &path ) {

    int cost[sizee][sizee], dist[sizee], pred[sizee];
    int visited[sizee], count, min_dist, next_node;

    for(int i = 0; i < sizee; ++i) {
        for (int j = 0; j < sizee; ++j) {
            if (G[i][j] == 0) cost[i][j] = INFINITY;
            else cost[i][j] = G[i][j];
        }
    }

    for(int i = 0; i < sizee; ++i) {
        dist[i]=cost[start][i];
        pred[i]=start;
        visited[i]=0;
    }
    dist[start]=0;
    visited[start]=1;
    count=1;

    while(count < sizee - 1) {
        min_dist=INFINITY;
        for(int i=0; i < sizee; ++i)
            if(dist[i] < min_dist && !visited[i]) {
                min_dist=dist[i];
                next_node=i;
            }
        visited[next_node]=1;

        for(int i=0 ; i < sizee ; ++i)
            if(!visited[i])
                if(min_dist + cost[next_node][i] < dist[i]) {
                    dist[i]= min_dist + cost[next_node][i];
                    pred[i]=next_node;
                }
        count++;
    }
    int f = 15;
    char str=97+f; // ascii
    path.push_front(str);
    int j=f;
    do {
        j=pred[j];
        char str2=97+j;
        path.push_front(str2);

    }while(j != start);
}

template<class _N, class _E>
void CGraph<_N,_E>::adj_matrix(std::list<N> &valor)
{
    int m = nodes.size(); // m = 16
    int **arr = new int*[m];
    for (int i = 0; i < m; ++i) {
        arr[i] = new int[m];
    }

    for(int i = 0; i < m; ++i){
        for(int j = 0; j < m; j++){
            arr[i][j] = 0;
        }
    }

    for(int i = 0; i < m; ++i){
        //char valor = nodes[i]->value;
        for(auto it = nodes[i]->edges.begin(); it != nodes[i]->edges.end(); ++it){
            if((*it)->dir == 1 and nodes[i] != (*it)->nodes[1]){
                for(int k = 0; k < m; ++k){
                    if(nodes[k] == (*it)->nodes[1]){
                        arr[i][k] = (*it)->value;
                        break; }
                }

            }
            else if((*it)->dir == 0 and nodes[i] == (*it)->nodes[1]){
                for(int k = 0; k < m; ++k){
                    if(nodes[k] == (*it)->nodes[0]){
                        arr[i][k] = (*it)->value;
                        break;
                    }
                }
            }
            else if((*it)->dir == 0 and nodes[i] == (*it)->nodes[0]){
                for(int k = 0; k < m; ++k){
                    if(nodes[k] == (*it)->nodes[1]){
                        arr[i][k] = (*it)->value;
                        break;
                    }
                }
            }

        }
    }
    std::list<N> res;
    dijkstra_algorithm(arr, m, 0, res);
    valor = res;
}

template<class _N, class _E>
void CGraph<_N,_E>::Path(Node *a, Node *b, std::list<N> &road)
{
    std::list<N> res;
    adj_matrix(res);
    road =res;
}

template<class _N, class _E>
void CGraph<_N,_E>::PrintPath(std::list<N> &road)
{
    std::cout<<"El camino es : ";
    for(auto it = road.begin(); it!=road.end(); ++it)
        std::cout<<*it<<"->";
    std::cout<<std::endl;
}

template <class _N, class _E>
void CGraph<_N, _E>::print(){

    for(int i = 0; i < nodes.size(); i++){
        std::cout <<"V"<<nodes[i]->value << "->";
        for(typename std::list<Edge*>::iterator it = nodes[i]->edges.begin(); it != nodes[i]->edges.end(); ++it){
            if ((*it)->nodes[0] == nodes[i])
                //std::cout <<(*it)->m_data <<" "<<(*it)->m_nodes[1]->m_data << " -> ";
                std::cout <<"V"<<(*it)->nodes[1]->value <<", W"<<(*it)->value << " -> "; //cuando la arista tiene direccion 1

            else if (!(*it)->dir)
                //std::cout <<(*it)->m_data <<" "<< (*it)->m_nodes[0]->m_data<< " <-> "; //cuando la arista es bidireccional
                std::cout <<"V"<<(*it)->nodes[0]->value<<", W"<< (*it)->value<< " <-> "; //cuando la arista es bidireccional
        } //mejorar esta parte si se puede
        std::cout << std::endl;
    }

}

int main()
{
    CGraph<char,int> g;
    CGraph<char,int>::Node* nodes[16];
    char data[16]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
    std::list<char> PathGraph;

    for(int i=0; i<16; i++)
        nodes[i] = g.InsNode(data[i]);

    g.InsEdge(nodes[0], nodes[1], 1, 0);
    g.InsEdge(nodes[1], nodes[2], 1, 0);
    g.InsEdge(nodes[1], nodes[5], 1, 0);
    g.InsEdge(nodes[3], nodes[7], 1, 0);
    g.InsEdge(nodes[4], nodes[5], 1, 0);
    g.InsEdge(nodes[4], nodes[8], 1, 0);
    g.InsEdge(nodes[5], nodes[6], 1, 0);
    g.InsEdge(nodes[5], nodes[9], 1, 0);
    g.InsEdge(nodes[6], nodes[7], 1, 0);
    g.InsEdge(nodes[6], nodes[10], 1, 0);
    g.InsEdge(nodes[8], nodes[9], 1, 0);
    g.InsEdge(nodes[9], nodes[10], 1, 0);
    g.InsEdge(nodes[9], nodes[13], 1, 0);
    g.InsEdge(nodes[10], nodes[11], 1, 0);
    g.InsEdge(nodes[10], nodes[14], 1, 0);
    g.InsEdge(nodes[11], nodes[15], 1, 0);
    g.InsEdge(nodes[12], nodes[13], 1, 0);
    g.InsEdge(nodes[13], nodes[14], 1, 0);

    cout << "grafo original: " << endl;
    g.print();
    cout << "\n\n";
    g.Path(nodes[0],nodes[15],PathGraph);
    g.PrintPath(PathGraph);
}