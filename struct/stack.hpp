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
		size_t Capacity = INT_MAX;
		size_t Size = 0;
		Stack() {}
		Stack(size_t capacity) :Capacity(capacity) {}
		void Push(T t) {
			Node<T>* n = new Node<T>(t, this->top);
			top = n;
			Size++;
		}
		T Pop() noexcept {
			if (IsEmpty()) { return T{ 0 }; }
			Node<T>* temp = top;
			top = top->link;
			T data = temp->data;
			delete temp;
			Size--;
			return data;
		}
		bool IsEmpty() {
			return top == nullptr;
		}
		T Top() noexcept {
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
