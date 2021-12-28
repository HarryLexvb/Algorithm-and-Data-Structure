#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;
int placeholder;

unsigned long long binpow(unsigned long long a,  unsigned long long b) {
    ///algoritmo de la exponeciacion binaria
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

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
    /////////////////////////////////PRINT/////////////////////////////////////////////
    void print_1(CBinTreeNode<T> *n);
    void Print_Row(const CBinTreeNode<T> *n, const int height, int depth);
    void Get_Line(const CBinTreeNode<T> *n, int depth, vector<int>& vals);
    ////////////////////////////////PODAR//////////////////////////////////////////////
    int Get_Tree_Height(CBinTreeNode<T> *n); //retorna la altura del n
    int Get_Number_Nodes(CBinTreeNode<T> *n, int x); // retorna la cantidad de nodos en un determinado nivel
    void Podar(CBinTreeNode<T> *n); //Podar el arbol
    void Get_Nodes_Level(CBinTreeNode<T> *n, int x); //retorna los nodos de un determinado novel
    void Delete_Nodes_Level(CBinTreeNode<T> *n, int level); // borrar los nodos de un determinado nivel

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
    delete root;
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
CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p)
{
    // función de reemplazo (swap)
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
    ///profundidad del árbol es decir cantidad de niveles
    if ( !n ) return 0;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T>
void CBinTree<T>::Print()
{
    InOrder(root);
    std::cout<<"\n";
}

/////////para imprimir el arbol////////////////////////////////////////////////////////
template <class T>
void CBinTree<T>::print_1(CBinTreeNode<T> *n)
{   ///imprimir el arbol
    int height = MaxDepth(root);
    for (int i = 0 ; i < height; i ++) {
        Print_Row(n, height, i);
    }
}
template <class T>
void CBinTree<T>::Print_Row(const CBinTreeNode<T> *n, const int height, int depth)
{
/*    vector<int> vec;
    Get_Line(n, depth, vec);
    cout << setw((height - depth)*2); // scale setw with depth
    bool toggle = true; // start with left
    if (vec.size() > 1) {
        for (int v : vec) {
            if (v != placeholder) {
                if (toggle)
                    cout << "  /" << std::setw(4) << ' ';
                else
                    cout << "\\" <<std::setw(4) << ' ';
            }
            toggle = !toggle;
        }
        cout << endl;
        cout << setw((height - depth)*2);
    }
    for (int v : vec) {
        if (v != placeholder)
            cout << v <<std::setw(4) << ' ';
    }
    cout << endl;*/
    std::vector<int> vec;
    Get_Line(n, depth, vec);
    int separacion = 80 / (binpow(2, depth) * 2);
    bool toggle = true;
    if (vec.size() > 1) {
        cout << std::setw(separacion + 1);
        for (int v : vec) {
            if (v != placeholder) {
                if (toggle)
                    cout << "/" << std::setw(separacion - 2) << " " << std::setw(separacion - 1);
                else
                    cout << "\\" << std::setw(separacion + 1) << " " << std::setw(separacion);
            }else
                cout << " " << std::setw(separacion - 2);
            toggle = !toggle;
        }
        cout << endl;
        cout << std::setw(separacion);
        /*
        for (int v : vec) {
            if (v != placeholder) {
                if (toggle)
                    cout << "/" << std::setw(separacion) << " " << std::setw(separacion - 1);
                else
                    cout << "\\" << std::setw(separacion) << " " << std::setw(separacion - 1);
            } else
                cout << " " << std::setw(separacion - 1);
            toggle = !toggle;
        }
        cout << endl;
        cout << setw(separacion);*/
    } else
        cout << std::setw(40);


    for (int v : vec) {
        if (v != placeholder)
            cout << v << std::setw(separacion) << " " << std::setw(separacion - 1);
        else
            cout << " " << std::setw(separacion - 1);
    }
    cout << endl;
}
template <class T>
void CBinTree<T>::Get_Line(const CBinTreeNode<T> *n, int depth, vector<int>& vals)
{
    if (depth <= 0 && n != nullptr) {
        vals.push_back(n->value);
        return;
    }
    if (n->nodes[0] != nullptr)
        Get_Line(n->nodes[0], depth - 1, vals);
    else if (depth-1 <= 0)
        vals.push_back(placeholder);
    if (n->nodes[1] != nullptr)
        Get_Line(n->nodes[1], depth - 1, vals);
    else if (depth-1 <= 0)
        vals.push_back(placeholder);
}
/////////////////PARA PODAR//////////////////////////////////////////////////////////////
template <class T>
int CBinTree<T>::Get_Tree_Height(CBinTreeNode<T> * n)
{   ///retorna la altura del n
    int AltIzq, AltDer;

    if(n == nullptr)
        return -1;
    else
    {
        AltIzq = Get_Tree_Height(n->nodes[0]);
        AltDer = Get_Tree_Height(n->nodes[1]);

        if(AltIzq>AltDer)
            return AltIzq+1;
        else
            return AltDer+1;
    }
}
template <class T>
int CBinTree<T>::Get_Number_Nodes(CBinTreeNode<T> *n, int x){
    ///cuenta cuantos nodos hay en un determinado nivel
    if(n != nullptr){
        if(x == 0)
            return Get_Number_Nodes(n->nodes[0], x - 1) + Get_Number_Nodes(n->nodes[1], x - 1) + 1;
        return Get_Number_Nodes(n->nodes[0], x - 1) + Get_Number_Nodes(n->nodes[1], x - 1) ;
    }
    return 0;
}
template<class T>
void CBinTree<T>::Podar(CBinTreeNode<T> *n){
    ///empareja el arbol
    //cout << "altura: "<<Get_Tree_Height(n);
    /*for (int i =0; i <Get_Tree_Height(n)+1; ++i ){
        cout << "\nhijos en el nivel " << i << ": " <<Get_Number_Nodes(n,i);
    }*/
    for (int i = Get_Tree_Height(root); i >= 0; --i ) {
        if (Get_Number_Nodes(root, i) != binpow(2, i)) {
            cout << "el nivel " << i << " se borra" << endl;
            Delete_Nodes_Level(root, i);
        }
    }
    cout << "el arbol ya es perfecto, no se borra nada :D" << endl;
}
template <class T>
void CBinTree<T>::Get_Nodes_Level(CBinTreeNode<T> *n, int x){
    /// retorna los nodos que contienen ese nivel
    if (n != nullptr) {
        if (x == 0)
            cout << n->value << "  ";
        Get_Nodes_Level(n->nodes[0], x - 1);
        Get_Nodes_Level(n->nodes[1], x - 1);
    }
}
template <class T>
void CBinTree<T>::Delete_Nodes_Level(CBinTreeNode<T>* n, int level){
    /// borra la hojas de un determinado nivel
    if (n == nullptr) return;
    if (level == 0)
        n = reinterpret_cast<CBinTreeNode<int> *>(Rem(n->value));
    else if (level > 0)
    {
        Delete_Nodes_Level(n->nodes[0], level - 1);
        Delete_Nodes_Level(n->nodes[1], level - 1);
    }
}

int main() {

    CBinTree<int> t;
    std::cout << "arbol \n";
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
    t.Ins(10); //t.Print();
    t.Ins(28); //t.Print();
    t.Ins(70); //t.Print();
    t.print_1(t.root);
    //cout << "nodos de ese nivel: \n";
    /*for (int i = 0; i < Get_Tree_Height(t.root) + 1; ++i){
        Get_Nodes_Level(t.root, i);
        cout << endl;
    }*/
    //cout << "altura: "<<Get_Tree_Height(t.root);
    //cout << "\nhijos en el nivel " <<Get_Number_Nodes(t.root,4);
    //t.Get_Nodes_Level(t.root, 4);

    /*
     * El codigo fue probado en Clion, Replit y Visual Community, no presento errores al compilar
     * version c++ 20
     * */

    cout << endl;
    t.Podar(t.root);
    cout << endl;
    t.print_1(t.root);
}
