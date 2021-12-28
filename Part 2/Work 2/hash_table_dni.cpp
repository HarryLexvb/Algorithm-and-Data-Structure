/*
 * author: Harold ALejandro Villanueva Borda
 * Computer Science - Data Structure 2021
 * @harrylexvb
 * */

#include <iostream>
#include <list>

using namespace  std;

/*cout << (mod(DNI, 10)) << endl; //8 * 2
    cout << (mod(DNI, 100)) / 10 << endl; //7 * 3
    cout << (mod(DNI, 1000)) / 100 << endl; //6 * 4
    cout << (mod(DNI, 10000)) / 1000 << endl; //5 * 5
    cout << (mod(DNI, 100000)) / 10000 << endl; //4 * 6
    cout << (mod(DNI, 1000000)) / 100000 << endl; //3 * 7
    cout << (mod(DNI, 10000000)) / 1000000 << endl; //2 * 2
    cout << (mod(DNI, 1000000000)) / 10000000 << endl; //1 *3*/

unsigned long long mod(unsigned long long a, unsigned long long b){
    unsigned long long q= a / b;
    if(q<0) q--;
    return a-(b * q);
}
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
//funcion de dispersion que sera un function object
struct CFd1{
    inline unsigned long operator()(int x)
    {
        return x-1;
    }
};
//algoritmo para la funcion dispersion 
int algorithm(unsigned int DNI){
    unsigned int num = 32765432;
    list<int> L1;
    int arr[] = {6,7,8,9,0,1,1,2,3,4,5};
    int a,sum=0, pos;
    for(int i = 1; i < 9; ++i){
        a = ((mod(DNI, binpow(10,i)))/(binpow(10,i-1)))*((mod(num, binpow(10,i)))/(binpow(10,i-1)));
        L1.push_back(a);
    }
    for(auto l : L1) { 
        sum += l; //suma de la lista
    }
    pos = (11 - mod(sum, 11)) + 1;
    if(pos > 11)
        return arr[mod(pos, 11)-1];
    else
        return arr[pos-1];
}

template <class T>
struct CListAdaptor : public std::list<T>{
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
    void print(){

        typename std::list<T>::iterator i;
        for (i = this->begin(); i != this->end(); ++i)
            cout << *i << "->";
        cout << endl;
        //cout << this->front() << "\n";
        //cout << this->back() << "\n";
    }
};

template<class T, class S, class Fd, unsigned long Sz> ///tipo de dato, tipo de estructura, funcion de dispersion, tamanio
class CHashTable{
public:
    CHashTable(); //constructor
    ~CHashTable(); //destructor
    bool empty() const;
    bool find(T v);
    bool ins(T v);
    bool rem(T v);
    void printTable();

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
bool CHashTable<T,S,Fd,Sz>::empty() const{
    int sum = {};
    for (int i{}; i < Sz ; ++i)
        sum += table[i].size();
    if(!sum) return true;
    return false;
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
    return table[algorithm(v)].FIND(v);
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::ins(T v)
{
    /*unsigned long id = fd(v)%Sz;
    table[id]->pushback(v);
    */
    ///table[ fd(v)%Sz ].push_back(v);
    if (find(v) == 0)
        table[algorithm(v)].INSERT(v);
    else
        return 0; 
    return 1;
}

template<class T, class S, class Fd, unsigned long Sz>
bool CHashTable<T,S,Fd,Sz>::rem(T v)
{
    table[algorithm(v) ].REMOVE(v);
    return 0;
}

template<class T, class S, class Fd, unsigned long Sz>
void CHashTable<T,S,Fd,Sz>::printTable(){
    for (int i = 0; i < Sz; ++i){
        cout << i << "  ";
        if(table[i].empty())
            cout << "NULL" << endl;
        else
            table[i].print();
    }
}

void  menu(){
    ///CHashTable<int, std::list<int>, CFd1, 10> ht; //dato entero, creamos con una lista, funcion de dispersion 1, tamanio 7
    CHashTable<int, CListAdaptor<int>, CFd1, 10> ht; //crear hsh table
    unsigned int DNI;
    int opcion;
    bool repetir = true;

    do {
        cout << "\n\nMenu de Opciones" << endl;
        cout << "1. INSERTAR" << endl;
        cout << "2. MOSTRAR" << endl;
        cout << "3. BORRAR" << endl;
        cout << "0. SALIR 4" << endl;

        cout << "\nIngrese una opcion: "; cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "INSERTAR: "; cin >> DNI;
                ht.ins(DNI);
                break;

            case 2:
                cout << "MOSTRAR: \n";
                ht.printTable();
                break;

            case 3:
                cout << "BORRAR: "; cin >> DNI;
                ht.rem(DNI);
                break;
            case 0:
                repetir = false;
                break;
        }
    } while (repetir);
}

int main()
{
    /*
     ejecuta sin ningun error en Clion, replit, visual studio community
     version c++ 20

     el programa inserta, remueve y muestra datos en una hash table
     numeros para prueba rapida:

     17801146 - 0
     72414960 - 5
     30960533 - 6
     72039840 - 6
     */
    menu();

}
//////////IGNORE/////////////////////////////
/*list<int> L1;
    unsigned int DNI = 73698708, num = 32765432;
    int arr[] = {6,7,8,9,0,1,1,2,3,4,5}, select;
    int a,sum=0, pos;

    for(int i = 1; i < 9; ++i){
        /*a = (mod(DNI, binpow(10,i)))/(binpow(10,i-1));
        b = (mod(num, binpow(10,i)))/(binpow(10,i-1));
        c = a*b;
         cout << a << "*"<<b <<"=" << c << endl;
         */
/*a = ((mod(DNI, binpow(10,i)))/(binpow(10,i-1)))*((mod(num, binpow(10,i)))/(binpow(10,i-1)));
L1.push_back(a);
}
for(auto l : L1) {
//cout << l << endl;
//l++;
sum += l; //suma de la lista
}
//cout << sum << endl;
pos = (11 - mod(sum, 11)) + 1;
//cout << pos << endl;
if(pos > 11)
cout << "pos: " <<arr[mod(pos, 11)-1];
else
cout << "pos: " << arr[pos-1];*/