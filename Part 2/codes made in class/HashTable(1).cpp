#include <iostream>
#include <list>
#include <set>

struct CFd1//funcion de dispersion que sera un function object 
{
    inline unsigned long operator()(int x)
    {
        return x+1;
    }
};

template <class T>
struct CListAdaptor : public std::list<T>
{
    //std::list<T> e;

    bool FIND(T v){
        typename std::list<T>::iterator i; 
        for (i = this->begin(); i != this->end(); ++i)
        {
            if(v == *i) 
                return 1; /// si lo encuetra retorna 1 
        }
        return 0;
    }  
    void INSERT(T v){this->push_back(v);} 
    void REMOVE(T v){this->remove(v);} 

};

template<class T, class S, class Fd, unsigned long Sz> ///ipo de dato, tipo de estructura, funcion de dispersion, tamanio 
class CHashTable
{
public:
    CHashTable(); //constructor
    ~CHashTable(); //destructor 
    bool find(T v);
    bool ins(T v);
    bool rem(T v);
    
    S* table; ///array de listas 
    Fd fd; ///funcion de dispersion 
};

template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T,S,Fd,Sz>::CHashTable()
{
    table = new S[Sz]; ///array de lista de tamaño Sz
}

template<class T, class S, class Fd, unsigned long Sz>
CHashTable<T,S,Fd,Sz>::~CHashTable()
{
    delete[] table; ///borrar
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::find(T v)
{
    /*S& l = table[ fd(v)%Sz ];
    
    typename S::iterator i; 
    for (i = l.begin(); i != l.end(); ++i)
    {
        if(v == *i) 
            return 1; /// si lo encuetra retorna 1 
    }
    return 0;*/
    return table[ fd(v)%Sz ].FIND(v); 
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::ins(T v)
{
    /*unsigned long id = fd(v)%Sz; 
    table[id]->pushback(v); 
    */
    ///table[ fd(v)%Sz ].push_back(v);
    table[ fd(v)%Sz ].INSERT(v);
    return 1;
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::rem(T v)
{
    table[ fd(v)%Sz ].REMOVE(v);
    return 0;
}

int main()
{
    ///CHashTable<int, std::list<int>, CFd1, 7> ht; //dato entero, creamos con una lista, funcion de dispersion 1, tamanio 7
    CHashTable<int, CListAdaptor<int>, CFd1, 7> ht; 
    ht.ins(11);
    ht.ins(8);
    ht.ins(4);
    ht.ins(9);
    ht.rem(8);
    
    
}


