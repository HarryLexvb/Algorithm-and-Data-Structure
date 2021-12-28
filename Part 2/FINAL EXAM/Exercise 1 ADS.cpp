#include<iostream>
#include<deque>
#include<list>

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
    void Path(Node *a, Node *b,std::list<N> &road);
    void PrintPath(std::list<N> &road);

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
void CGraph<_N,_E>::Path(Node *a, Node *b, std::list<N> &road)
{
   
  road.push_back(a->value);
  //question code go here
  road.push_back(b->value);
}

template<class _N, class _E>
void CGraph<_N,_E>::PrintPath(std::list<N> &road)
{
  std::cout<<"El camino es : ";
  for(auto it = road.begin(); it!=road.end(); ++it)
      std::cout<<*it<<" ";
  std::cout<<std::endl;
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

    g.Path(nodes[0],nodes[15],PathGraph);
    g.PrintPath(PathGraph);
}
