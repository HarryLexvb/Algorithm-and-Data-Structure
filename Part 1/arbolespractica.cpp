#include <iostream>
#include <queue>
#include <list>
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
    void print_hojas_izquierdas(std::list<T>* l);
    void print_hojas_derechas(std::list<T>* l);
    void concatenar(std::list<T>* l);
    //void Print(std::list<T>* l);
    void Print();

private:
    CBinTreeNode<T>* root;
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
void CBinTree<T>::LevelOrder(CBinTreeNode<T>* n)  // amplitud
{
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
int CBinTree<T>::MaxDepth(CBinTreeNode<T>* n) //profundidad del árbol es decir cantidad de niveles
{
    if ( !n ) return 0;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T>
void CBinTree<T>::Print()
{
    InOrder(root);
    std::cout<<"\n";
}

template <class T>
void PreOrder_modificado(CBinTreeNode<T>* n, std::list<T>* L)
{
    if ( !n ) return;
    L->push_back(n->value);
    PreOrder_modificado(n->nodes[0], L);

    cout<<"vresion 1"<<endl;
    for ( auto i : *L )
        cout<<i<<" ";
}
template <class T>
void ReverseOrder_modificado(CBinTreeNode<T>* n, std::list<T>* L)
{
    if ( !n ) return;
    L->push_front(n->value);
    ReverseOrder_modificado(n->nodes[1], L);

    cout<<"vresion 1"<<endl;
    for ( auto i : *L )
        cout<<i<<" ";

}
template <class T>
void fillunion(CBinTreeNode<T>* n, std::list<T>* L)
{
    if ( !n ) return;
    L->push_front(n->value);
    ReverseOrder_modificado(n->nodes[1], L);L->pop_back();
    L->push_back(n->value);
    PreOrder_modificado(n->nodes[0], L);

    cout<<"vresion 1"<<endl;
    for ( auto i : *L )
        cout<<i<<" ";

}
template <class T>
void CBinTree<T>::print_hojas_izquierdas(std::list<T>* L)
{
    PreOrder_modificado(root, L);
    CBinTreeNode<T> *p = root; // creamos lista
    for(; p; p=p->nodes[0]) // llenamos con ´los valores del arbol
        L->push_back((p->value));

    cout<<"vresion 2"<<endl;
    for ( auto i : *L )
        cout<<i<<" ";
}

template <class T>
void CBinTree<T>::print_hojas_derechas(std::list<T>* L)
{
    ReverseOrder_modificado(root, L);
    CBinTreeNode<T> *p = root; //creamos lista
    for(; p; p=p->nodes[1])  //llenamos con los valores del arbol
        L->push_front(p->value);

    cout<<"vresion 2"<<endl;
    for ( auto i : *L )
        cout<<i<<" ";
}

template <class T>
void CBinTree<T>::concatenar(std::list<T>* L)
{
    //...
    fillunion(root, L);
    //juntamos las listas
    CBinTreeNode<T> *p = root;
    for(; p; p=p->nodes[1])
        L->push_front(p->value);
    p = root;
    for(p = p->nodes[0]; p; p=p->nodes[0])
        L->push_back((p->value));

    cout<<"vresion 2"<<endl;
    for ( auto i : *L )
        cout<<i<<" ";
}

int main(){
    CBinTree<int> t;
    std::cout<<"ins \n";
    t.Ins(65); t.Print();
    t.Ins(41); t.Print();
    t.Ins(79); t.Print();
    t.Ins(33); t.Print();
    t.Ins(51); t.Print();
    t.Ins(79); t.Print();
    t.Ins(68); t.Print();
    t.Ins(71); t.Print();
    t.Ins(81); t.Print();

    list<int> left;
    list<int> right;
    list<int> unionn;

    t.print_hojas_izquierdas(&left);
    t.print_hojas_derechas(&right);
    t.concatenar(&unionn);

    std::cout<<"\nmax depth \n";
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
    t.LevelOrder(t.Root());     std::cout<<"\n";
}