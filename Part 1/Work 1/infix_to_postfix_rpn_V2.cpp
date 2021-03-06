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
    
    /*void print()
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
    
    }*/
     
private:
    CNode<T>* head, *tail;
    size_t nelem;
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
    {   seq.push_front(x);   }
    void pop()
    {   seq.pop_front();     }
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

//////////////////////////////CLASE POSTFIJO////////////////////////////////

class Postfijo {
private:
    static bool isOperator(char);
    static int precedence(char);
public:
    Postfijo() = default;
    static string infijoAPostfijo(const string&);
};

string Postfijo::infijoAPostfijo(const string &cadena)
{
    /***
     * Crear una pila vacía para los operadores y una cadena de salida.
     */
    string postfijo;
    CStack<char, CList<char>> operadores;
    char operador;
    /***
     * Recorrer la expresión infija de izquierda a derecha.
     */
    for(char c : cadena)
    {
        try
        {
            if(isOperator(c))
            {
                /***
                 * Si el símbolo es un operador, primero remover cada operador de la pila con mayor o
                    igual precedencia que no sea un ‘(’ y agregarlo a la cadena de salida, después
                    insertar el operador encontrado.
                 */
                while( !operadores.empty() && (operador = operadores.top()) != '(' && precedence(c) <= precedence(operador))
                {
                    postfijo += operador;
                    operadores.pop();
                }
                operadores.push(c);
            }
            else if(c == '(')
            {
                /***
                 * Si el símbolo es ‘(‘, agregarlo a la pila de operadores.
                 */
                operadores.push(c);
            }
            else if(c == ')')
            {
                /***
                 * Si el símbolo es ‘)’, vaciar de la pila hasta encontrar el ‘(’ correspondiente, agregar
                 * cada operador a la cadena de salida.
                 */
                while((operador = operadores.top()) != '(')
                {
                    postfijo+=operador;
                    operadores.pop();
                }
                operadores.pop();

            }
            else
            {
                /***
                 * Si el símbolo es un operando, agregarlo a la cadena de salida.
                 */
                postfijo += c;
            }
        }
        catch(...)
        {
            cout << "La cadena no esta en el formato adecuado infijo" << endl;
            return "";
        }
    }
    /***
     * Vaciar cada operador aún presente en la pila y agregarlo a la cadena de salida.
     */
    while(!operadores.empty())
    {
        postfijo += operadores.top();
        operadores.pop();
    }
    return postfijo;
}

bool Postfijo::isOperator(char c)
{
    return precedence(c) != 0;
}

int Postfijo::precedence(char c)
{
    return (c == '+' || c == '-') ? 1 :
           (c == '*' || c == '/') ? 2 :
           (c == '^')? 3 : 0;
}


float scanNum(char ch){
   int value;
   value = ch;
   return float(value-'0');//return float from character
}
int isOperator(char ch){
   if(ch == '+'|| ch == '-'|| ch == '*'|| ch == '/' || ch == '^')
      return 1;//character is an operator
   return -1;//not an operator
}
int isOperand(char ch){
   if(ch >= '0' && ch <= '9')
      return 1;//character is an operand
   return -1;//not an operand
}
float operation(int a, int b, char op){
   //Perform operation
   if(op == '+')
      return b+a;
   else if(op == '-')
      return b-a;
   else if(op == '*')
      return b*a;
   else if(op == '/')
      return b/a;
   else if(op == '^')
      return pow(b,a); //find b^a
   else
      return INT_MIN; //return negative infinity
}

float postfixEval(string postfix){
   int a, b;
   CStack<float, CList<float>> stk;
   string::iterator it;
   for(it=postfix.begin(); it!=postfix.end(); it++){
      //read elements and perform postfix evaluation
      if(isOperator(*it) != -1){
         a = stk.top();
         stk.pop();
         b = stk.top();
         stk.pop();
         stk.push(operation(a, b, *it));
      }
      else if(isOperand(*it) > 0){
         stk.push(scanNum(*it));
      }
   }
   return stk.top();
}

int main(){

    string input, expression;
    cout << "enter infix expression: "; getline(cin,input);
    expression = Postfijo::infijoAPostfijo(input); 
    cout << "postfix: " << expression << endl;
    cout << "The result is: "<<postfixEval(expression);
}
