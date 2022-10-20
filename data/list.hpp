#pragma once
#ifndef LIST_H
#define LIST_H
#include "../struct/linkedlist.hpp"
#include <thread>
using cyh::Struct::ListNode;
using cyh::Struct::ListNodeOperation;


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
				ListNode<T>* newNode = new ListNode<T>(t);
				size_t it_to_begin = 0;
				size_t it_to_end = 0;
				Optn::AddToEnd(data, newNode);
				first = Optn::BeginOf(data, &it_to_begin);
				last = Optn::EndOf(data, &it_to_end);
				Length = it_to_begin+it_to_end+1;
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
		bool IsEmpty = true;
		bool UseMt = false;
		ListNode<T>* first = nullptr;
		ListNode<T>* data = nullptr;
		ListNode<T>* last = nullptr;
		size_t Length = 0;
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
		T operator[](size_t index) {
			if (index >= Length) {		
				return {};
			}
			else {
				return *(_get_item_of_index(index));
			}
		}
		class Iterator
		{
		private:
			const ListNode<T>* m_pCurrentNode;
		public:
			Iterator() noexcept :
				m_pCurrentNode(first) { }
			Iterator(const ListNode<T>* pNode) noexcept :
				m_pCurrentNode(pNode) { }
			Iterator& operator=(ListNode<T>* pNode)
			{
				this->m_pCurrentNode = pNode;
				return *this;
			}
			// Prefix ++ overload
			Iterator& operator++()
			{
				if (m_pCurrentNode)
					m_pCurrentNode = m_pCurrentNode->next;
				return *this;
			}
			// Postfix ++ overload
			Iterator operator++(int)
			{
				Iterator iterator = *this;
				++* this;
				return iterator;
			}
			bool operator!=(const Iterator& iterator)
			{
				return m_pCurrentNode != iterator.m_pCurrentNode;
			}
			T operator*()
			{
				return m_pCurrentNode->data;
			}
		};
		Iterator begin()
		{
			return Iterator(first);
		}
		Iterator end()
		{
			return Iterator(nullptr);
		}
	};
}
#endif


