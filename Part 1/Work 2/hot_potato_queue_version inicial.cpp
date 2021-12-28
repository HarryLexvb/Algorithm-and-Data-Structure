#include <iostream>
#include <queue>
#include <string>

using namespace std;

#include <iostream>
#include <cmath>
using namespace std;

////////////////////////////CLASE LIST//////////////////////////////////////////
template<class T>
struct CNode{
    CNode(T x)
    {
        value = x;
        next = prev = nullptr; //0
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

    void push_front(const T& x)
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
        //Borra el primer elemento de la lista
        /*if (empty()){
            cout<<"No element to pop.\n";
            return;
        }
        head=head->next;
        if(head==nullptr)
            tail=nullptr;*/
        if(empty())
        {
            throw runtime_error("Trying pop_front() from empty list");
        }
        if(nelem == 1)
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

    const T& front()
    {
        if (empty())
        {
            throw runtime_error("Trying front() from empty list");
        }

        return head->value; //OBSERVAR
    }

    T& operator[](int i)
    {
        CNode<T>* n = head;
        for (int k = 0; k != i; k++)
            n = n->next;
        return n->value;
    }

private:
    CNode<T>* head, *tail;
    size_t nelem;
};

////////////////////////////CLASE VECTOR//////////////////////////////////////////

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
    bool empty()
    {   return seq.empty(); }
    const T& top()
    {
        if(empty())
        {
            throw runtime_error("Trying top() from empty stack.");
        }
        return seq.front();
    }
private:
    S seq;
};

///////////////////////////////CLASE QUEUE///////////////////////////////////////

template<class T, class S>
class CQueue{
public:
    void push(T x)
    {   seq.push(x);   }
    void pop()
    {   seq.pop();     }
    bool empty() {
        return seq.empty();
    }
    T front() {
        return seq.front();
    }
    int size() {
        return seq.size();
    }

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

///////////////////////////HOT POTATO ALGORITHM //////////////////////////////////////////

template <class T, class S>
void print_state(CQueue<T, S> q) {
	while (!q.empty()){
		cout << q.front() << (q.size() > 1 ? "->" : " ");
		q.pop();
	}
	cout<<endl;
}

template <class T, class S>
void hot_potato_game(CQueue<T, S>& q) {
    while(q.size() > 1) {
        print_state<T, S>(q);
        int salto = rand() % (2*q.size()) + 1;
        int counter = 0;
        cout << "La tiene " << q.front() << endl;
        cout << "Salto de " << salto << endl;
        salto %= q.size();

        CQueue<T, S> newQ;
        CQueue<T, S> rest;
        while(!q.empty()) {
            if (counter != salto) {
                if (counter < salto) {
                    rest.push(q.front());
                } else {
                    newQ.push(q.front());
                }
            }
            q.pop();
            counter++;
        }
        q = newQ;

        while(!rest.empty()) {
            q.push(rest.front());
            rest.pop();
        }
        cout << endl;
    }
    cout << q.front() << endl;
}

int main() {
    srand(time(nullptr));

    CQueue<char, queue<char>> q;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        char jugador = 65 + i;
        q.push(jugador);
    }

    hot_potato_game<char, queue<char>>(q);

    /*

    IMPLEMENTAR EL JUEGO DE LA PAPA CALIENTE USANDO SOLO LA CLASE CQUEUE (COLAS) QUE LE SERVIRA PARA 
    SIMULAR UNA LISTA CIRCULAR DE SER NECESARIO DE AGREGAR MAS FUNCIONES A LA CLASE QUEUE PUEDE HACERLO SIEMPRE 
    Y CUANDO FORMEN PARTE DE LA ESTRUCTURA DE LA CLASE QUEUE. 
    NO USAR NINGUNA LIBRERIA DE LA STL DE SER ASI NO SE CALIFICARA 

    lista generara de forma aleatoria en base a la cantidad de jugadores:
    ejemplo, numero de jugadores: 5
    lista: 
    A -> B -> C -> E -> F -> G

    la papa empieza en A
    se genera N aleatoriamente: N = 4
    la papa avanza 4 posiciones
    notamos que F esta en la posicion 4 entonces sale del juego (muere)    
    A -> B -> C -> E -> G
    la papa no puede quedar en el aire asi que pasa al sigueinte, en este caso G

    ahora la papa empieza en G 
    la lista ahora tiene 5 elementos  
    se genera N aleatoriamente: N = 2
    la papa avanza 2 posiciones
    notamos que B esta en la posicion 2 entonces sale del juego (muere)
    A -> C -> E -> G
    la papa no puede quedar en el aire asi que pasa al sigueinte, en este caso C

    ahora la papa empieza en C
    la lista ahora tiene 4 elementos  
    se genera N aleatoriamente: N = 3
    la papa avanza 3 posiciones
    notamos que A esta en la posicion 3 entonces sale del juego (muere)
    C -> E -> G
    la papa no puede quedar en el aire asi que pasa al sigueinte, en este caso C

    ahora la papa empieza en C
    la lista ahora tiene 3 elementos  
    se genera N aleatoriamente: N = 8
    la papa avanza 8 posiciones
    notamos que E esta en la posicion 8 entonces sale del juego (muere)
    C -> E -> G
    la papa no puede quedar en el aire asi que pasa al sigueinte, en este caso G

    ahora la papa empieza en G
    la lista ahora tiene 2 elementos  
    se genera N aleatoriamente: N = 5
    la papa avanza 5 posiciones
    notamos que C esta en la posicion 5 entonces sale del juego (muere)
    C -> G
    la papa no puede quedar en el aire asi que pasa al sigueinte, en este caso G

    ahora la papa empieza en G 
    la lista ahora tiene 1 elemento 
    se genera N aleatoriamente: N = 7
    la papa avanza 7 posiciones 
    al trata de ser el unico elemento entonces saltara en si mismo 
    eliminandose asi por defecto y quedando la lista vacia e imprimir al final  NULL 

    */

    
}