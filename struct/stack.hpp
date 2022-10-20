#pragma once
#ifndef ADV_STRUCT_H
#define ADV_STRUCT_H
#include "basic.hpp"
using namespace cyh::Struct;
namespace cyh::Struct {

	//stack
	template<class T>
	struct Stack {
		Node<T>* top = nullptr;
		size_t Capacity;
		Stack() {}
		Stack(size_t capacity) :Capacity(capacity) {}
		void Push(T t) {
			Node<T>* n = new Node<T>(t, this->top);
			top = n;
		}
		T Pop() {
			Node<T> temp = top;
			top = temp->link;
			T data = temp->data;
			free(temp);
			return data;
		}
		bool IsEmpty() {
			return top == nullptr;
		}
		T Top() {
			return top->data;
		}
		~Stack() {
			while (!IsEmpty()) {
				Pop();
			}
		}
	};

}

#endif // !ADV_STRUCT_H
