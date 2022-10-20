#include "polynomial.hpp"
using cyh::data::Polynomial;
void Polynomial::add_order(string& func) {
	string temp = "";
	int cBrS = 0;
	for (auto& c : func) {
		if (c == ')') {
			cBrS--;
		}
		if (c == '(') {
			cBrS++;
		}
	}

}
void Polynomial::to_prefix(string func) {
	string temp = "";
	int countOfBrb = 0;
	for (auto& c : func) {
		
	}

}
void Polynomial::to_tree(string func) {

	
}
bool Polynomial::is_operator(char c) {
	return op.find(c) != std::string::npos;
}
void Polynomial::set(text func) {
	_raw = func;
	_raw.Replace("\n", "");
	_raw.Trim();
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
Polynomial& Polynomial::operator=(const text& t) {
	set(t);
	return *this;
}