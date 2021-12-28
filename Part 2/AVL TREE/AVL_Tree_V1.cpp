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
        height = 1;
    }
    T value;
    int height;
    CBinTreeNode<T>* nodes[2]; //0 left, 1 right
};

template <class T>
class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    CBinTreeNode<T>* Root();
    //////////////////////////AVL algorithm///////////////////////////////////

    ///////////////////////////////////////////////////////////////////////
    bool Find(T x, CBinTreeNode<T>**& p);
    //bool Ins(T x);
    void Ins(T x);
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
    //////////////////////////////////PRINT 2////////////////////////////////////////////
    void print_2(CBinTreeNode<T>* p, int indent=0);

    CBinTreeNode<T>* root;


private:
    ////////////AVL ALGORITHM /////////////////////////////////////////////////////////////
    int height(CBinTreeNode<T>* head){
        if(head==NULL) return 0;
        return head->height;
    }
    CBinTreeNode<T> * rightRotation(CBinTreeNode<T>* head){
        CBinTreeNode<T>* newhead = head->nodes[0];
        head->nodes[0] = newhead->nodes[1];
        newhead->nodes[1] = head;
        head->height = 1+max(height(head->nodes[0]), height(head->nodes[1]));
        newhead->height = 1+max(height(newhead->nodes[0]), height(newhead->nodes[1]));
        return newhead;
    }
    CBinTreeNode<T>* leftRotation(CBinTreeNode<T>* head){
        CBinTreeNode<T>* newhead = head->nodes[1];
        head->nodes[1] = newhead->nodes[0];
        newhead->nodes[0] = head;
        head->height = 1+max(height(head->nodes[0]), height(head->nodes[1]));
        newhead->height = 1+max(height(newhead->nodes[0]), height(newhead->nodes[1]));
        return newhead;
    }
    CBinTreeNode<T>* insertUtil(CBinTreeNode<T>* head, T x){
        if(head==NULL){
            int n;
            n+=1;
            CBinTreeNode<T>* temp = new CBinTreeNode<T>(x);
            return temp;
        }
        if(x < head->value) head->nodes[0] = insertUtil(head->nodes[0], x);
        else if(x > head->value) head->nodes[1] = insertUtil(head->nodes[1], x);
        head->height = 1 + max(height(head->nodes[0]), height(head->nodes[1]));
        int bal = height(head->nodes[0]) - height(head->nodes[1]);
        if(bal>1){
            if(x < head->nodes[0]->value){
                return rightRotation(head);
            }else{
                head->nodes[0] = leftRotation(head->nodes[0]);
                return rightRotation(head);
            }
        }else if(bal<-1){
            if(x > head->nodes[1]->value){
                return leftRotation(head);
            }else{
                head->nodes[1] = rightRotation(head->nodes[1]);
                return leftRotation(head);
            }
        }
        return head;
    }
    /*CBinTreeNode<T>* removeUtil(CBinTreeNode<T>* head, T x){
        if(head==NULL) return NULL;
        if(x < head->value){
            head->nodes[0] = removeUtil(head->nodes[0], x);
        }else if(x > head->value){
            head->nodes[1] = removeUtil(head->nodes[1], x);
        }else{
            CBinTreeNode<T>* r = head->nodes[1];
            if(head->nodes[1]==NULL){
                CBinTreeNode<T>* l = head->nodes[0];
                delete(head);
                head = l;
            }else if(head->nodes[0]==NULL){
                delete(head);
                head = r;
            }else{
                while(r->nodes[0]!=NULL) r = r->nodes[0];
                head->value = r->value;
                head->nodes[1] = removeUtil(head->nodes[1], r->value);
            }
        }
        if(head==NULL) return head;
        head->height = 1 + max(height(head->nodes[0]), height(head->nodes[1]));
        int bal = height(head->nodes[0]) - height(head->nodes[1]);
        if(bal>1){
            if(height(head->nodes[0]) >= height(head->nodes[1])){
                return rightRotation(head);
            }else{
                head->nodes[0] = leftRotation(head->nodes[0]);
                return rightRotation(head);
            }
        }else if(bal < -1){
            if(height(head->nodes[1]) >= height(head->nodes[0])){
                return leftRotation(head);
            }else{
                head->nodes[1] = rightRotation(head->nodes[1]);
                return leftRotation(head);
            }
        }
        return head;
    }*/
///////////////////////////////////////////////////////////////////////////////////////////
    //CBinTreeNode<T>* root;
    bool brep;
};

template <class T>
CBinTree<T>::CBinTree() ///constructor
{
    root = 0;
    brep = 0;
}

template <class T>
CBinTree<T>::~CBinTree() ///destructor
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
void CBinTree<T>::Ins(T x)
{
    ///implementacion original es un bool
    /*CBinTreeNode<T>** p;
    if ( Find(x,p) )
        return 0;
    *p = new CBinTreeNode<T>(x);
    return 1;*/
    root=insertUtil(root, x);
}

template <class T>
bool CBinTree<T>::Rem(T x)
{
    ///implementacion original es bool
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
    //root=removeUtil(root, x);
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

////////imprimir arbol no cool//////////////////////////////////////////////////////
template <class T>
void CBinTree<T>::Print()
{
    InOrder(root);
    std::cout<<"\n";
}

/////////imprimir el arbol cool////////////////////////////////////////////////////////
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
    vector<int> vec;
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
    cout << endl;
    /* std::vector<int> vec;
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
     } else
         cout << std::setw(40);


     for (int v : vec) {
         if (v != placeholder)
             cout << v << std::setw(separacion) << " " << std::setw(separacion - 1);
         else
             cout << " " << std::setw(separacion - 1);
     }
     cout << endl;*/
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
//////////////////////print 2 ///////////////////////////////////////////
template <class T>
void CBinTree<T>::print_2(CBinTreeNode<T>* p, int indent)
{
    if(p != NULL) {
        if(p->nodes[1]) {
            print_2(p->nodes[1], indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->nodes[1]) std::cout<<" /\n" << std::setw(indent) << ' ';
        std::cout<< p->value << "\n ";
        if(p->nodes[0]) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print_2(p->nodes[0], indent+4);
        }
    }
}

int main() {

    CBinTree<int> t;
    std::cout << "ARBOL ORGINAL \n\n";
    /*t.Ins(70);
    t.Ins(50);
    t.Ins(80);
    t.Ins(30);
    t.Ins(60);
    t.Ins(60);
    t.Ins(73);
    t.Ins(90);
    t.Ins(20);
    t.Ins(40);   // */
    /*t.Ins(6);
    t.Ins(2);
    t.Ins(8);
    t.Ins(1);
    t.Ins(4);
    t.Ins(3);
    t.Ins(7); // */

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
    t.Ins(70); //t.Print(); // */
    t.Rem(70);

    //t.Print();
    //t.print_1(t.root); cout << "\n\n";
    t.print_2(t.root);

}
