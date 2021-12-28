#include <iostream>
#include <queue>
using namespace std;

template<class T>
struct CLess
{
  inline bool operator()(T a, T b)
  { return a<b; }
};

template<class T>
struct CGreater
{
  inline bool operator()(T a, T b)
  { return a>b; }
};

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

template <class T, class C>
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
    
private:
    CBinTreeNode<T>* root;
    bool brep;
    C cmp;
};

template <class T, class C>
CBinTree<T,C>::CBinTree()
{
    root = 0;
    brep = 0;
}

template <class T, class C>
CBinTree<T,C>::~CBinTree()
{
    //...
}

template <class T, class C>
CBinTreeNode<T>* CBinTree<T,C>::Root()
{
    return root;
}

template <class T, class C>
bool CBinTree<T,C>::Find(T x, CBinTreeNode<T>**& p)
{
    for (   p = &root;
            *p && (*p)->value != x;
            p = &((*p)->nodes[ cmp((*p)->value,x) ] )
        );
    return *p != 0;
}

template <class T, class C>
bool CBinTree<T,C>::Ins(T x)
{
    CBinTreeNode<T>** p;
    if ( Find(x,p) ) return 0;
    *p = new CBinTreeNode<T>(x);
    return 1;
}

template <class T, class C>
bool CBinTree<T,C>::Rem(T x)
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

template <class T, class C>
CBinTreeNode<T>** CBinTree<T,C>::Rep(CBinTreeNode<T>** p)
{
    CBinTreeNode<T>** q;
    for ( q = &(*p)->nodes[!brep];
         (*q)->nodes[brep];
         q = &(*q)->nodes[brep] );
    brep = !brep;
    return q;
}

template <class T, class C>
void CBinTree<T,C>::InOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    std::cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

template <class T, class C>
void CBinTree<T,C>::PreOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    std::cout<<n->value<<" ";
    PreOrder(n->nodes[0]);
    PreOrder(n->nodes[1]);
}

template <class T, class C>
void CBinTree<T,C>::PosOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    PosOrder(n->nodes[0]);
    PosOrder(n->nodes[1]);
    std::cout<<n->value<<" ";
}

template <class T, class C>
void CBinTree<T,C>::ReverseOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    ReverseOrder(n->nodes[1]);
    std::cout<<n->value<<" ";
    ReverseOrder(n->nodes[0]);
}

template <class T, class C>
void CBinTree<T,C>::LevelOrder(CBinTreeNode<T>* n)
{
    if ( !root ) return;
    std::queue< CBinTreeNode<T>* > q;
    for ( q.push(root); !q.empty(); q.pop() )
    {
        std::cout<<q.front()->value<<" ";
        if ( q.front()->nodes[0] ) q.push( q.front()->nodes[0] );
        if ( q.front()->nodes[1] ) q.push( q.front()->nodes[1] );
    }
}

template <class T, class C>
int CBinTree<T,C>::MaxDepth(CBinTreeNode<T>* n)
{
    if ( !n ) return 0;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T, class C>
void CBinTree<T,C>::Print()
{
    InOrder(root);
    std::cout<<"\n";
}

int main()
{
    CBinTree<int, CGreater<int>> t;
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
    t.LevelOrder(t.Root());     std::cout<<"\n";
}




/*
 template <class T, class C>
 CBinTreeNode<T>** CBinTree<T,C>::Rep(CBinTreeNode<T>** p)
 {
     int b = rand()%2;
     CBinTreeNode<T>** q = &(*p)->nodes[b];
     while ( (*q)->nodes[!b] )
         q = &(*q)->nodes[!b];
     return q;
 }
 
 template <class T, class C>
 CBinTreeNode<T>** CBinTree<T,C>::Rep(CBinTreeNode<T>** p)
 {
     CBinTreeNode<T>** q = &(*p)->nodes[!brep];
     while ( (*q)->nodes[brep] )
         q = &(*q)->nodes[brep];
     brep = !brep;
     return q;
 }

 template <class T, class C>
 int CBinTree<T,C>::MaxDepth(CBinTreeNode<T>* n)
 {
     if ( !n ) return 0;
     int l, r;
     l = MaxDepth(n->nodes[0]);
     r = MaxDepth(n->nodes[1]);
     return (l>r ? l : r) + 1;
 }

 */

