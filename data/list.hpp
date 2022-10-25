#pragma once
#ifndef CYH_LIST_H
#define CYH_LIST_H
#include "../struct/linkedlist.hpp"
#include "../struct/iterator.hpp"
#include <thread>
using cyh::Struct::ListNode;
using cyh::Struct::ListNodeOperation;
using cyh::Struct::LNIterator;

namespace cyh::data {

	static const std::string OverRangeException = "List out of range";
	template<class T>
	class List {
	protected:
		using Optn = Struct::ListNodeOperation<T>;
		void _add(T& t) {
			if (data == nullptr) {
				data = new ListNode<T>(t);
				first = data;
				last = data;
				Length = 1;
			}
			else {
				while (data->next != nullptr) {
					data = data->next;
				}
				data->next = new ListNode<T>(t,data);
				data = data->next;
				last = data;
				Length++;
			}
		}
		void _add(ListNode<T>*& node) {
			if (data == nullptr) {
				data = node;
				first = data;
				last = data;
				Length = 1;
			}
			else {
				ListNode<T>*& temp = node;
				Optn::AddToEnd(data, temp);
				last = data;
				Optn::IterToEnd(last);
				Length+=Optn::CountOfNode(node);
			}
		}
		void _remove(ListNode<T>*& node) {
			size_t it_to_begin = 0;
			size_t it_to_end = 0;
			if (node == nullptr) { return; }
			if (node->next != nullptr) {
				data = node->next;
			}
			else {
				data = node->prev;
			}
			ListNodeOperation<int>::Remove(node);
			first = Optn::BeginOf(data, &it_to_begin);
			last = Optn::EndOf(data, &it_to_end);
			Length = it_to_begin + it_to_end + 1;
		}
		void _clear() {
			if (data == nullptr) {
				return;
			}
			Optn::IterToEnd(last);
			while (last->prev != nullptr) {
				last = last->prev;
				delete last->next;
			}
			first = data = last = nullptr;
			Length = 0;
		}
		ListNode<T>* _get_item_of_index(size_t index) {
			if (first == nullptr) {
				return nullptr;
			}
			ListNode<T>* nodeI = ListNodeOperation<T>::NodeOfIndex(first, index);
			return nodeI;
		}
	public:
		ListNode<T>* first = nullptr;
		ListNode<T>* data = nullptr;
		ListNode<T>* last = nullptr;
		bool IsEmpty = true;
		bool UseMt = false;
		size_t Length = 0;
		LNIterator<T> begin()
		{
			if (!first) {
				ListNode<T>* temp = data;
				Optn::IterToBegin(temp);
				first = temp;
			}
			return LNIterator<T>(first);
		}
		LNIterator<T> end()
		{
			return LNIterator<T>(last->next);
		}
		T operator[](size_t index) {
			if (index >= Length) {
				return {};
			}
			else {
				return *(_get_item_of_index(index));
			}
		}

		List() {
			data = nullptr;
		}
		void Add(T t) {
			_add(t);
		}
		void Remove(ListNode<T>*& t) {
			_remove(t);
		}
		ListNode<T>* Find(T& t) {

		}
		void Clear() {
			_clear();
		}


		void Show() {
			if (data == nullptr) {
				std::cout << "[]" << std::endl;
				return;
			}
			ListNode<T>* ptemp = first;
			std::cout << "[" << (ptemp->data);
			while (ptemp->next != nullptr) {
				ptemp = ptemp->next;
				std::cout << "," << ptemp->data;
			}
			std::cout << "]" << std::endl;
		}
		void rShow() {
			if (data == nullptr) { return; }
			ListNode<T>* ptemp = last;
			std::cout << "[" << (ptemp->data);
			while (ptemp->prev != nullptr) {
				ptemp = ptemp->prev;
				std::cout << "," << ptemp->data;
			}
			std::cout << "]" << std::endl;
		}


	};
}
#endif


