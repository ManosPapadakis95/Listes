#pragma once


#include <iostream>       // std::cout, std::cerr
#include <exception>      // std::terminate
#include <string>		  // std::to_string

using namespace std;


namespace Listes {


	template<class T>
	class List {

		struct Node {
			T data;
			Node* next = nullptr;
		};

		Node* centinel = nullptr; // previus of the new node or the last node
		unsigned int sz = 0;

		Node *head = nullptr;

	public:

		List() : centinel(new Node), head(centinel) {}

		~List() {
			for (auto *current = head; head;) {
				head = head->next;
				delete current;
				current = head;				
			}
			this->sz = 0;
			this->head = this->centinel = nullptr;
		}
		T get(unsigned int i) const {
#ifdef LIST_SAFE
			if (i >= this->sz) {
				cerr << "Error: out of bounds using index \'" + to_string(i) + "\'\n";
				std::terminate();
			}
#endif
			auto *current = this->head;
			for (unsigned int j = 0; j < i; ++j) {
				current = current->next;
			}
			return current->data;
		}
		List<T>& remove(unsigned int i){
#ifdef LIST_SAFE
			if (i >= this->sz) {
				cerr << "Error: out of bounds using index \'" + to_string(i) + "\'\n";
				std::terminate();
			}
#endif
			auto *current = this->head;
			--i;
			for (unsigned int j = 0; j < i; ++j) {
				current = current->next;
			}
			auto* del = current->next;
			current = del->next;
			delete del;
			--this->sz;
			return *this;
		}
		List<T>& insert(unsigned int i, T data) {
#ifdef LIST_SAFE
			if (i >= this->sz) {
				cerr << "Error: out of bounds using index \'" + to_string(i) + "\'\n";
				std::terminate();
			}
#endif

			auto *current = this->head;
			for (unsigned int j = 0; j < i; ++j) {
				current = current->next;
			}

			auto* node = new Node;
			node->data = data;
			node->next = current->next;

			
			current->next =node;
			++this->sz;
			return *this;
		}
		 List<T>& push_back(T data) {

			auto* node = new Node;

			centinel->data = data;
			centinel->next = node;
			centinel = node;
			++this->sz;
			return *this;
		}

		List<T>& push_front(T data) {

			auto* node = new Node;

			node->data = data;
			node->next = head->next;
			head = node;
			++this->sz;
			return *this;
		}

		List<T>& pop_front() {
#ifdef LIST_SAFE
			if (this->sz < 1) {
				cerr << "Error: the list is empty.\n";
				std::terminate();
			}
#endif
			auto *front = head;

			head = head->next;
			delete front;
			--this->sz;
			return *this;
		}

		List<T>& pop_back() {

#ifdef LIST_SAFE
			if (this->sz < 1) {
				cerr << "Error: the list is empty.\n";
				std::terminate();
			}
#endif
			auto *current = head;
			for (; current->next != centinel; current = current->next);
			delete centinel;
			centinel = current;
			--this->sz;

			return *this;
		}

		template<typename F>
		List<T>& apply(F func) {
			for (auto *current = head;current!=centinel;current=current->next){
				func(current->data);
			}
			return *this;
		}

		inline unsigned int size() const {
			return this->sz;
		}
	};
};
