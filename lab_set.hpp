#ifndef LAB_SET_HPP_
#define LAB_SET_HPP_
#define red 0
#define black 1
#include "labafx.hpp"

// DO NOT MODIFY BELOW

namespace Lab {
template <typename T> class set {
public:
  struct node {
    bool color;
    T data;
    node *parent;
    node *left;
    node *right;
    node() {
      color = red;
      data = 0;
      parent = nullptr;
      left = nullptr;
      right = nullptr;
    }
    node *grandParent(node *n) { return n->parent->parent; }

    node *uncle(node *n) {
      if (n->parent == grandParent(n)->left)
        return grandParent(n)->right;
      else
        return grandParent(n)->left;
    }
    node *brother(node *n) {
      if (n == n->parent->left)
        return n->parent->right;
      else
        return n->parent->left;
    }
  };
  set() {
    node *treeRoot = nullptr;
    length = 0;
  };
  int size() const { return length; }
  void insert(const T &item);
  void insert_case1(node *n);
  void insert_case2(node *n);
  void insert_case3(node *n);
  void insert_case4(node *n);
  void insert_case5(node *n);
  void rotate_left(node *n);
  void rotate_right(node *n);
  class iterator {
  public:
    node *current;
    const T &operator*() { return current->data; }
    iterator(node *currentTmp) { current = currentTmp; }
    iterator operator++(int) {
      node *leftChild = this->current->left;
      node *rightChild = this->current->right;
      node *now = rightChild;
      while (now->left) {
        now = now->left;
      }
      return iterator(now);
    }; // for iter++
    iterator operator--(int) {
      node *leftChild = this.current->left;
      node *rightChild = this.current->right;
      node *now = leftChild;
      while (now->right) {
        now = now->right;
      }
      return iterator(now);
    };
    iterator &operator++() {
      node *leftChild = this->current->left;
      node *rightChild = this->current->right;
      this->current = rightChild;
      while (this->current->left) {
        this->current = this->current->left;
      }
      return *this;
    };
    iterator &operator--() {
      node *leftChild = this->current->left;
      node *rightChild = this->current->right;
      this->current = leftChild;
      while (this->current->right) {
        this->current = this->current->right;
      }
      return *this;
    }
    bool operator==(const iterator &another) const {
      return (&current) == (&another.current);
    };
    bool operator!=(const iterator &another) const {
      return (&current) != (&another.current);
    };

    // private:
    // int length;
    // add your data and function here
  };
  iterator find(const T &item);
  void erase(iterator it);
  void delete_case1(node *n);
  void delete_case2(node *n);
  void delete_case3(node *n);
  void delete_case4(node *n);
  void delete_case5(node *n);
  void delete_case6(node *n);
  void delete_one_child(node *n);
  void del(node *now);
  iterator begin();
  iterator end();
  void clear();
  ~set() { clear(); };

private:
  int length;
  node *data;
  node *beg;
  node *en;
  node *treeRoot = nullptr;
  // add your data and function here
};
template <typename T> typename set<T>::iterator set<T>::begin() {
  if (!treeRoot)
    return nullptr;
  node *leftChild = treeRoot->left;
  node *rightChild = treeRoot->right;
  if (!leftChild)
    return treeRoot;
  while (leftChild->left) {
    leftChild = leftChild->left;
  }
  return iterator(leftChild);
}

template <typename T> typename set<T>::iterator set<T>::end() {
  if (!treeRoot)
    return nullptr;
  node *leftChild = treeRoot->left;
  node *rightChild = treeRoot->right;
  if (!leftChild)
    return treeRoot;
  while (rightChild->right) {
    rightChild = rightChild->right;
  }
  return iterator(rightChild);
}

template <typename T> void set<T>::rotate_left(node *n) {
  if (n->parent == nullptr) {
    treeRoot = n;
    return;
  }
  node *gParent = n->grandParent(n);
  node *father = n->parent;
  node *son = n->left;
  father->right = son;
  if (son)
    son->parent = father;
  n->left = father;
  father->parent = n;
  if (treeRoot == father)
    treeRoot = n;
  n->parent = gParent;
  if (gParent) {
    if (gParent->left == father)
      gParent->left = n;
    else
      gParent->right = n;
  }
}

template <typename T> void set<T>::rotate_right(node *n) {
  if (n->parent == nullptr) {
    treeRoot = n;
    return;
  }
  node *gParent = n->grandParent(n);
  node *father = n->parent;
  node *son = n->right;
  father->left = son;
  if (son)
    son->parent = father;
  n->right = father;
  father->parent = n;
  if (treeRoot == father)
    treeRoot = n;
  n->parent = gParent;
  if (gParent) {
    if (gParent->left == father)
      gParent->left = n;
    else
      gParent->right = n;
  }
}

template <typename T> void set<T>::insert(const T &item) {
  node *newNode = new node;
  newNode->data = item;
  node *now = treeRoot;
  while (now) {
    node *left = now->left;
    node *right = now->right;
    if (newNode->data == now->data)
      return;
    if (left && newNode->data < now->data)
      now = left;
    else if (right && newNode->data > now->data)
      now = right;
    else {
      // newNode= now;
      if (newNode->data < now->data) {
        now->left = newNode;
        newNode->parent = now;
        break;
      } else {
        now->right = newNode;
        newNode->parent = now;
        break;
      }
    }
    // if(now->left->data<newNode->data)
  }
  length++;
  insert_case1(newNode);
}
template <typename T> void set<T>::insert_case1(node *n) {
  if (n->parent == nullptr) {
    treeRoot = n;
    n->color = black;
  } else {
    insert_case2(n);
  }
}

template <typename T> void set<T>::insert_case2(node *n) {
  if (n->parent->color == black)
    return;
  else
    insert_case3(n);
}

template <typename T> void set<T>::insert_case3(node *n) {
  if (n->uncle(n) != nullptr && n->uncle(n)->color == red &&
      n->parent->color == red) {
    n->uncle(n)->color = black;
    n->parent->color = black;
    n->grandParent(n)->color = red;
    insert_case1(n->grandParent(n));
  } else
    insert_case4(n);
}

template <typename T> void set<T>::insert_case4(node *n) {
  if (n == n->parent->right && n->parent == n->grandParent(n)->left) {
    rotate_left(n->parent);
    n = n->left;
  }
  if (n == n->parent->left && n->parent == n->grandParent(n)->right) {
    rotate_right(n->parent);
    n = n->right;
  }
  insert_case5(n);
}
template <typename T> void set<T>::insert_case5(node *n) {
  n->parent->color = black;
  n->grandParent(n)->color = red;
  if (n == n->parent->left && n->parent == n->grandParent(n)->left) {
    rotate_right(n->grandParent(n));
  } else {
    rotate_left(n->grandParent(n));
  }
}
template <typename T> typename set<T>::iterator set<T>::find(const T &item) {
  node *now = treeRoot;
  while (now) {
    // node *leftChild=now->left;
    // node *rightChild=now->right;
    if (now->data == item)
      return iterator(now);
    if (now->data < now)
      now = now->right;
    else if (now->data > now)
      now = now->left;
  }
  return end();
}

template <typename T> void set<T>::erase(iterator it) {
  node *leftChild = it.current->left;
  node *rightChild = it.current->right;
  node *tmp = it.current;
  if (leftChild && rightChild) {
    tmp = leftChild;
    while (tmp->right)
      tmp = tmp->right;
    it.current->data = tmp->data;
    // delete tmp;
  }
  delete_one_child(tmp);
  length--;
}

template <typename T> void set<T>::delete_one_child(node *n) {
  if (!n)
    return;
  node *child;
  if (n->left)
    child = n->left;
  else
    child = n->right;
  if (n->left == nullptr && n->right == nullptr && n->parent == nullptr) {
    n = nullptr;
    treeRoot = n;
    return;
  } // if root
  if (n->parent == nullptr) {
    delete n;
    treeRoot = child;
    treeRoot->color = black;
    child->parent = nullptr;
    return;
  }
  if (n->parent->left == n)
    n->parent->left = child;
  else
    n->parent->right = child;
  child->parent = n->parent;
  if (n->color == black) {
    if (child->color == red) {
      child->color = black;
    } else
      delete_case1(child);
  }
  delete n;
}

template <typename T> void set<T>::delete_case1(node *n) {
  if (n->parent = nullptr) {
    n->color = black;
    return;
  }
  delete_case2(n);
}

template <typename T> void set<T>::delete_case2(node *n) {
  node *bro = n->brother(n);
  if (bro->color == red) {
    n->parent->color = red;
    bro->color = black;
    if (n->parent->left == n)
      rotate_left(n->parent);
    else
      rotate_right(n->parent);
  }
  delete_case3(n);
}

template <typename T> void set<T>::delete_case3(node *n) {
  node *bro = n->brother(n);
  if ((n->parent->color == black) && (bro->left->color == black) &&
      (bro->color == black) && (bro->right->color == black)) {
    bro->color = red;
    delete_case1(n->parent);
  } else
    delete_case4(n);
}

template <typename T> void set<T>::delete_case4(node *n) {
  node *bro = n->brother(n);
  if ((n->parent->color == red) && (bro->left->color == black) &&
      (bro->color == black) && (bro->right->color == black)) {
    bro->color = red;
    bro->parent->color = black;
  } else
    delete_case5(n);
}

template <typename T> void set<T>::delete_case5(node *n) {
  node *bro = n->brother(n);
  if (bro->color == black) {
    if ((n == n->parent->left) && (bro->right->color == black) &&
        (bro->left->color == red)) {
      bro->color = red;
      bro->left->color = black;
      rotate_right(bro);
    } else if ((n == n->parent->right) && (bro->right->color == red) &&
               (bro->left->color == black)) {
      bro->color = red;
      bro->right->color = black;
      rotate_left(bro);
    }
    delete_case6(n);
  }
}

template <typename T> void set<T>::delete_case6(node *n) {
  node *bro = n->brother(n);
  bro->color = n->parent->color;
  n->parent->color = black;

  if (n == n->parent->left) {
    bro->right->color = black;
    rotate_left(n->parent);
  } else {
    bro->left->color = black;
    rotate_right(n->parent);
  }
}

template <typename T> void set<T>::clear() { del(treeRoot); }
template <typename T> void set<T>::del(node *now) {
  if (!now)
    return;
  node *leftChild = now->left;
  node *rightChild = now->right;
  del(leftChild);
  del(rightChild);
  delete now;
  length--;
}
} // namespace Lab
#endif
