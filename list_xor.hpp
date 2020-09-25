#pragma once


#include <iostream>       // std::cout, std::cerr
#include <exception>      // std::exception, std::terminate
#include <string>

using namespace std;


namespace Listes{


template<class T>
class XorList {

  struct Node {
    T data;
    Node* next_prev=nullptr;
  };

  //Node* previus=nullptr; //  previus of centinel
  Node* centinel=nullptr; // previus of the new node or the last node
  unsigned int sz=0;

  Node* head=nullptr;

  inline static Node* Oper(Node* x,Node* y){
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(x) xor reinterpret_cast<uintptr_t>(y));
  }
  inline static Node* previus(){
    return Oper(XorList<T>::centinel,XorList<T>::centinel->next_prev);
  }

public:

  XorList() : centinel(new Node), head(centinel) {}

  ~XorList(){
    // Current is the second node
    auto *previus = this->head,*current=Oper(this->head, this->head->next_prev);
    for(unsigned int j=1;j<this->sz;++j){
      auto* next=Oper(previus,current->next_prev);
      delete previus;
      previus=current;
      current=next;
    }
    this->sz=0;
    delete this->centinel;
    this->head=this->centinel=nullptr;
  }
  T get(unsigned int i) const {
    if(i>=this->sz){
      cerr<<"Error: out of bounds using index \'"+to_string(i)+"\'\n";
      std::terminate();
    }else{
      auto *previus = this->head,*current=this->head;
      for(int j=0;j<i;++j){
        auto* next=Oper(previus,current->next_prev);
        previus=current;
        current=next;
      }
      return current->data;
    }
    return head->data;
  }
  XorList<T>& insert(int i,T data) {
    auto *previus = this->head,*current=this->head;
    for(unsigned int j=0;j<i;++j){
      auto* next=Oper(previus,current->next_prev);
      previus=current;
      current=next;
    }

    auto* node = new Node;
    node->data=data;
    node->next_prev=previus;

    current->next_prev=Oper(previus,node);
    ++this->sz;
    return *this;
  }
  XorList<T>& push_back(T data) {

    auto* node = new Node;

    centinel->data=data;
    centinel->next_prev=Oper(previus(),node);
    centinel=node;
    ++this->sz;
    return *this;
  }

  XorList<T>& push_front(T data) {

    auto* node = new Node, *next=Oper(head,head->next_prev);

    head->next_prev=Oper(node,next);
    node->data=data;
    node->next_prev=Oper(head,node);
    head=node;
    ++this->sz;
    return *this;
  }

  XorList<T>& pop_front() {
    if(this->sz<1){
      cerr<<"Error: the list is empty.\n";
      std::terminate();
    }else{
      auto *next=Oper(head,head->next_prev);

      next->next_prev=Oper(next,Oper(head,next->next_prev));
      delete head;
      head=next;
      --this->sz;
    }
    return *this;
  }

  template<typename F>
  XorList<T>& apply(F func){
    auto *previus = this->head,*current=this->head;
    for(unsigned int j=0;j<this->sz;++j){
      func(current->data);
      auto* next=Oper(previus,current->next_prev);
      previus=current;
      current=next;
    }
    return *this;
  }

  inline unsigned int size() const {
    return this->sz;
  }
};
};