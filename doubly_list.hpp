#pragma once


#include <iostream>       // std::cout, std::cerr
#include <exception>      // std::terminate
#include <string>     // std::to_string

using namespace std;


namespace Listes {


  template<class T>
  class DList {

    struct Node {
      T data;
      Node* next = nullptr;
      Node* prev = nullptr;
    };

    unsigned int sz = 0;

    Node* head = nullptr;

  public:

    DList() {}

    ~DList() {
      // Current is the second node
      auto *current;
      for (unsigned int j = 0; j < this->sz; ++j) {
        current = head;
        head=head->next;
        delete current;
      }
      this->sz = 0;
      this->head = nullptr;
    }
    T get(unsigned int i) const {
#ifdef DOUBLY_LIST_SAFE
      if (i >= this->sz) {
        cerr << "Error: out of bounds using index \'" + to_string(i) + "\'\n";
        std::terminate();
      }
#endif
      auto *current=head;
      for (unsigned int j = 0; j < i; ++j,current = current->next);
      return current->data;
    }
    DList<T>& insert(unsigned int i, T data) {
#ifdef DOUBLY_LIST_SAFE
      if (i >= this->sz) {
        cerr << "Error: out of bounds using index \'" + to_string(i) + "\'\n";
        std::terminate();
      }
#endif

      auto *current=head;
      for (unsigned int j = 0; j < i; ++j,current = current->next);

      auto* node = new Node;
      node->data = data;
      node->next = current;
      node->previus = current->previus;

      current->previus = node;
      ++this->sz;
      return *this;
    }
    DList<T>& push_back(T data) {

	  auto *current=head;
      for (unsigned int j = 0; j < this->sz-1; ++j,current = current->next);

      auto* node = new Node;

      node->previus = current;
      node->data = data;
      current->next = node;
      ++this->sz;
      return *this;
    }

    DList<T>& push_front(T data) {

      auto* node = new Node;
      head->previus = node;
      node->next = head;
      node->data = data;
      ++this->sz;
      return *this;
    }

    DList<T>& pop_front() {
#ifdef DOUBLY_LIST_SAFE
      if (this->sz < 1) {
        cerr << "Error: the list is empty.\n";
        std::terminate();
      }
#endif
      auto *current = head;
      head=head->next;
      delete current;
      --this->sz;
      return *this;
    }

    DList<T>& pop_back() {

#ifdef DOUBLY_LIST_SAFE
      if (this->sz < 1) {
        cerr << "Error: the list is empty.\n";
        std::terminate();
      }
#endif

      auto *current=head;
      for (unsigned int j = 0; j < this->sz-2; ++j,current = current->next);
      delete current->next;
      current->next=nullptr;
      --this->sz;

      return *this;
    }

    template<typename F>
    DList<T>& apply(F func) {
      auto *current=head;
      for (unsigned int j = 0; j < this->sz; ++j,current = current->next) {
      	func(current->data);
      }
      return *this;
    }

    inline unsigned int size() const {
      return this->sz;
    }
  };
};