/*
 * author: Harold ALejandro Villanueva Borda
 * Computer Science - Data Structure 2021
 * @harrylexvb
 * */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

////////////////////////////CLASE LIST//////////////////////////////////////////
#include <iostream>
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
    void push_back(T x); /// insert element below a list
    void push_front(const T& x); /// insert element above list
    void pop_back(); /// delete the last elemnt in a list
    void pop_front(); /// delete the first element in a list
    const T& back(); /// returns the last element of a list
    T& operator[](int i); ///operator
    void clear(); /// clear memory
    void print(); ///print version 1
    void print2(); ///print version 2
private:
    CNode<T>* head, * tail;
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
    CVector(int size = 5); /// constructor
    ~CVector(); /// destructor
    void expand(); /// expand the vector each time it reaches the front
    void collapse(); /// delete each time the list becomes empty
    void push_front(T x); /// insert element above vector
    void push_back(T x); /// insert element below a vector
    void pop_back(); /// delete the last element in a vector
    void pop_front(); /// delete the first element in a vector
    T& operator[](int i); /// operator
    void print(); /// print array
private:
    T* m_v;
    int m_size;
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
void CVector<T>::pop_back() /// delete the last element in a vector
{
    m_v[m_nelem] = NULL;
    m_nelem--;

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
    const T& back(); /// returns the first element
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
void CQueue<T, S>::print() /// print queue
{
    seq.print();
}

///////////////////////////////CLASE DEQUE//////////////////////////////////////////////
template <class T>
class CDeque {
public:
    CDeque(T n_block_size) : block_size(n_block_size) {
        mid_block = block_size / 2;
        map = new T * [block_size] { NULL };
        map[mid_block] = new T[block_size]{ 0 };

        map_back = mid_block;
        map_front = mid_block;
        array_back = mid_block;
        array_front = mid_block;
        actual_size_map = block_size;
    }
    ~CDeque() {
        for (int i = 0; i < actual_size_map; i++) {
            delete[] map[i];
        }
        delete[] map;
    }
    void push_back(T n_value) {
        if (start_cdeque &&
            (map[map_back][array_back] == map[map_front][array_front])) {
            map[map_back][array_back] = n_value;
            start_cdeque = false;
        }
        else {
            if (array_back < (block_size - 1)) {
                array_back++;
                map[map_back][array_back] = n_value;
            }
            else {
                AddBlockBack();
                map[map_back][array_back] = n_value;
            }
        }
    }
    void push_front(T n_value) {
        if (start_cdeque &&
            (map[map_back][array_back] == map[map_front][array_front])) {
            map[map_front][array_front] = n_value;
            start_cdeque = false;
        }
        else {
            if (array_front > 0) {
                array_front--;
                map[map_front][array_front] = n_value;
            }
            else {
                AddBlockFront();
                map[map_front][array_front] = n_value;
            }
        }
    }
    void pop_back() {
        if (start_cdeque) {
            return;
        }
        else if (array_back == 0 && SamePosition()) {
            map[map_back][array_back] = 0;
        }
        else if (array_back == 0) {
            DeleteBlock(map_back);
            map_back--;
            array_back = block_size - 1;
        }
        else {
            map[map_back][array_back] = 0;
            array_back--;
        }
    }
    void pop_front() {
        if (start_cdeque) {
            return;
        }
        else if (array_front == (block_size - 1) && SamePosition()) {
            map[map_front][array_front] = 0;
        }
        else if (array_front == (block_size - 1)) {
            DeleteBlock(map_front);
            map_front++;
            array_front = 0;
        }
        else {
            map[map_front][array_front] = 0;
            array_front++;
        }
    }
    T& operator[](T index) {
        if (start_cdeque) std::cout << "**CDeque empty** ";
        int i = map_front + ((array_front + index) / block_size);
        int j = (array_front + index) % block_size;
        // If you want show physical allocation
        // std::cout << "map[" << i << "]{" << j << "] = ";
        return map[map_front + ((array_front + index) / block_size)]
            [(array_front + index) % block_size];
    }
    void print() {
        if (start_cdeque) std::cout << "**CDeque empty** ";
        std::cout << " | ";
        for (int i = 0; i < actual_size_map; i++) {
            if (map[i]) {
                int* t_map = map[i];
                for (int j = 0; j < block_size; j++) {
                    std::cout << *t_map++ << " ";
                }
            }
            std::cout << " | ";
        }
        std::cout << "\n\n---------------MORE INFO----------------\n";
        std::cout << "\nfront -> " << map[map_front][array_front] << "\n";
        std::cout << "back -> " << map[map_back][array_back] << "\n";
        std::cout << "Length array map: " << actual_size_map << std::endl
            << std::endl;
    }

private:

    int** map = NULL; /// pointer to main array (map)
    bool start_cdeque = true; /// variable to know first element aggregated

    /// variables to resize array map
    int block_size = 0;
    int mid_block = 0;
    int actual_size_map = 0;

    /// index to back pointer
    int map_back = 0;
    int array_back = 0;

    /// index to front pointer
    int map_front = 0;
    int array_front = 0;

    void AddBlockBack() {
        if (map_back >= (block_size - 1)) {
            ResizeMap();
        }
        map_back++;
        array_back = 0;
        map[map_back] = new int[block_size] {0};
    }
    void AddBlockFront() {
        if (map_front <= 0) {
            ResizeMap();
        }
        map_front--;
        array_front = block_size - 1;
        map[map_front] = new int[block_size] {0};
    }
    void ResizeMap() {
        int n_block_map_size = actual_size_map * 3;
        int** n_map = new int* [n_block_map_size] { NULL };
        for (int i = actual_size_map; i < actual_size_map * 2; i++) {
            n_map[i] = map[i - actual_size_map];
        }
        map_back += actual_size_map;
        map_front += actual_size_map;
        actual_size_map = n_block_map_size;
        delete[] map;
        map = n_map;
    }
    bool SamePosition() {
        if ((array_back == array_front) && (map_back == map_front))
            return true;
        else
            return false;
    }
    void DeleteBlock(int index)
    {
        delete[] map[index];
        map[index] = NULL;
    }
};


//////////////////////////////CLASE POSTFIJO////////////////////////////////
class Postfijo {
private:
    static bool isOperator(char);
    static int precedence(char);
public:
    Postfijo() = default;
    static string InfixToPostfix(const string& cadena);
};

string Postfijo::InfixToPostfix(const string& cadena)
{

    ///Crear una pila vacía para los operators y una cadena de salida.
    string postfix;
    CStack<char, CList<char>> operators;
    char operador;
    ///Recorrer la expresión infija de izquierda a derecha.
    for (char c : cadena)
    {
        try
        {
            if (isOperator(c))
            {
                ///Si el símbolo es un operador, primero remover cada operador de la pila con mayor o
                ///igual precedencia que no sea un ‘(’ y agregarlo a la cadena de salida, después
                ///insertar el operador encontrado.
                while (!operators.empty() && (operador = operators.back()) != '(' && precedence(c) <= precedence(operador))
                {
                    postfix += operador;
                    operators.pop();
                }
                operators.push(c);
            }
            else if (c == '(') operators.push(c); ////Si el símbolo es ‘(‘, agregarlo a la pila de operators.
            else if (c == ')')
            {
                ///Si el símbolo es ‘)’, vaciar de la pila hasta encontrar el ‘(’ correspondiente, agregar
                ///cada operador a la cadena de salida.
                while ((operador = operators.back()) != '(')
                {
                    postfix += operador;
                    operators.pop();
                }
                operators.pop();
            }
            else postfix += c;///Si el símbolo es un operando, agregarlo a la cadena de salida.
        }
        catch (...)
        {
            cout << "La cadena no esta en el formato adecuado infijo" << endl;
            return "";
        }
    }
    ///Vaciar cada operador aún presente en la pila y agregarlo a la cadena de salida.
    while (!operators.empty())
    {
        postfix += operators.back();
        operators.pop();
    }
    return postfix;
}
bool Postfijo::isOperator(char c)
{
    return precedence(c) != 0;
}
int Postfijo::precedence(char c)
{
    return (c == '+' || c == '-') ? 1 :
        (c == '*' || c == '/') ? 2 :
        (c == '^') ? 3 : 0;
}


//////////////////////////////CLASE RPN/////////////////////////////

template <class T>
struct RPN {

    static T scanNum(char c)
    {
        int value;
        value = c;
        return float(value - '0'); ///retorna el primer caracter
    }
    static int isOperator(char c)
    {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') return 1; ///el caracter es un operador
        return -1; ///el caracter no es un operador
    }
    static int isOperand(char c)
    {
        if (c >= '0' && c <= '9') return 1; ///el catracter es un operando
        return -1; ///el caracter no es un operando
    }
    static T operation(T a, T b, char op)
    {
        ///realizamos la operacion
        if (op == '+') return b + a;
        else if (op == '-') return b - a;
        else if (op == '*') return b * a;
        else if (op == '/') return b / a;
        else if (op == '^') return pow(b, a);
        else return INT_MIN; ///retorna un infinito negativo
    }
    static T Calculator(string postfix)
    {
        T a, b;
        CStack<float, CList<float>> post;
        string::iterator it;
        for (it = postfix.begin(); it != postfix.end(); it++) {
            ///captura los elemntos de la expresion postfija
            if (isOperator(*it) != -1) {
                a = post.back();
                post.pop(); 
                b = post.back();
                post.pop();
                post.push(operation(a, b, *it));
            }
            else if (isOperand(*it) > 0) {
                post.push(scanNum(*it));
            }
        }
        return post.back();
    }
};


int main() {

    /*
        notacion:
        +: suma
        -: resta
        *: multiplicacion
        /: division
        ^: potenciacion
        ^(/): radicacion

        ejemplo:
        tipo int: (3+5)*(7-4) = 24 
        postfijo: 35+74-*
        tipo float: (3*4)/(2+3) = 2.4
        postfijo: 34*23+/
        con potencia: (2^(1/2))+(5/2) = 3.91
        postfijo: 212/^52/+

        el prograa esta testeado y funcionando en visual studio community, Clion y sublime text 
        para ejecutarlo en replit solo se debera comentar la linea 734 

    */

    string input, expression;
    cout << "enter infix expression: "; getline(cin, input);
    expression = Postfijo::InfixToPostfix(input);
    cout << "postfix: " << expression << endl;
    cout << "The result is: " << RPN<float>::Calculator(expression);

}
