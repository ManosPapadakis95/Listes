
#pragma once

namespace Listes{


template<class T>
class ListXor {

  struct Node {
    T data;
    Node* next_prev=nullptr;
  };

  Node* previus=nullptr; //  previus of centinel
  Node* centinel=nullptr; // previus of the new node or the last node
  unsigned int size=0;

  Node* head=nullptr;

  static Node* Oper(Node* x,Node* y){
    return reinterpret_cast<Node*>(reinterpret_cast<uintptr_t>(x) xor reinterpret_cast<uintptr_t>(y));
  }
public:

  ListXor(){
    this->head = new Node;
    this->previus=this->centinel=this->head;
  }

  ~ListXor(){
    auto *previus = this->head,*current=this->head;
    auto* next = Oper(previus, current->next_prev);
    previus = current;
    current = next;
    for(unsigned int j=1;j<this->size;++j){
      auto* next=Oper(previus,current->next_prev);
      delete previus;
      previus=current;
      current=next;
    }
    this->size=0;
    delete this->centinel;
    this->head=this->previus=this->centinel=nullptr;
  }
  T get(int i) const {
    auto *previus = this->previus,*current=this->head;
    for(int j=0;j<i;++j){
      auto* next=Oper(previus,current->next_prev);
      previus=current;
      current=next;
    }
    return current->data;
  }
  ListXor<T>& insert(int i,T data) {
    auto *previus = this->previus,*current=this->head;
    for(int j=0;j<i;++j){
      auto* next=Oper(previus,current->next_prev);
      previus=current;
      current=next;
    }

    auto* node = new Node;
    node->data=data;
    node->next_prev=previus;

    current->next_prev=Oper(previus,node);
    ++this->size;
    return *this;
  }
  ListXor<T>& push_back(T data) {

    auto* node = new Node;

    centinel->data=data;
    centinel->next_prev=Oper(previus,node);
    previus=centinel;
    centinel=node;
    ++this->size;
    return *this;
  }

  template<typename F>
  ListXor<T>& apply(F func){
    auto *previus = this->head,*current=this->head;
    for(unsigned int j=0;j<this->size;++j){
      func(current->data);
      auto* next=Oper(previus,current->next_prev);
      previus=current;
      current=next;
    }
    return *this;
  }

  inline unsigned int getsize() const {
    return this->size;
  }
};
};