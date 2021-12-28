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
    void InOrder(CBinTreeNode<T>* n);
    void PrintList(std::list<T>* l);

    void FillList_a(std::list<T>* l);
    void FillList_c(std::list<T>* l);
    void FillList_ca(std::list<T>* l);

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
void CBinTree<T>::InOrder(CBinTreeNode<T>* n)
{
    if ( !n ) return;
    InOrder(n->nodes[0]);
    std::cout<<n->value<<" ";
    InOrder(n->nodes[1]);
}

template <class T>
void CBinTree<T>::PrintList(std::list<T>* l)
{
    std::cout<<"\n";
    for ( auto i : *l )
        std::cout<<i<<" ";
}
template <class T>
void PreOrder_modificado(CBinTreeNode<T>* n, std::list<T>* L)
{
    if ( !n ) return;
    L->push_back(n->value);
    PreOrder_modificado(n->nodes[0], L);
}
template <class T>
void ReverseOrder(CBinTreeNode<T>* n,std::list<T>* L)
{
    if ( !n ) return;
    L->push_front(n->value);
    ReverseOrder(n->nodes[1],L);

}
template <class T>
void fill_C_fusion(CBinTreeNode<T>* n, std::list<T>* L)
{
    if ( !n ) return;
    L->push_front(n->value);
    ReverseOrder(n->nodes[1],L);L->pop_back();
    L->push_back(n->value);
    PreOrder_modificado(n->nodes[0], L);
}
template <class T>
void CBinTree<T>::FillList_a(std::list<T>* L)
{
    //...
    PreOrder_modificado(root, L);
}

template <class T>
void CBinTree<T>::FillList_c(std::list<T>* L)
{
    //...
    ReverseOrder(root,L);
}

template <class T>
void CBinTree<T>::FillList_ca(std::list<T>* L)
{
    //...
    fill_C_fusion(root, L);
}

int main()
{
    CBinTree<int> t;
    t.Ins(51);
    t.Ins(33);  t.Ins(69);
    t.Ins(22);  t.Ins(44);  t.Ins(60);  t.Ins(82);
    t.Ins(18);  t.Ins(25);  t.Ins(48);  t.Ins(55);  t.Ins(64);  t.Ins(73);
    t.Ins(61);  t.Ins(66);
    t.InOrder(t.Root());        std::cout<<"\n------\n";

    std::list<int> a,c,ca;

    t.FillList_a(&a);
    t.PrintList(&a);

    t.FillList_c(&c);
    t.PrintList(&c);

    t.FillList_ca(&ca);
    t.PrintList(&ca);
}