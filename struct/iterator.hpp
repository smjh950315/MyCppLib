#pragma once
#ifndef CYH_ITERATOR_H
#define CYH_ITERATOR_H
#include "basic.hpp"
using cyh::Struct::ListNode;
namespace cyh::Struct {

	template<class T>
	class Iterator {
	private:
	public:
		const T* m_pCurrent;
		Iterator() noexcept :
			m_pCurrent(nullptr) { }
		Iterator(const T* pNode) noexcept :
			m_pCurrent(pNode) { }
		Iterator& operator=(T* pNode) {
			this->m_pCurrent = pNode;
			return *this;
		}
		Iterator& operator++() {
			if (m_pCurrent) {
				m_pCurrent++;
			}
			return *this;
		}
		Iterator operator++(int) {
			Iterator iterator = *this;
			++* this;
			return iterator;
		}
		bool operator!=(const Iterator& iterator)
		{
			return m_pCurrent != iterator.m_pCurrent;
		}
		T& operator*()
		{
			return *m_pCurrent;
		}
	};
	template<class T>
	class LNIterator {
	private:
	public:
		const ListNode<T>* m_pCurrent;
		LNIterator() noexcept :
			m_pCurrent(nullptr) { }
		LNIterator(const ListNode<T>* pNode) noexcept :
			m_pCurrent(pNode) { }
		LNIterator<T>& operator=(ListNode<T>* pNode) {
			this->m_pCurrent = pNode;
			return *this;
		}
		LNIterator<T>& operator++() {
			if (m_pCurrent) {
				m_pCurrent = m_pCurrent->next;
			}
			return *this;
		}
		LNIterator<T> operator++(int) {
			LNIterator iterator = *this;
			++* this;
			return iterator;
		}
		bool operator!=(const LNIterator<T>& iterator)
		{
			return m_pCurrent != iterator.m_pCurrent;
		}
		T operator*()
		{
			return m_pCurrent->data;
		}
	};
}

#endif // !CYH_CONTAINER_H
