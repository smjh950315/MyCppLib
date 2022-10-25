#ifndef CYH_POLYNOMIAL_H
#define CYH_POLYNOMIAL_H
#include "../data/text.hpp"
#include "../data/keyvaluepair.hpp"
#include "../data/dictionary.hpp"
#include "../struct/basic.hpp"
#include "../struct/stack.hpp"
using cyh::data::text;
using cyh::data::KeyValuePair;
using cyh::data::Dictionary;
using cyh::Struct::btNode;
using cyh::Struct::Stack;

namespace cyh::math {

	static const string numbers = "0123456789";
	static const wstring operators = L"+-*/";
	static const int priority_op[4] = { 1,1,2,2 };
	static const wchar_t ParameterList[10] = 
	{L'壹',L'貳',L'叁',L'肆',L'伍',L'陸',L'柒',L'捌',L'玖',L'拾'};
	static bool is_operator(wchar_t c) {
		size_t i = 0;
		for (auto& o : operators) {
			if (c == o) {
				break;
			}
			i++;
		}
		return i < operators.length();
	}
	static int op_priority(wchar_t c) {
		int index = 0;
		for (auto o : operators) {
			if (c == o) {
				return priority_op[index];
			}
			index++;
		}
		return index == operators.length() ? -1 : index;
	}
	static double GetComputeResult(wchar_t oper, double a, double b) {
		switch (oper) {
		case '+':
			return a + b;
		case '-':
			return a - b;
		case '*':
			return a * b;
		case '/':
			if (b == 0) { return INT_MAX; }
			return a / b;
		default:
			return 0;
		}
	}
	struct ComputeNode
	{
		ComputeNode* parent = nullptr;
		ComputeNode* lChild = nullptr;
		ComputeNode* rChild = nullptr;
		bool isLeft = true;
		bool Operator = false;
		wchar_t value;
		double DBL_VAL = 0;
		ComputeNode(wchar_t _val) :value(_val) {}
		ComputeNode(wchar_t _val, ComputeNode* prnt) :value(_val), parent(prnt) {}
		ComputeNode(wchar_t _val, ComputeNode* prnt, bool is_left)
			:value(_val), parent(prnt), isLeft(is_left) {
			Operator = is_operator(_val);
		}
		double GetValue(Dictionary param) {
			if (Operator) {
				double l = lChild == nullptr ? 0 : lChild->GetValue(param);
				double r = rChild == nullptr ? 0 : rChild->GetValue(param);
				return GetComputeResult(value, l, r);
			}
			for (auto p : param.KVPairs) {
				if (value == p.Key) {
					return p.Value.ToDouble();
				}
			}
			return 0;
		}
	};
	class Polynomial {
	private:		
		void buffer_init();
		void buffer_clear();
		void chptr_init(wchar_t*& chptr, size_t length);
		void chptr_clear(wchar_t*& chptr);
		void infix_to_prefix();
		void read_func(text func);
		void load_function();
		void func_n1();
		void func_n2();
		void func_n3();
		void to_binary_tree();
		void build_sub_tree();
		void clear_sub_tree(ComputeNode* tree);
		void get_operand(text t);
		void replace_operand(text& _raw);
		wchar_t* _prefix = nullptr;
		wchar_t* CharStack = nullptr;
		wchar_t* Infix = nullptr;
		size_t infix_L = 0;
		Dictionary Parameters;
		vector<text> paramTemp;
		ComputeNode* pCurrent = nullptr;
		Stack<ComputeNode*> CNStack;	
	public:
		text n1;
		text n2;
		text n3;
		text RawStr;	
		wstring Prefix;
		wstring rPrefix;
		size_t MaxLength = 256;
		ComputeNode* Root = nullptr;
		int nCount = 0;
		Polynomial(text n);
		Polynomial(text n1, text n2);
		Polynomial(text n1, text n2, text n3);
		Polynomial& operator=(text t);
		double Parameter();
	};
}
#endif