#include <iostream>
using namespace std; 

////////////////////////////CLASE LIST//////////////////////////////////////////

template<class T>
struct CNode{
    CNode(T x)
    {
        value = x;
        next = prev = 0;
    }
    T value;
    CNode<T> *next, *prev;
};

template<class T>
class CList{
public:
    CList()
    {
        head = tail = 0;
        nelem = 0;
    }
    ~CList()
    {
        //...
    }
    bool empty(){
        return head==nullptr;
    }
        
    void push_back(T x)
    {
        CNode<T>* n = new CNode<T>(x);
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
    
    void pop_back()
    {
        //Borra el último elemento de la lista 
        if(empty()){
            cout<<"No element to pop\n";
            return;
        }
        CNode<T> *ptr=head;
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
    
    void push_front(T x)
    {
        CNode<T>* n = new CNode<T>(x);
        if (!nelem)
            head = tail = n;
        else
        {
            n->next = head;
            head->prev = n;
            head = n;
        }
        nelem ++;
    }
    
    void pop_front()
    {
        //borra el primer elemento de la lista 
        //Borra el primer elemento de la lista 
        if (empty()){
        cout<<"No element to pop.\n";
        return;
        }
        head=head->next;
        if(head==nullptr)
            tail=nullptr;
    }
    
    T& operator[](int i)
    {
        CNode<T>* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->value;
    }
    
    void print()
    {
        std::cout<<"\n";
        for (CNode<T>* n = head; n != 0; n = n->next )
            std::cout<<n->value<<" ";
    }
    void print2()
    {
        std::cout<<"\n";
        for (int i = 0; i < nelem; i++)
            std::cout<<(*this)[i]<<" ";
    
    }
    
private:
    CNode<T>* head, *tail;
    int nelem;
};

////////////////////////////CLASE VECTOR//////////////////////////////////////////

// en esta clase falta implementar el pop_front y collapse()

template<class T>
class CVector{
public:
    CVector(int size = 5)
    {
        m_size = size;
        m_v = new T[m_size];
        m_nelem = 0;
    }
    ~CVector()
    {
        delete m_v;
    }
    
    void expand()
    {
        T* p = new T[2*m_size];
        for (int i = 0; i < m_size; i++)
            p[i] = m_v[i];
        delete m_v;
        m_v = p;
        m_size = 2*m_size;
    }
    
    void push_back(T x)
    {
        if ( m_nelem == m_size )
            expand();
        m_v[m_nelem] = x;
        m_nelem++;
    }
    
    void pop_back()
    {
        m_nelem --; //este espara borrar el ultimo elemnto del vector 
        /*
            implementar el collapse() que consiste en: 
            si la mitad del tamaño del vector esta vacio se debera borrar dicha mitad vacia 
        */
    }
    
    void push_front(T x)
    {
        if ( m_nelem == m_size )
            expand();
        for ( int i = m_nelem-1; i >= 0; i-- )
            m_v[i+1] = m_v[i];
        m_v[0] = x;
        m_nelem++;
    }
    
    void pop_front()
    {

        //implementar el algoritmo para borrar el primer elemento del vector 

        /*
            implementar el collapse() que consiste en: 
            si la mitad del tamaño del vector esta vacio se debera borrar dicha mitad vacia 
        */
    }
    
    T& operator[](int i)
    {
        return m_v[i];
    }
    
    void print()
    {
        for (int i  = 0; i < m_nelem; i++)
            std::cout<<m_v[i]<<" ";
        std::cout<<std::endl;
    }
    
private:
    T* m_v;
    int m_size;
    int m_nelem;
};

///////////////////////////////CLASE STACK///////////////////////////////////////

template<class T, class S>
class CStack{
public:
    void push(T x)
    {   seq.push_back(x);   }
    void pop()
    {   seq.pop_back();     }
private:
    S seq;
};

///////////////////////////////CLASE QUEUE///////////////////////////////////////

template<class T, class S>
class CQueue{
public:
    void push(T x)
    {   seq.push_back(x);   }
    void pop()
    {   seq.pop_front();     }

private:
    S seq;
};

template<class T>
class CDeque{
public: 
    CDeque()
    {
        //constructor 
    }
    ~CDeque()
    {
        //destructor
    }
    void push_back()
    {
        //code here..
    }
    void push_front()
    {
        //code here..
    }
    void pop_back()
    {
        //code here..
    }
    void pop_front()
    {
        //code here..
    }
    T& operator[](int i)
    {
        //code here..
    }
    
    void print()
    {
        //code here..
    }    
private: 
    //variables que usara 
};
int main(){

    /*    
    cout << "\n\n---------------VECTOR----------------\n\n"; 

    CVector<int> v(5);
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
    //v[2] = 1;*/

    cout << "\n\n---------------LISTA----------------\n\n"; 
/*
    //DATOS PARA LA LISTA 
    CList<int> l;
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
        la clase deque es un hibirdo de la clase lista y la clase vector, este nuevo algoritmo es mucho mas
        eficiente ya que posee las mejores caracteristicas de la clase lista y la clase vector.
        las operaciones que debe de tener la clase Deque es la siguiente: 

        -push_back: insertar al final
        -push_front: inserta al inicio
        -pop_back: borrar el ultimo elemento
        -pop_front borra el primer elemento
        -operartor[]: accede a una posicion en especifico 

        idea general: 
        

    *//*
    CDeque<int> d(4); 
    d.push_back(2); 
    d.push_back(3); 
    d.push_back(4); 
    d.push_back(7); 
    d.push_back(9); 
    d.push_back(1); 
    //d.pop_back(); 
    //d.pop_front; 
    cout<<"\n\nelem 4: "<<d[4]<<"\n";
    d.print(); */

    cout << "\n\n---------------QUEUE----------------\n\n"; 

    CQueue<int, CList<int>> q;
    q.push(3);
    q.push(6);
    q.push(1);
    q.pop();
    //q.pop();
    
    cout << "\n\n---------------STACK----------------\n\n"; 

    CStack<int, CVector<int>> s;
    s.push(3);
    s.push(6);
    s.push(1);
    s.pop();
    //s.pop();
}