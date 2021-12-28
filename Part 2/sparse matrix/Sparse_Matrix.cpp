#include <iostream>
using namespace std;

template<typename T>
class nodo_smx {
public:
    T m_data;
    int x_data, y_data;
    nodo_smx<T>* next;
    nodo_smx<T>* down;

    nodo_smx(T info, int x, int y) {
        this->m_data = info;
        this->x_data = x;
        this->y_data = y;
        next = down = nullptr;
    }
};

template<typename M>
class nodo_temp {
public:
    typedef typename M::Tt T;
    T info;
    int x_, y_;
    M* matrix;

    nodo_temp(T info, int x, int y, M* ma) {
        this->info = info;
        this->x_ = x;
        this->y_ = y;
        matrix = ma;
    }
    operator T();
    nodo_temp<M>& operator =(T dato) {
        cout << "dato:" << dato;
        cout << "\t" << info << " (" << x_ << " , " << y_ << ")" << endl;
        if (dato == matrix->var_nul) {
            matrix->eliminar(x_, y_);
        }
        else {
            matrix->insertar(x_, y_, dato);
        }
        return *this;
    }

    nodo_temp<M>& operator =(nodo_temp<M> dato) {
        cout << "dato:" << dato;
        cout << "\t" << info << " (" << x_ << " , " << y_ << ")" << endl;
        if (dato == matrix->var_nul) {
            matrix->eliminar(x_, y_);
        }
        else {
            matrix->insertar(x_, y_, dato);
        }
        return *this;
    }
};

template<typename M>
nodo_temp<M>::operator T() {
    return info;
}

template <class T, int filas, int columnas, T nulo_char >
class Csparsa {
public:

    typedef Csparsa<T, filas, columnas, nulo_char> self;
    typedef T  Tt;

    T var_nul = nulo_char;

    nodo_smx<T>* x_[filas];
    nodo_smx<T>* y_[columnas];

    Csparsa() {
        for (int i = 0; i < filas; i++) {
            x_[i] = nullptr; // x_[i] = 0
        }
        for (int i = 0; i < columnas; i++) {
            y_[i] = nullptr; // y_[i] = 0
        }
    }


    bool insertar(int i, int j, T dato);
    bool eliminar(int i, int j);
    void debug_fila(nodo_smx<T>* cent);
    bool find_x(int i, int j, nodo_smx<T>**& p);
    bool find_y(int i, int j, nodo_smx<T>**& p);
    void print_matrix_x();
    void print_matrix_y();
    //T operator()(int i, int j);
    nodo_temp<self> operator()(int i, int j);
    /*nodo_smx<T>& operator()(int i, int j){
       return insertar(i,j,0);
    }*/

};

template <class T, int filas, int columnas, T nulo_char>
inline bool Csparsa<T, filas, columnas, nulo_char>::insertar(int i, int j, T dato)
{
    nodo_smx<T>** ptr;
    if (i >= 0 && i < filas && j >= 0 && j < columnas)
    {
        if (find_x(i, j, ptr))
        {
            if (dato == nulo_char)
            {
                eliminar(i, j);
            }
            else {
                (*ptr)->m_data = dato;
                return 1;
            }
        }
        else {
            nodo_smx<T>* temp = new nodo_smx<T>(dato, i, j);
            temp->down = *ptr;
            *ptr = temp;
            find_y(i, j, ptr);
            temp->next = *ptr;
            *ptr = temp;
            return 1;
        }
        return 0;

    }
    return 0; // necesario
}
/*inline bool Csparsa<T, filas, columnas, nulo_char > ::insertar(int i, int j, T dato) {
    nodo_smx<T>** ptr;
    //cout<<"dato in:"<<dato<<endl;
    if (i >= 0 && i < filas && j >= 0 && j < columnas) {
        if (find_x(i, j, ptr)) { //si lo encuentra, ya existe, entonces cambio su valor
            if (dato == nulo_char) {
                eliminar(i, j);
            }
            else {
                (*ptr)->m_data = dato;
                return 1;
            }
            return 0;
        }
        else {
            nodo_smx<T>* tmp = new nodo_smx<T>(dato, i, j);
            //lo mismo que en la lista enlazada pero para abajo
            tmp->down = *ptr;
            *ptr = tmp;
            //lo mismo que la lista enlazada
            find_y(i, j, ptr);
            tmp->next = *ptr;
            *ptr = tmp;
            return 1;
        }
    }
    else {
        cout << "\FUERA DE RANGO\n";
        return 0;
    }
}*/

template <class T, int filas, int columnas, T nulo_char>
inline bool Csparsa<T, filas, columnas, nulo_char>::eliminar(int i, int j)
{
    nodo_smx<T>** x;
    nodo_smx<T>** y;
    if (find_y(i, j, y))
        return 0;
    find_x(i, j, x);
    nodo_smx<T>* temp = (*y)->down;
    nodo_smx<T>* temp2 = (*x)->next;
    delete* y;
    *y = temp;
    *x = temp2;
    return 1;
}
/*inline bool Csparsa<T, filas, columnas, nulo_char > ::eliminar(int i, int j) {
    nodo_smx<T>** ptrY;
    nodo_smx<T>** ptrX;
    if (!find_y(i, j, ptrY))
    {
        return 0;
    }
    find_x(i, j, ptrX);
    nodo_smx<T>* tmpY = (*ptrY)->down; //PUENTE ABAJO
    nodo_smx<T>* tmpX = (*ptrX)->next; //PUENTE ARRIBA
    delete* ptrY;
    *ptrY = tmpY;
    *ptrX = tmpX;
    return 1;
}*/

template <class T, int filas, int columnas, T nulo_char>
inline void Csparsa<T, filas, columnas, nulo_char > ::debug_fila(nodo_smx<T>* cent) {
    while (cent) {
        cout << cent->m_data;
        cout << "-> ";
        cent = cent->next;
    }
}

template <class T, int filas, int columnas, T nulo_char >
inline bool Csparsa<T, filas, columnas, nulo_char> ::find_x(int i, int j, nodo_smx<T>**& p) {
    p = &(x_[i]);
    while (*p && (*p)->y_data < j)
        p = &((*p)->next);
    return *p && (*p)->y_data == j;
    /*p = &(x_[i]);
    while (*p && (*p)->y_data < j) {
        p = &((*p)->next);
    }
    return *p && (*p)->y_data == j;*/
}

template <class T, int filas, int columnas, T nulo_char >
inline bool Csparsa<T, filas, columnas, nulo_char> ::find_y(int i, int j, nodo_smx<T>**& p) {
    p = &(y_[j]);
    while (*p && (*p)->x_data < i)
        p = &((*p)->down);
    return *p && (*p)->x_data == i;

    /*p = &(y_[j]);
    while (*p && (*p)->x_data < i) {
        p = &((*p)->down);
    }
    return *p && (*p)->x_data == i;*/
}

template <class T, int filas, int columnas, T nulo_char>
inline void Csparsa<T, filas, columnas, nulo_char > ::print_matrix_x() {
    cout << "\n";
    for (int i = 0; i < filas; i++) {
        cout << "\t";
        //cout<<i;
        //debug_fila(x_[i]);
        int cont = 0;
        nodo_smx<T>* q = x_[i];
        while (q) {
            while (q->y_data > cont) {
                cout << nulo_char << " ";
                cont++;
            }
            cout << q->m_data << " ";
            q = q->next;
            cont++;
        }
        while (columnas - cont > 0) {
            cout << nulo_char << " ";
            cont++;
        }
        cout << "\n";
    }
    cout << "\n";
}

template <class T, int filas, int columnas, T nulo_char>
inline void Csparsa<T, filas, columnas, nulo_char > ::print_matrix_y() {
    for (int i = 0; i < columnas; i++) {
        cout << "\t";
        int cont = 0;
        nodo_smx<T>* q = y_[i];
        while (q) {
            while (q->x_data > cont) {
                cout << nulo_char << " ";
                cont++;
            }
            cout << q->m_data << " ";
            q = q->down;
            cont++;
        }
        while (filas - cont > 0) {
            cout << nulo_char << " ";
            cont++;
        }
        cout << "\n";
    }
}

template <class T, int filas, int columnas, T nulo_char>
nodo_temp<Csparsa<T, filas, columnas, nulo_char >> Csparsa<T, filas, columnas, nulo_char > :: operator()(int i, int j) {
    nodo_smx<T>** p;
    T f;
    if (find_x(i, j, p)) {
        f = (*p)->m_data;
    }
    else {
        f = nulo_char;
    }
    return nodo_temp<self>(f, i, j, this);
}

int main() {
    
    Csparsa<int, 6, 6, 0> Matrix;
    cout << "Matriz original:\n";
    /*Matrix.insertar(0, 0, 9);
    Matrix.insertar(0, 1, 8);|
    Matrix.insertar(0, 2, 7);
    Matrix.insertar(1, 0, 6);
    Matrix.insertar(1, 1, 5);
    Matrix.insertar(1, 2, 4);
    Matrix.insertar(2, 0, 3);
    Matrix.insertar(2, 1, 2);
    Matrix.insertar(2, 2, 1);*/

    /*for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            cout << i << " - " << j << endl ; 
        }
        cout<< endl; 
    }*/
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            Matrix.insertar(i, j, i+1);
            cout << i << "," << j << " = ";
            cout << Matrix(i, j) << endl;
        }
        cout << endl; 
    }
    /*for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            cout << i << "," << j << " = ";
            cout << Matrix(i, j) << endl;
        }
        cout << endl; 
    }*/

    //Matrix.print_matrix_x();
    //cout << "Matriz tranpuesta:\n\n";
    //Matrix.print_matrix_y();

    //cout << "\nTHE[2][2]    : " << Matrix(2, 0) << endl;
    //cout << "THE[2][8]    :" << Matrix(2, 8) << " out of range\n";

}