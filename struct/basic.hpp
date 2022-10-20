#pragma once
#include<iostream>
#ifndef STRUCT_H
#define STRUCT_H

namespace cyh::Struct
{
	//single direction
	template <class T>
	struct Node {
		T data;
		Node* link = nullptr;
		Node() :data(0) {}
		Node(T t) :data(t) {}
		Node(T t, Node* n) :data(t), link(n) {}
	};
	//tree node
	template <class T>
	struct Leaf
	{
		T data;
		Leaf* parent = nullptr;
		Leaf* prev = nullptr;
		Leaf* next = nullptr;
		Leaf* first_child = nullptr;
		Leaf* child = nullptr;
		Leaf() :data(0) { }
		Leaf(T t) :data(t) { }
		Leaf(T t, Leaf* pre) {
			data = t;
			prev = pre;
			parent = pre->parent;
		}
		Leaf(T t, Leaf* prnt, Leaf* pre){
			data = t;
			parent = prnt;
			prev = pre;
		}
		void AddChild(T t) {
			if (!child) {
				child = new Leaf(this, nullptr);
				first_child = child;
			}
			else {
				while (child->next != nullptr) {
					child = child->next;
				}
				child->next = new Leaf(t, child);
			}
		}
	};
	//double direction
	template<class T>
	struct ListNode {
		T data;
		ListNode* prev = nullptr;
		ListNode* next = nullptr;
		ListNode() :data(0) { }
		ListNode(T t) :data(t) { }
		ListNode(T t, ListNode* _prev) :data(t), prev(_prev) { }
		operator T() {
			return data;
		}
	};

	template <class T>
	struct btNode {
		T data;
		btNode* parent = nullptr;
		btNode* lChild = nullptr;
		btNode* rChild = nullptr;

		btNode():data(0){}
		btNode(T t, btNode* prnt): data(t),parent(prnt){}
	};
};

#endif // !STRUCT_H