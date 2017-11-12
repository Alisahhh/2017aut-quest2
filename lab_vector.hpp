#ifndef LAB_VECTOR_HPP_
#define LAB_VECTOR_HPP_
//#define Lab std
//#endif

#include "labafx.hpp"
#include <cstdio>
#include <cstring>
#include <iostream>
namespace Lab {
template <typename T> class vector {
public:
  vector();
  class iterator {
  public:
    iterator() {
      point = nullptr;
      // return *this;
    }
    iterator(T *pointTmp) {
      point = pointTmp;
      // return *this;
    }
    // T &operator*();
    // iterator operator+(int n);
    // zht does not require the followings, make him happy.
    // NOOOOOOOOOOOOO!
    // iterator &operator++();
    // bool operator==(const iterator &another) const;
    // bool operator!=(const iterator &another) const;
    // iterator operator++(int);
  public:
    // add your data and function here
    T *point;
    // T &operator*() { return point; }
    iterator operator+(const int &n) {
      // iterator ite = *this;
      // ite.t += n;
      // return ite;
      this->point += n;
      return *this;
    }
    int operator-(const iterator &another) { return point - another.point; }
    iterator &operator++() {
      point++;
      return *this;
    }
    T &operator*() { return *point; }
    bool operator==(const iterator &another) const {
      return another.point == point;
    }
    bool operator!=(const iterator &another) const {
      return another.point != point;
    }
  };
  iterator begin();
  iterator end();
  size_t size() const;
  void push_back(const T &item);
  void pop_back();
  void erase(iterator iter);
  void clear();
  size_t capacity();
  void shrink_to_fit();
  void reserve(size_t resv_size);
  ~vector();

private:
  T *data;
  int length;
  int cap;
  void restruction();
  // add your data and function here
};
template <typename T> vector<T>::vector() {
  data = nullptr;
  length = 0;
  cap = 0;
}

// template <typename T> T &vector<T>::iterator::operator*() { return *point; }

template <typename T> typename vector<T>::iterator vector<T>::begin() {
  return iterator(&data[0]);
}

template <typename T> typename vector<T>::iterator vector<T>::end() {
  return iterator(&data[length]);
}

template <typename T> size_t vector<T>::size() const { return size_t(length); }

template <typename T> void vector<T>::push_back(const T &item) {
  if (length == cap) {
    restruction();
  }
  data[length++] = item;
}

template <typename T> void vector<T>::pop_back() {
  if (!length) {
    std::cout << "The vector is empty";
  } else {
    data[--length] = T();
  }
}

template <typename T> void vector<T>::erase(iterator iter) {
  int dist = iter - begin();
  std::memmove(data + dist, data + dist + 1, (length - dist - 1) * sizeof(T));
  data[--length] = T();
}

template <typename T> void vector<T>::clear() {
  while (length)
    data[--length] = T();
}

template <typename T> size_t vector<T>::capacity() { return size_t(cap); }

template <typename T> void vector<T>::shrink_to_fit() {
  data = (T *)realloc(data, (length + 1) * sizeof(T));
  cap = length;
}

template <typename T> void vector<T>::reserve(size_t resv_size) {
  cap = resv_size;
  T *newdata = new T[cap + 1];
  if (length) {
    memcpy(newdata, data, (cap + 1) * sizeof(T));
    delete[] data;
  }
  data = newdata;
}

template <typename T> void vector<T>::restruction() {
  if (cap == 0)
    cap = 1;
  else
    cap *= 2;
  T *newdata = new T[cap + 1];
  if (length) {
    memcpy(newdata, data, sizeof(T) * length);
    delete[] data;
  }
  data = newdata;
}

template <typename T> vector<T>::~vector() {
  if (data) {
    delete[] data;
    data = nullptr;
  }
  length = 0;
  cap = 0;
}
} // namespace Lab

#endif
