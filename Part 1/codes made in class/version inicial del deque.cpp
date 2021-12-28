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
        tail->next=nullptr;
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
        if (empty()){
        cout<<"No element to pop.\n";
        return;
        }
        if(head != nullptr && head != tail){
            head=head->next;
        }

        if(head == tail){
            head = tail = nullptr;
        }
       
            
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
        m_v[m_nelem] = NULL;
        m_nelem --;
        
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
        T* p = new T[m_size];
        for (int i = 1; i < m_size; i++)
            p[i-1] = m_v[i];
        delete m_v;
        m_v = p;
        m_size = m_size-1;
        m_nelem--;
        m_v[m_nelem] = NULL;
    }

    void collapse( )
    {
        T* p = new T[m_nelem];
        int counter =0;
        int test = 0;
        for (int i = 0; i < m_size; i++){
            if( m_v[i] != NULL ){
                p[counter] = m_v[i];
                counter++;
            }
            test++;
        }
            
        m_v = p;
        m_size = m_nelem;

        //std::cout << counter << " " << test << endl;
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

///////////////////////////////// CLASE DEQUE ///////////////////////////////////
template<class T>
class CDeque{
public: 
    CDeque(int b_size_)
    {
        b_size = b_size_;
        T* block = new T[b_size];
        out_offset = (chunks/2) ;
        blocks[out_offset] = block;
        in_offset = (b_size/2) ;
        head = tail = {out_offset, in_offset};
       // std::cout << out_offset << " " << in_offset << endl;
    }
    ~CDeque()
    {
        //destructor
    }
    void push_back(T x)
    {//sacar posicion original
    // offset + index / b_size = block en el que esta
    // offset + index % b_size = posicion dentro del block
        auto out = tail.first;
        auto in = tail.second;
        //std::cout << out << " " << in;
       if(size == 0){
            blocks[out][in] = x;
            size++;
           // std::cout <<  " entre" << in;
       }
        if(out == chunks-1 && in == b_size -1){
            //no hay espacio en el bloque actual y no hay espacio para otro bloque
           // std::cout << "Deque lleno" << endl;
        }
        else{
            if(in == b_size){
                //no hay espacio en el bloque actual pero hay espacio para otro bloque 
                //std::cout << "Entre " << x << in << endl;
                T* block = new T[b_size];
                blocks[out+1] = block;
                blocks[out][0] = x;
                tail.first = tail.first + 1;
                tail.second = 1;
                size++;
            }else{
               // cout << "entre " <<x << endl;
               // cout << out << in << endl;
                blocks[out][in] = x;
                tail.second = tail.second+1;
                size++;
            }
        }


    }
    void push_front(T x)
    {
        auto out = head.first;
        auto in = head.second;
        //std::cout << out << " " << in;
       if(size == 0){
            blocks[out][in] = x;
            size++;
           // std::cout <<  " entre" << in;
       }
        if(out == 0 && in == b_size -1){
            //no hay espacio en el bloque actual y no hay espacio para otro bloque
           // std::cout << "Deque lleno" << endl;
        }
        else{
            if(in == b_size){
                //no hay espacio en el bloque actual pero hay espacio para otro bloque 
                //std::cout << "Entre " << x << in << endl;
                T* block = new T[b_size];
                blocks[out-1] = block;
                blocks[out][b_size -1] = x;
                head.first = head.first - 1;
                head.second = b_size -1;
                size++;
            }else{
               // cout << "entre " <<x << endl;
               // cout << out << in << endl;
                blocks[out][in-1] = x;
                head.second = head.second-1;
                size++;
            }
        }
    }
    void pop_back()
    {   
        if(tail.second == 0){
            blocks[tail.first] = nullptr;
            tail.first = tail.first -1;
            tail.second = b_size-1;
            
        }else{
            blocks[tail.first][tail.second] = NULL;
        }
        size --;
        
    }
    void pop_front()
    {
        if(head.second ==  b_size-1){
            blocks[head.first] = nullptr;
            head.first = head.first +1;
            head.second= 0;
        }else{
            //cout << "a" <<endl;

            blocks[head.first][head.second] = NULL;
        }
        size --;
    }
    T& operator[](int i)
    {
    //sacar posicion original
    // offset + index / b_size = block en el que esta
    // offset + index % b_size = posicion dentro del block
        int block = (head.second + i) / chunks;
        int pos = (head.second + i) % b_size;
        cout << block << " " << pos << endl;
        cout << head.second << " " << in_offset << endl;
        return blocks[block + head.first][pos] ;
        
    }
    
    void print()
    {
        for(int i=0; i<size; ++i){
            int block = (head.second + i) / chunks;
            int pos = (head.second + i) % b_size;
            
            cout << blocks[block + out_offset][pos] << " ";
        }cout << endl;
    }

    int len(){
        return size;
    }    
private: 
    int b_size;
    int chunks = 5;
    int in_offset;
    int out_offset;
    int size =-1;
    pair<int,int> head, tail;
    T** blocks = new T*[chunks];
    
};
int main(){
/*
    cout << "\n\n---------------QUEUE----------------\n\n"; 

    CQueue<int, CList<int>> q;
    q.push(3);
    q.push(6);
    q.push(1);
    q.pop();
    q.pop();
    
    cout << "\n\n---------------STACK----------------\n\n"; 

    CStack<int, CVector<int>> s;
    s.push(3);
    s.push(6);
    s.push(1);
    s.pop();
    s.pop();
    */

   /*
    cout << "\n\n---------------VECTOR----------------\n\n"; 
    
    CVector<int> v(5);
    v.push_back(2);
    v.push_back(1);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.print();
    v.expand();
    v.print();
    v.collapse();
    v.print();
   */

    /*


    cout << "\n\n---------------LISTA----------------\n\n"; 

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
    */

   
    cout << "\n\n---------------DEQUE----------------\n\n";     
    
    CDeque<int> d(4); 

    d.push_back(1); 
    d.push_back(2);
    d.push_back(3); 
    d.push_back(4);
    d.push_front(5);
    d.push_front(6);
    d.push_front(7);
    d.push_front(8);
    
    d.print();
    d.pop_back();
    d.push_front(7);
    d.push_front(8);
    d.pop_front();

    d.print();
    //cout << d.len() <<endl;
    
}