#include <iostream>

using namespace std; 

class CVector{
public:
    CVector(int size){
        m_size = size;
        m_v = new int[m_size];
        m_nelem = 0;
    }
    ~CVector(){
        delete m_v;
    }
    
    void expand(){
        int* p = new int[2*m_size];
        for (int i = 0; i < m_size; i++)
            p[i] = m_v[i];
        delete m_v;
        m_v = p;
        m_size = 2*m_size;
    }
    
    void push_back(int x){
        if ( m_nelem == m_size )
            expand();
        m_v[m_nelem] = x;
        m_nelem++;
    }
    
    void pop_back(){ //Borra el último elemento del vector
        //nelem --;
        //collapse
        /*if(m_nelem == 0){
            throw std::exception("Pop back on empty vector!"); 
        }*/
        m_nelem--; 
         
    }
    
    void push_front(int x){
        if ( m_nelem == m_size )
            expand();
        for ( int i = m_nelem-1; i >= 0; i-- )
            m_v[i+1] = m_v[i];
        m_v[0] = x;
        m_nelem++;
    }
    
    void pop_front(){ //Borra el primer elemento del vector
        //nelem --;
        //collapse
        
    }
    
    int& operator[](int i){
        return m_v[i];
    }
    
    void print(){
        for (int i  = 0; i < m_nelem; i++)
            cout<<m_v[i]<<" ";
        cout<<endl;
    }
    
private:
    int* m_v;
    int m_size;
    int m_nelem;
};

///HACER LA MISMA IMPLEMENTACION PERO USANDO NODOS Y LISTAS ENLAZADAS 

struct CNode{
    CNode(int x){
        value = x;
        next = prev = 0;
    }
    int value;
    CNode *next, *prev;
};

class CList{

public:
    bool empty();

    CList(){
        head = tail = 0;
        nelem = 0;
    }

    ~CList(){
        
    }
    
    void push_back(int x){
        CNode* n = new CNode(x);
        if (!nelem)
            head = tail = n;
        else
        {
            n->prev = tail;
            tail->next = n;
            tail = n;
        }
        nelem ++;
    }
    
    void pop_back(){
        //Borra el último elemento de la lista 
        if(empty()){
            cout<<"No element to pop\n";
            return;
        }
        CNode *ptr=head;
        if(head->next==nullptr){
            head=nullptr;
            tail=nullptr;
        }
        while(ptr->next->next != nullptr){
            ptr=ptr->next;
        }
        tail=ptr;
        ptr->next=nullptr;
    }
    
    void push_front(int x){
        CNode* n = new CNode(x);
        if (!nelem)
            head = tail = n;
        else
        {
            n->next = head;
            head->prev = n;
            head = n;
        }
        nelem++;
    }

    void pop_front(){
        //Borra el primer elemento de la lista 
        if (empty()){
        cout<<"No element to pop.\n";
        return;
        }
        head=head->next;
        if(head==nullptr)
            tail=nullptr;
    }
    
    int& operator[](int i){
        CNode* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->value;
    }
    
    void print(){
        std::cout<<"\n";
        for (CNode* n = head; n != 0; n = n->next )
            std::cout<<n->value<<" ";
    }
    void print2(){
        std::cout<<"\n";
        for (int i = 0; i < nelem; i++)
            std::cout<<(*this)[i]<<" ";
    }
    
private:
    CNode* head, *tail;
    int nelem;
};
bool CList::empty(){
    return head==nullptr;
}

template <class T, class S>
class Cstack{

    void push(T x)
    {
        seq.push_back(x); 
    }
    void pop()
    {
        seq.pop_back();
    }
private: 
    S seq; 
};

template <class T, class S>
class CQueue{
public:
    void push(T x)
    {
        seq.push_back(x);
    }
    void pop()
    {
        seq.pop_front();
    }
private:
    S seq; 
};

int main(){

	cout << "\n\n---------------VECTOR----------------\n\n"; 

	CVector v(5);
    v.push_back(2);
    v.push_back(7);
    v.push_back(9);
    v.push_back(1);
    v.push_back(3);
    v.push_back(8);
    v.push_front(6);
    v.push_front(4);    
    v.pop_front();
    //v.pop_back();
    
    v.print();

    //int a = v[2];
    //v[2] = 1;

    cout << "\n\n---------------LISTA----------------\n\n"; 

	//DATOS PARA LA LISTA 
	CList l;
    l.push_back(2);
    l.push_back(7);
    l.push_back(9);
    l.push_back(1);
    l.push_back(3);
    l.push_back(8);
    l.push_front(6);
    l.push_front(4);
    //l.pop_front();
    //l.pop_back();
    
    l.print();
    //l.print2();    
   	//cout<<"\n\nelem 4: "<<l[4]<<"\n";

    cout << "\n\n---------------DEQUE----------------\n\n"; 	
    /*
        la clase deque es un hibirdo de la clase lista y la clase vector 
        este nuevo algoritmo es mucho mas eficiente ya que posee las mejores 
        caracteristicas de la clase lista y la clase vector 
    */

    cout << "\n\n---------------STACK----------------\n\n"; 

    Cstack<int, CList<int>> s; 
    s.push(3);  
    s.push(6);  
    s.push(1);  
    s.pop();
    s.pop(); 

    cout << "\n\n---------------QUEUE----------------\n\n"; 

    CQueue<int, CList<int>> q; 
    q.push(3);  
    q.push(6);  
    q.push(1);  
    q.pop();
    q.pop(); 
}
