#include "polynomial.hpp"
using cyh::math::Polynomial;


void Polynomial::buffer_init() {
	size_t funcLen = RawStr.Length;
	chptr_init(CharStack, funcLen);
	chptr_init(_prefix, funcLen);
}
void Polynomial::buffer_clear() {
	size_t funcLen = RawStr.Length;
	chptr_clear(CharStack);
	chptr_clear(_prefix);
}
void Polynomial::chptr_init(wchar_t*& chptr, size_t length) {
	chptr_clear(chptr);
	if (chptr != nullptr) {
		delete[] chptr;
		chptr = nullptr;
	}
	chptr = new wchar_t[length];
	for (int i = 0; i < length; i++) {
		chptr[i] = L'\0';
	}
}
void Polynomial::chptr_clear(wchar_t*& chptr) {
	if (chptr != nullptr) {
		delete[] chptr;
		chptr = nullptr;
	}
}
void Polynomial::infix_to_prefix() {
	buffer_init();
	int iInfix = infix_L - 1;
	int in = iInfix, pre = 0, top = 0;
	while (in >= 0) {
		wchar_t c = Infix[in];
		switch (c) {
		case L'(':
			if (top < 0) { break; }
			while (CharStack[top] != L')') {
				_prefix[pre++] = CharStack[top--];
				if (top < 0) { break; }
			}
			top--;
			break;
		case L')':
			CharStack[++top] = Infix[in];
			break;
		case L'+':case L'-':case L'*':case L'/':
			while (op_priority(CharStack[top]) >= op_priority(Infix[in])) {
				_prefix[pre++] = CharStack[top--];
			}
			CharStack[++top] = Infix[in];
			break;
		default:
			_prefix[pre++] = Infix[in];
			break;
		}
		in--;
	}
	while (top > 0) {
		_prefix[pre++] = CharStack[top--];
	}
	Prefix = _prefix;
	rPrefix = _prefix;
	buffer_clear();
	std::reverse(Prefix.begin(), Prefix.end());
}
void Polynomial::read_func(text func) {
	if (func.Length >= MaxLength) {
		return;
	}
	RawStr = func;
	RawStr.RemoveAll('\n');
	RawStr.Trim();
	get_operand(RawStr);
	text _raw;
	replace_operand(_raw);
	wstring raw = _raw;
	infix_L = raw.length();
	Infix = &raw[0];
	infix_to_prefix();
}

void Polynomial::load_function() {
	switch (nCount)
	{
	case 1:
		func_n1();
		break;
	case 2:
		func_n1();
		break;
	case 3:
		func_n1();
		break;
	default:
		break;
	}
}
void Polynomial::func_n1() {


}
void Polynomial::func_n2() {

}
void Polynomial::func_n3() {

}

void Polynomial::to_binary_tree() {
	size_t preLen = Prefix.length();
	if (preLen == 0) { return; }
	if (Root != nullptr) {
		clear_sub_tree(Root);
	}
	buffer_init();
	build_sub_tree();
}
void Polynomial::build_sub_tree() {	
	for (auto& c : rPrefix) {
		ComputeNode* n = new ComputeNode(c);
		if (!is_operator(c)) {
			CNStack.Push(n);
		}
		else {
			if (!CNStack.IsEmpty()) {
				n->rChild = CNStack.Pop();
				n->rChild->parent = n;
				n->rChild->isLeft = false;
				n->lChild = CNStack.Pop();
				n->lChild->parent = n;
				n->lChild->isLeft = true;
				CNStack.Push(n);
			}
		}
	}
	Root = CNStack.Pop();
}
void Polynomial::clear_sub_tree(ComputeNode* tree) {
	if (tree->lChild != nullptr) {
		clear_sub_tree(tree->lChild);
	}
	if (tree->rChild != nullptr) {
		clear_sub_tree(tree->rChild);
	}
	if (tree->parent != nullptr) {
		ComputeNode* temp = tree;
		tree = tree->parent;
		if (temp->isLeft) {
			tree->lChild = nullptr;
		}
		else {
			tree->rChild = nullptr;
		}
		delete temp;
	}
	else {
		delete tree;
		tree = nullptr;
	}
}
void Polynomial::get_operand(text txt) {
	auto temp_plus = txt.Splits("+");
	vector<text> temp_minus;
	for (auto& t : temp_plus) {
		auto temp1 = t.Splits("-");
		temp_minus.insert(temp_minus.end(), temp1.begin(), temp1.end());
	}
	vector<text> temp_times;
	for (auto& t : temp_minus) {
		auto temp1 = t.Splits("*");
		temp_times.insert(temp_times.end(), temp1.begin(), temp1.end());
	}
	vector<text> temp_div;
	for (auto& t : temp_times) {
		auto temp1 = t.Splits("/");
		temp_div.insert(temp_div.end(), temp1.begin(), temp1.end());
	}
	vector<text> temp_lq;
	for (auto& t : temp_div) {
		auto temp1 = t.Splits("/");
		temp_lq.insert(temp_lq.end(), temp1.begin(), temp1.end());
	}
	vector<text> temp_rq;
	for (auto& t : temp_lq) {
		auto temp1 = t.Splits("/");
		temp_rq.insert(temp_rq.end(), temp1.begin(), temp1.end());
	}
	for (auto rq : temp_rq) {
		text trq = rq;
		trq.RemoveAll(L'(');
		trq.RemoveAll(L')');
		if (trq.Length != 0) {
			paramTemp.push_back(trq);
		}
	}
}
void Polynomial::replace_operand(text& _raw) {
	_raw = RawStr;
	vector<text> paramTemp2;
	paramTemp2.push_back(paramTemp[0]);
	for (auto& para : paramTemp) {
		int i = 0;
		for (auto& para2 : paramTemp2) {
			if (para.ToWStr() == para2) {
				break;
			}	
			i++;
		}
		if (i == paramTemp2.size()) {
			paramTemp2.push_back(para);
		}		
	}
	paramTemp = paramTemp2;
	int prmLst = 0;
	for (auto& p : paramTemp) {
		text c = ParameterList[prmLst++];
		Parameters.Add(c,p);
	}	
	for (auto kvp : Parameters.KVPairs) {
		_raw.ReplaceAll(kvp.Value, kvp.Key);
	}	
}

Polynomial::Polynomial(text n) {
	this->n1 = n;
	nCount = 1;
}
Polynomial::Polynomial(text n1, text n2) {
	this->n1 = n1;
	this->n2 = n2;
	nCount = 2;
}
Polynomial::Polynomial(text n1, text n2, text n3) {
	this->n1 = n1;
	this->n2 = n2;
	this->n3 = n3;
	nCount = 3;
}
Polynomial& Polynomial::operator=(text t) {
	read_func(t);
	to_binary_tree();
	return *this;
}
double Polynomial::Parameter() {
	return 0;
}

