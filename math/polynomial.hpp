#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "../data/text.hpp"
#include "../struct/basic.hpp";
#include "../struct/stack.hpp";
using cyh::data::text;
using cyh::Struct::btNode;
using cyh::Struct::Stack;
namespace cyh::data {


	/*  (a+b)*(c+d)   *+ab+cd   */
	static const string op = "+-*/^)";
	static const int priority_op[] = { 1,1,2,2,3,4 };

	class Polynomial {
	private:
		text _raw;
		void add_order(string& func);
		void to_prefix(string func);
		void to_tree(string func);
		bool is_operator(char c);
		void set(text func);
		void load_function();
		void func_n1();
		void func_n2();
		void func_n3();
		
	public:
		text n1;
		text n2;
		text n3;
		btNode<char>* root = nullptr;
		btNode<char>* fTree = nullptr;
		int nCount = 0;
		Polynomial(text n);
		Polynomial(text n1, text n2);
		Polynomial(text n1, text n2, text n3);
		Polynomial& operator=(const text& t);
	};



}
#endif