#ifndef LAB_LIST_HPP_
#define LAB_LIST_HPP_
namespace Lab {
template <typename Type> class list {
public:
  list();
  struct node {
    Type data = 0;
    node *pre = nullptr;
    node *next = nullptr;
  };
  class iterator {
  public:
    iterator() {
      beg = nullptr;
      end = nullptr;
      length = 0;
    }
    iterator(node *currentTmp) { current = currentTmp; }
    // Type &operator*();
    // assume zht asking for prefix increment
    // make him unhappy
    // iterator &operator++();
    // iterator &operator--();
    Type &operator*() { return current->data; }
    iterator &operator++() {
      current = current->next;
      return *this;
    }
    iterator &operator--() {
      current = current->pre;
      return *this;
    }
    bool operator!=(const iterator &another) const {
      return another.current != current;
    }
    node *current;
    // add your data and function here
  };

public:
  void push_back(const Type &elem);
  void push_front(const Type &elem);
  iterator begin();
  iterator end();
  int size() const;
  void pop_front();
  void pop_back();
  void erase(iterator iter);
  void clear();
  ~list();

public:
  node *beg;
  node *en;
  int length;
  // add your data and function here
};

template <typename Type> list<Type>::list() {
  beg = nullptr;
  en = nullptr;
  length = 0;
}

template <typename Type> typename list<Type>::iterator list<Type>::begin() {
  return iterator(beg);
}

template <typename Type> typename list<Type>::iterator list<Type>::end() {
  return iterator(en);
}
template <typename Type> void list<Type>::push_back(const Type &elem) {
  node *newNode = new node;
  newNode->data = elem;
  newNode->pre = en;
  newNode->next = nullptr;
  if (en) {
    en->next = newNode;
  }
  en = newNode;
  if (!length) {
    beg = newNode;
  }
  length++;
}

template <typename Type> void list<Type>::push_front(const Type &elem) {
  node *newNode = new node;
  newNode->data = elem;
  newNode->next = beg;
  newNode->pre = nullptr;
  if (beg) {
    beg->pre = newNode;
  }
  beg = newNode;
  if (!length)
    en = newNode;
  length++;
}

template <typename Type> int list<Type>::size() const { return length; }

template <typename Type> void list<Type>::pop_front() {
  node *newNode = new node;
  newNode = beg;
  beg = beg->next;
  if (beg)
    beg->pre = nullptr;
  length--;
  delete newNode;
}

template <typename Type> void list<Type>::pop_back() {
  node *newNode = new node;
  length--;
  newNode = en;
  en = en->pre;
  if (en)
    en->next = nullptr;
  delete newNode;
}
template <typename Type> void list<Type>::erase(iterator iter) {
  // node *newNode = iter.current->pre;
  if (iter.current->pre)
    iter.current->pre->next = iter.current->next;
  if (iter.current->next)
    iter.current->next->pre = iter.current->pre;
  delete iter.current;
  length--;
}
template <typename Type> void list<Type>::clear() {
  while (beg != en) {
    node *newNode = beg->next;
    delete beg;
    beg = newNode;
    length--;
  }
  delete beg;
  beg = en = nullptr;
  length = 0;
}
template <typename Type> list<Type>::~list() {
  /*while (beg.next != nullptr) {
    node *newNode = beg->next;
    delete beg;
    beg = newNode;
  }
  delete beg;*/
  list::clear();
}
} // namespace Lab

#endif
// (.*) \(\*(.*)\)\(.*?desc[,]?(.*)\)
// (.*)\(\*(.*)\)\(.*?iter[,]?(.*)\)
