/*
 * author: Harold ALejandro Villanueva Borda
 * Computer Science - Data Structure 2021
 * @harrylexvb
 * */

#include <iostream>
#include <cmath>
#include <string>

////////////////////////////CLASE LIST//////////////////////////////////////////
using namespace std;

template<class T>
struct CNode {
    CNode(T x) /// node structure
    {
        value = x;
        next = prev = nullptr; //0
    }
    T value;
    CNode<T>* next, * prev;

};

template<class T>
class CList {
public:
    CList(); /// constructor
    ~CList(); ///destructor
    bool empty(); /// check if my list is empty
    size_t size() const; /// return size 
    void push_back(T x); /// insert element below a list
    void push_front(const T& x); /// insert element above list
    void pop_back(); /// delete the last elemnt in a list
    void pop_front(); /// delete the first element in a list
    const T& front(); /// returns the first element of a list
    const T& back(); /// returns the last element of a list
    void insert(size_t position, const T& element); /// insert element 
    void erase(size_t position); /// erase element 
    void remove(const T& value); /// Remove elements with specific value 
    T& operator[](int i); ///operator
    void clear(); /// clear memory
    void print(); ///print version 1
    void print2(); ///print version 2
private:
    CNode<T>* head, *tail;
    size_t nelem;
};

template<class T>
CList<T>::CList() /// constructor
{
    head = tail = 0;
    nelem = 0;
}

template<class T>
CList<T>::~CList() ///destructor
{
    clear();
}

template<class T>
bool CList<T>::empty() /// check if my list is empty
{
    return head == nullptr;
}

template<typename T>
size_t CList<T>::size() const
{
    return nelem;
}

template<class T>
void CList<T>::push_back(T x) /// insert element below a list
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
    nelem++;
}

template<class T>
void CList<T>::push_front(const T& x) /// insert element above list
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
    nelem++;
}

template<class T>
void CList<T>::pop_back() /// delete the last elemnt in a list
{
    //Borra el último elemento de la lista
    /*if(empty()){
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
    ptr->next=nullptr;*/
    if (empty())
        throw runtime_error("Trying pop_back() from empty list");

    if (nelem == 1)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        tail = tail->prev;
        tail->next = nullptr;
    }
    --nelem;
}

template<class T>
void CList<T>::pop_front() /// delete the first element in a list
{
    //Borra el primer elemento de la lista
    /*if (empty()){
        cout<<"No element to pop.\n";
        return;
    }
    head=head->next;
    if(head==nullptr)
        tail=nullptr;*/
    if (empty())
        throw runtime_error("Trying pop_front() from empty list");

    if (nelem == 1)
    {
        head = nullptr;
        tail = nullptr;
    }
    else
    {
        head = head->next;
        head->prev = nullptr;
    }
    --nelem;
}

template<class T>
const T& CList<T>::front() /// returns the first element of a list
{
    if (empty())
        throw runtime_error("Trying front() from empty list");
    return head->value; //OBSERVAR
}

template<class T>
const T& CList<T>::back() /// returns the last element of a list
{
    if (empty())
        throw runtime_error("Trying back() from empty list");
    return tail->value; //OBSERVAR
}

template<class T>
T& CList<T>::operator[](int i)  /// operator
{
    CNode<T>* n = head;
    for (int k = 0; k != i; k++)
        n = n->next;
    return n->value;
}

template<class T>
void CList<T>::clear() /// clear memory
{
    while (!empty())
        pop_front();
}

template<class T>
void CList<T>::print() /// print version 1
{
    std::cout << "\n";
    for (CNode<T>* n = head; n != 0; n = n->next)
        std::cout << n->value << " ";
}

template<class T>
void CList<T>::print2() /// print version 2
{
    std::cout << "\n";
    for (int i = 0; i < nelem; i++)
        std::cout << (*this)[i] << " ";

}


////////////////////////////CLASE VECTOR//////////////////////////////////////////

template<class T>
class CVector {
public:
    CVector(int size); /// constructor
    ~CVector(); /// destructor
    bool empty(); /// check if my list is empty
    void expand(); /// expand the vector each time it reaches the front
    void collapse(); /// delete each time the list becomes empty
    void push_front(T x); /// insert element above vector
    void push_back(T x); /// insert element below a vector
    void pop_back(); /// delete the last element in a vector
    void pop_front(); /// delete the first element in a vector
    const T& front();
    const T& back();
    T& operator[](int i); /// operator
    void print(); /// print array
private:
    T* m_v;
    //int m_size;
    size_t m_size;
    int m_nelem;
};

template<class T>
CVector<T>::CVector(int size) ///constructor
{
    m_size = size;
    m_v = new T[m_size];
    m_nelem = 0;
}

template<class T>
CVector<T>::~CVector() ///destructor
{
    delete m_v;
}

template<class T>
bool CVector<T>::empty() /// check if my list is empty
{
    return (m_size == 0);
}

template<class T>
void CVector<T>::expand() /// expand the vector each time it reaches the front
{
    T* p = new T[2 * m_size];
    for (int i = 0; i < m_size; i++)
        p[i] = m_v[i];
    delete m_v;
    m_v = p;
    m_size = 2 * m_size;
}

template<class T>
void CVector<T>::collapse() ////// delete each time the list becomes empty
{
    T* p = new T[m_nelem];
    int counter = 0;
    int test = 0;
    for (int i = 0; i < m_size; i++) {
        if (m_v[i] != NULL) {
            p[counter] = m_v[i];
            counter++;
        }
        test++;
    }

    m_v = p;
    m_size = m_nelem;

    //std::cout << counter << " " << test << endl;
}

template<class T>
void CVector<T>::push_back(T x) /// insert element below a vector
{
    if (m_nelem == m_size)
        expand();
    m_v[m_nelem] = x;
    m_nelem++;
}

template<class T>
void CVector<T>::push_front(T x) /// insert element above vector
{
    if (m_nelem == m_size)
        expand();
    for (int i = m_nelem - 1; i >= 0; i--)
        m_v[i + 1] = m_v[i];
    m_v[0] = x;
    m_nelem++;
}

template<class T>
void CVector<T>::pop_back() /// delete the last element in a vector
{
    m_v[m_nelem] = NULL;
    m_nelem--;

}

template<class T>
void CVector<T>::pop_front() /// delete the first element in a vector
{
    T* p = new T[m_size];
    for (int i = 1; i < m_size; i++)
        p[i - 1] = m_v[i];
    delete m_v;
    m_v = p;
    m_size = m_size - 1;
    m_nelem--;
    m_v[m_nelem] = NULL;
}

template<class T>
const T& CVector<T>::front() /// returns the first element of a list
{
    if (empty())
        throw runtime_error("Trying front() from empty list");
    return m_v[0]; //OBSERVAR
}

template<class T>
const T& CVector<T>::back() /// returns the last element of a list
{
    if (empty())
        throw runtime_error("Trying back() from empty list");
    return m_v[m_size-1]; //OBSERVAR
}

template<class T>
T& CVector<T>::operator[](int i) /// operator
{
    return m_v[i];
}

template<class T>
void CVector<T>::print() /// print array
{
    for (int i = 0; i < m_nelem; i++)
        std::cout << m_v[i] << " ";
    std::cout << std::endl;
}

///////////////////////////////CLASE STACK///////////////////////////////////////

template<class T, class S>
class CStack {
public:
    CStack(); /// constructor
    ~CStack(); ///destructor
    size_t size(); /// return size
    void push(T x); /// insert element (push_back)
    void pop(); /// remove element (pop_back)
    bool empty(); /// check if is empty
    const T& front(); /// returns the first element
    const T& back(); /// returns the last element
    void print(); /// print stack
private:
    S seq;
};

template<class T, class S>
CStack<T, S>::CStack() {} /// constructor

template<class T, class S>
CStack<T, S>::~CStack() ///destructor
{
    seq.clear();
}

template<class T, class S>
size_t CStack<T, S>::size() /// return size
{
    return seq.size();
}

template<class T, class S>
void CStack<T, S>::push(T x) /// insert element (push_back)
{
    seq.push_back(x);
}

template<class T, class S>
void CStack<T, S>::pop() ///remove element (pop_back)
{
    seq.pop_back();
}

template<class T, class S>
bool CStack<T, S>::empty() /// check if is empty
{
    return seq.empty();
}

template<class T, class S>
const T& CStack<T, S>::front() /// returns the first element
{
    if (empty())
        throw runtime_error("Trying front() from empty stack.");
    return seq.front();
}

template<class T, class S>
const T& CStack<T, S>::back() /// returns the first element
{
    if (empty())
        throw runtime_error("Trying front() from empty stack.");
    return seq.back();
}

template<class T, class S>
void CStack<T, S>::print() /// print queue
{
    seq.print();
}

///////////////////////////////CLASE QUEUE///////////////////////////////////////

template<class T, class S>
class CQueue {
public:

    CQueue(); /// constructor
    ~CQueue(); ///destructor
    void push(T x); /// insert element (push_back)
    void pop(); /// remove element (pop_back)
    bool empty(); /// check if is empty
    const T& front(); /// returns the first element
    const T& back(); /// returns the first element
    size_t size(); /// return size 
    void print(); /// print queue


private:
    S seq;
};

template<class T, class S>
CQueue<T, S>::CQueue() {} /// constructor

template<class T, class S>
CQueue<T, S>::~CQueue() ///destructor
{
    seq.clear();
}

template<class T, class S>
size_t CQueue<T, S>::size() /// return size
{
    return seq.size();
}

template<class T, class S>
void CQueue<T, S>::push(T x) /// insert element (push_back)
{
    seq.push_back(x);
}

template<class T, class S>
void CQueue<T, S>::pop() ///remove element (pop_front)
{
    seq.pop_front();
}

template<class T, class S>
bool CQueue<T, S>::empty() /// check if is empty
{
    return seq.empty();
}

template<class T, class S>
const T& CQueue<T, S>::front() /// returns the first element
{
    if (empty())
        throw runtime_error("Trying front() from empty stack.");
    return seq.front();
}

template<class T, class S>
const T& CQueue<T, S>::back() /// returns the first element
{
    if (empty())
        throw runtime_error("Trying front() from empty stack.");
    return seq.back();
}

template<class T, class S>
void CQueue<T, S>::print() /// print queue
{
    seq.print();
}


int main() {

    CList<int> l; 
    l.push_back(2);         
    l.push_back(3);         
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    l.print();
    cout << "\nfront: " << l.front() << endl;         
    cout << "back: " << l.back() << endl; 
    cout << "size: " << l.size() << endl;       
}