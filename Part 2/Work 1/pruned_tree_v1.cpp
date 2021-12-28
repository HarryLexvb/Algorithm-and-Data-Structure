#include <iostream>
#include <list>
#include <queue>
#include <iomanip>
#include <vector>

using namespace std;

template <class T>
struct CBinTreeNode
{
    CBinTreeNode(T v)
    {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    T value;
    CBinTreeNode<T>* nodes[2]; //0 left, 1 right
};

template <class T>
class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    CBinTreeNode<T>* Root();
    bool Find(T x, CBinTreeNode<T>**& p);
    bool Ins(T x);
    bool Rem(T x);
    CBinTreeNode<T>** Rep(CBinTreeNode<T>** p);
    void InOrder(CBinTreeNode<T>* n);
    void PreOrder(CBinTreeNode<T>* n);
    void PosOrder(CBinTreeNode<T>* n);
    void ReverseOrder(CBinTreeNode<T>* n);
    void LevelOrder(CBinTreeNode<T>* n);
    int MaxDepth(CBinTreeNode<T>* n);
    void Print();
    void post(CBinTreeNode<T>* p, int indent=0);

    CBinTreeNode<T>* root;

private:
    //CBinTreeNode<T>* root;
    bool brep;
};

template <class T>
CBinTree<T>::CBinTree()
{
    root = 0;
    brep = 0;
}

template <class T>
CBinTree<T>::~CBinTree()
{
    //...
}

template <class T>
CBinTreeNode<T>* CBinTree<T>::Root()
{
    return root;
}

template <class T>
bool CBinTree<T>::Find(T x, CBinTreeNode<T>**& p)
{
    /*
    p=&root; // inicio
    while(*p && (*P)->value != 0) //pregunta
        p=&((*p)->nodes[(*p)->value < x]);  //salto

    return *p != 0;
    */
    for (   p = &root;
            *p && (*p)->value != x;
            p = &((*p)->nodes[ (*p)->value < x ])
            );
    return *p != 0;
}

template <class T>
bool CBinTree<T>::Ins(T x)
{
    CBinTreeNode<T>** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinTreeNode<T>(x);
    return 1;
}

template <class T>
bool CBinTree<T>::Rem(T x)
{
    CBinTreeNode<T>** p;
    if ( !Find(x,p) ) return 0;
    if ( (*p)->nodes[0] && (*p)->nodes[1] )
    {
        CBinTreeNode<T>** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinTreeNode<T>* t = *p;
    *p = (*p)->nodes[ (*p)->nodes[1] != 0 ];
    delete t;
    return 1;
}

template <class T>
CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p)  // función de reemplazo
{
    CBinTreeNode<T>** q;
    for ( q = &(*p)->nodes[!brep];
          (*q)->nodes[brep];
          q = &(*q)->nodes[brep] );
    brep = !brep;
    return q;
}

template <class T>
void CBinTree<T>::InOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    std::cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

template <class T>
void CBinTree<T>::PreOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    std::cout<<n->value<<" ";
    PreOrder(n->nodes[0]);
    PreOrder(n->nodes[1]);
}

template <class T>
void CBinTree<T>::PosOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    PosOrder(n->nodes[0]);
    PosOrder(n->nodes[1]);
    std::cout<<n->value<<" ";
}

template <class T>
void CBinTree<T>::ReverseOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    ReverseOrder(n->nodes[1]);
    std::cout<<n->value<<" ";
    ReverseOrder(n->nodes[0]);
}

template <class T>
void CBinTree<T>::LevelOrder(CBinTreeNode<T>* n)
{   // amplitud

    /*
    std::queue< CBinTreeNode<T>* > q;
    if ( !root ) return;
    q.push(root); //inicio
    while(!q.empty()){ //pregunta
        std::cout << q.front() << "\n";
        if ( q.front()->nodes[0] ) q.push( q.front()->nodes[0] );
           if ( q.front()->nodes[1] ) q.push( q.front()->nodes[1] );
           q.pop(); //incremento
    }
    */
    if ( !root ) return;
    std::queue< CBinTreeNode<T>* > q;
    for ( q.push(root); !q.empty(); q.pop() )
    {
        std::cout<<q.front()->value<<" ";
        if ( q.front()->nodes[0] ) q.push( q.front()->nodes[0] );
        if ( q.front()->nodes[1] ) q.push( q.front()->nodes[1] );
    }
}

template <class T>
int CBinTree<T>::MaxDepth(CBinTreeNode<T>* n)
{
    //profundidad del árbol es decir cantidad de niveles
    if ( !n ) return 0;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T>
void CBinTree<T>::Print()
{
    InOrder(root);
    std::cout<<"\n";
}

/////////para imprimir bonito///////////////////
template <class T>
void CBinTree<T>::post(CBinTreeNode<T>* p, int indent)
{
    if(p != NULL) {
        if(p->nodes[1]) {
            post(p->nodes[1], indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->nodes[1]) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< p->value << "\n ";
        if(p->nodes[0]) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            post(p->nodes[0], indent+4);
        }
    }
}
template<class T>
void Podar(CBinTreeNode<T>*&nodo)
{
    // Algoritmo recursivo, recorrido en postorden
    if(nodo) {
        Podar(nodo->nodes[0]); // Podar izquierdo
        Podar(nodo->nodes[1]);   // Podar derecho
        delete nodo;            // Eliminar nodo
        nodo = NULL;
    }
}

int main(){

    CBinTree<int> t;
    std::cout<<"arbol \n";
    t.Ins(50); //t.Print();
    t.Ins(40); //t.Print();
    t.Ins(80); //t.Print();
    t.Ins(30); //t.Print();
    t.Ins(43); //t.Print();
    t.Ins(60); //t.Print();
    t.Ins(95); //t.Print();
    t.Ins(20); //t.Print();
    t.Ins(35); //t.Print();
    t.Ins(73); //t.Print();
    t.Ins(90); //t.Print();
    t.Ins(99); //t.Print();
    t.Ins(10); //t.Print();b
    t.Ins(28); //t.Print();
    t.Ins(70); //t.Print();
    //t.post(t.root);
    //Podar(t.root);
    t.post(t.root); 

    /*
    std::cout<<"max depth \n";
    std::cout<<t.MaxDepth(t.Root())<<"\n";

    std::cout<<"rem \n";
    t.Rem(33); t.Print();
    t.Rem(68); t.Print();
    t.Rem(65); t.Print();

    std::cout<<"DepthFirst\n";
    t.InOrder(t.Root());        std::cout<<"\n";
    t.PreOrder(t.Root());       std::cout<<"\n";
    t.PosOrder(t.Root());       std::cout<<"\n";
    t.ReverseOrder(t.Root());   std::cout<<"\n";
    std::cout<<"BreadthFirst\n";
    t.LevelOrder(t.Root());     std::cout<<"\n";*/
}
