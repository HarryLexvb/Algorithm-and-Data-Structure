#include <iostream>
using namespace std;

////////////////////////////CLASE LIST//////////////////////////////////////////
template <class T>
struct CNode {
  CNode(T x) {
    value = x;
    next = prev = nullptr;  // 0
  }
  T value;
  CNode<T>*next, *prev;
};

template <class T>
class CList {
 public:
  CList() {
    head = tail = 0;
    nelem = 0;
  }
  ~CList() {
    // code here
    clear();
  }
  bool empty() { return head == nullptr; }

  void push_back(T x) {
    CNode<T>* n = new CNode<T>(x);
    if (!nelem)
      head = tail = n;
    else {
      n->prev = tail;
      tail->next = n;
      tail = n;
    }
    nelem++;
  }

  void push_front(const T& x) {
    CNode<T>* n = new CNode<T>(x);
    if (!nelem)
      head = tail = n;
    else {
      n->next = head;
      head->prev = n;
      head = n;
    }
    nelem++;
  }

  void pop_back() {
    // Borra el último elemento de la lista
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
    if (empty()) {
      throw runtime_error("Trying pop_back() from empty list");
    }
    if (nelem == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }

    --nelem;
  }

  void pop_front() {
    // Borra el primer elemento de la lista
    /*if (empty()){
        cout<<"No element to pop.\n";
        return;
    }
    head=head->next;
    if(head==nullptr)
        tail=nullptr;*/
    if (empty()) {
      throw runtime_error("Trying pop_front() from empty list");
    }
    if (nelem == 1) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = head->next;
      head->prev = nullptr;
    }
    --nelem;
  }

  const T& front() {
    if (empty()) {
      throw runtime_error("Trying front() from empty list");
    }

    return head->value;  // OBSERVAR
  }

  T& operator[](int i) {
    CNode<T>* n = head;
    for (int k = 0; k != i; k++) n = n->next;
    return n->value;
  }

  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  void print() {
    std::cout << "\n";
    for (CNode<T>* n = head; n != 0; n = n->next) std::cout << n->value << " ";
  }
  void print2() {
    std::cout << "\n";
    for (int i = 0; i < nelem; i++) std::cout << (*this)[i] << " ";
  }

 private:
  CNode<T>*head, *tail;
  size_t nelem;
};

////////////////////////////CLASE VECTOR//////////////////////////////////////////

template <class T>
class CVector {
 public:
  CVector(int size = 5) {
    m_size = size;
    m_v = new T[m_size];
    m_nelem = 0;
  }
  ~CVector() { delete m_v; }

  void expand() {
    T* p = new T[2 * m_size];
    for (int i = 0; i < m_size; i++) p[i] = m_v[i];
    delete m_v;
    m_v = p;
    m_size = 2 * m_size;
  }

  void push_back(T x) {
    if (m_nelem == m_size) expand();
    m_v[m_nelem] = x;
    m_nelem++;
  }

  void pop_back() {
    m_v[m_nelem] = NULL;
    m_nelem--;
  }

  void push_front(T x) {
    if (m_nelem == m_size) expand();
    for (int i = m_nelem - 1; i >= 0; i--) m_v[i + 1] = m_v[i];
    m_v[0] = x;
    m_nelem++;
  }

  void pop_front() {
    T* p = new T[m_size];
    for (int i = 1; i < m_size; i++) p[i - 1] = m_v[i];
    delete m_v;
    m_v = p;
    m_size = m_size - 1;
    m_nelem--;
    m_v[m_nelem] = NULL;
  }

  void collapse() {
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

    // std::cout << counter << " " << test << endl;
  }

  T& operator[](int i) { return m_v[i]; }

  void print() {
    for (int i = 0; i < m_nelem; i++) std::cout << m_v[i] << " ";
    std::cout << std::endl;
  }

 private:
  T* m_v;
  int m_size;
  int m_nelem;
};

///////////////////////////////CLASE STACK///////////////////////////////////////

template <class T, class S>
class CStack {
 public:
  CStack() {}
  ~CStack() { seq.clear(); }
  size_t size() { return seq.size(); }
  void push(T x) { seq.push_front(x); }
  void pop() { seq.pop_front(); }
  bool empty() { return seq.empty(); }
  const T& top() {
    if (empty()) {
      throw runtime_error("Trying top() from empty stack.");
    }
    return seq.front();
  }

 private:
  S seq;
};

///////////////////////////////CLASE QUEUE///////////////////////////////////////

template <class T, class S>
class CQueue {
 public:
  void push(T x) { seq.push_back(x); }
  void pop() { seq.pop_front(); }

 private:
  S seq;
};

///////////////////////////////////////////////////CLASE DEQUE///////////////////////////////////////7777
template <class T>
class CDeque {
 public:
  CDeque(T n_block_size) : block_size(n_block_size) {
    mid_block = block_size / 2; 
    map = new T* [block_size] { NULL };
    map[mid_block] = new T[block_size]{0};

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
    } else {
      if (array_back < (block_size - 1)) {
        array_back++;
        map[map_back][array_back] = n_value;
      } else {
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
    } else {
      if (array_front > 0) {
        array_front--;
        map[map_front][array_front] = n_value;
      } else {
        AddBlockFront();
        map[map_front][array_front] = n_value;
      }
    }
  }
  void pop_back() {
    if (start_cdeque) {
      return;
    } else if (array_back == 0 && SamePosition()) {
      map[map_back][array_back] = 0;
    } else if (array_back == 0) {
      DeleteBlock(map_back);
      map_back--;
      array_back = block_size - 1;
    } else {
      map[map_back][array_back] = 0;
      array_back--;
    }
  }
  void pop_front() {
    if (start_cdeque) {
      return;
    } else if (array_front == (block_size - 1) && SamePosition()) {
      map[map_front][array_front] = 0;
    } else if (array_front == (block_size - 1)) {
      DeleteBlock(map_front);
      map_front++;
      array_front = 0;
    } else {
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
  // pointer to main array (map)
  int** map = NULL;

  // variable to know first element aggregated
  bool start_cdeque = true;

  // variables to resize array map
  int block_size = 0;
  int mid_block = 0;
  int actual_size_map = 0;

  // index to back pointer
  int map_back = 0;
  int array_back = 0;

  // index to front pointer
  int map_front = 0;
  int array_front = 0;

  void AddBlockBack() {
    if (map_back >= (block_size - 1)) {
      ResizeMap();
    }
    map_back++;
    array_back = 0;
    map[map_back] = new int[block_size]{0};
  }
  void AddBlockFront() {
    if (map_front <= 0) {
      ResizeMap();
    }
    map_front--;
    array_front = block_size - 1;
    map[map_front] = new int[block_size]{0};
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
  void DeleteBlock(int index) {
    delete[] map[index];
    map[index] = NULL;
  }
};

int main() {
  cout << "\n\n---------------DEQUE----------------\n\n";
  /*
      la clase deque es un hibrido de la clase lista y la clase vector, este
     nuevo algoritmo es mucho mas eficiente ya que posee las mejores
     caracteristicas de la clase lista y la clase vector. las operaciones que
     debe de tener la clase Deque es la siguiente:

      -push_back: insertar al final
      -push_front: inserta al inicio
      -pop_back: borrar el ultimo elemento
      -pop_front borra el primer elemento
      -operartor[]: accede a una posicion en especifico

  */
  CDeque<int> d(2);
  d.push_back(3);
  
  //std::cout << "\n\nd[1]: " << d[0] << "\n";
  d.print();
}