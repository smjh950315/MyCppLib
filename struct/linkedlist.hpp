#pragma once
#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "Basic.hpp"
namespace cyh::Struct {
	//ListNode operation
	template<class T>
	class ListNodeOperation {
	public:

		//=======================TestOK!=======================
		static void IterToBegin(ListNode<T>*& node) {
			if (node == nullptr) { return; }
			while (node->prev != nullptr) {
				node = node->prev;
			}
		}
		static void IterToEnd(ListNode<T>*& node) {
			if (node == nullptr) { return; }
			while (node->next != nullptr) {
				node = node->next;
			}
		}
		static void IterToBegin(ListNode<T>*& node, size_t* counter) {
			if (node == nullptr) { return; }
			while (node->prev != nullptr) {
				node = node->prev;
				(*counter)++;
			}
		}
		static void IterToEnd(ListNode<T>*& node, size_t* counter) {
			while (node->next != nullptr) {
				node = node->next;
				(*counter)++;
			}
		}
		static ListNode<T>* NodeOfIndex(ListNode<T>*& node, size_t index) {
			size_t counter = 0;
			ListNode<T>* temp = node;
			IterToBegin(temp);
			while (temp->next != nullptr && counter < index) {
				temp = temp->next;
				counter++;
			}
			return temp;
		}
		static ListNode<T>* BeginOf(ListNode<T>*& node) {
			if (node == nullptr) {
				return nullptr;
			}
			ListNode<T>* temp = node;
			while (temp->prev != nullptr) {
				temp = temp->prev;
			}
			return temp;
		}
		static ListNode<T>* EndOf(ListNode<T>*& node) {
			if (node == nullptr) {
				return nullptr;
			}
			ListNode<T>* temp = node;
			while (temp->next != nullptr) {
				temp = temp->next;
			}
			return temp;
		}

		static ListNode<T>* BeginOf(ListNode<T>*& node, size_t* counter) {
			if (node == nullptr) {
				return nullptr;
			}
			ListNode<T>* temp = node;
			while (temp->prev != nullptr) {
				temp = temp->prev;
				(*counter)++;
			}
			return temp;
		}
		static ListNode<T>* EndOf(ListNode<T>*& node, size_t* counter) {
			if (node == nullptr) {
				return nullptr;
			}
			ListNode<T>* temp = node;
			while (temp->next != nullptr) {
				temp = temp->next;
				(*counter)++;
			}
			return temp;
		}

		static ListNode<T>* LastNode(ListNode<T>* node) {
			if (node == nullptr) { return node; }
			while (node->next != nullptr) {
				node = node->next;
			}
			return node;
		}
		static void Remove(ListNode<T>*& node) {
			if (node == nullptr) { return; }
			if ((node->prev) == nullptr && (node->next) == nullptr) {
				delete node;
				node = nullptr;
				return;
			}
			if (node->prev == nullptr) {
				ListNode<T>* temp = node;
				node->next->prev = nullptr;
				delete temp;
				return;
			}
			if (node->next == nullptr) {
				ListNode<T>* temp = node;
				node->prev->next = nullptr;
				delete temp;
				return;
			}
			ListNode<T>* temp = node;
			node = node->next;
			node->prev = temp->prev;
			node->prev->next = temp->next;
			delete temp;
		}
		//====================================================


		/*==============operation without check===============*/
		static void AddToBegin(ListNode<T>*& node, ListNode<T>*& node_add) {
			IterToBegin(node);
			IterToEnd(node_add);
			node->prev = node_add;
			node_add->next = node;
		}
		static void AddToEnd(ListNode<T>*& node, ListNode<T>*& node_add) {
			IterToBegin(node_add);
			IterToEnd(node);
			node->next = node_add;
			node_add->prev = node;
		}
		/********************************************/


		/*=====================Not tested yet=======================*/
		static void FindToBegin(ListNode<T>*& node, T& t, bool* found) {
			ListNode<T>* iter_temp_to_begin = node;
			if (node == nullptr) {
				return;
			}
			while (node->prev != nullptr) {
				if ((*found) == true) {
					break;
				}
				if (node->data == t) {
					*found = true;
					break;
				}
			}
		}
		static void FindToEnd(ListNode<T>*& node, T& t, bool* found) {
			ListNode<T>* iter_temp_to_end = node;
			if (node == nullptr) {
				return;
			}
			while (node->next != nullptr) {
				if ((*found) == true) {
					break;
				}
				if (node->data == t) {
					*found = true;
					break;
				}
			}
		}
		static bool NodeFound(ListNode<T>*& node, T& t) {
			ListNode<T>* iter_temp_to_begin = node;
			ListNode<T>* iter_temp_to_end = node;
			bool found = false;
			std::thread th_to_beg = std::thread(&ListNodeOperation::FindToBeg, iter_temp_to_begin, t, &found);
			std::thread th_to_end = std::thread(&ListNodeOperation::FindToBeg, iter_temp_to_end, t, &found);
			th_to_beg.join();
			th_to_end.join();
			return found;
		}
		/********************************************/
	};
}
#endif // !LINKED_LIST_H
