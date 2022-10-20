#include "tuples.hpp"
using cyh::data::Vector;
using cyh::data::Matrix;
using cyh::data::Phalanx;
using cyh::data::Number;

template<class T>
void Vector<T>::_clearData() {
	if (data != nullptr)
	{
		delete data;
	}
	data = nullptr;
}
template<class T>
void Vector<T>::_clear() {
	_clearData();
	Length = 0;
}
template<class T>
void Vector<T>::_init() {
	_clearData();
	if (Length == 0) {
		data = nullptr;
	}
	else {
		data = new T[Length];
	}
}

template<class T>
void Vector<T>::_expand(size_t arrLength, T fill) {
	if (!_sizeValid(arrLength)) { return; }
	size_t OldLength = Length;
	Length = arrLength;
	if (data == nullptr) {
		_init();
	}
	T* OldData = data;
	data = new T[Length];
	for (size_t i = 0; i < OldLength; i++) {
		*(data + i) = *(OldData + i);
	}
	for (size_t i = OldLength; i < Length; i++) {
		*(data + i) = fill;
	}
	delete OldData;
}
template<class T>
void Vector<T>::_expand(size_t arrLength, T* arr) {
	if (!_sizeValid(arrLength)) { return; }
	size_t OldLength = Length;
	Length = arrLength;
	if (data == nullptr) {
		_init();
	}
	T* temp = arr;
	T* OldData = data;
	data = new T[Length];
	for (size_t i = 0; i < Length; i++) {
		*(data + i) = *(temp + i);
	}
	delete OldData;
}
template<class T>
void Vector<T>::_shrink(size_t arrLength, T* arr) {
	if (!_sizeValid(arrLength)) { return; }
	size_t OldLength = Length;
	Length = arrLength;
	if (data == nullptr) {
		_init();
	}
	T* temp = arr;
	T* OldData = data;
	data = new T[Length];
	for (size_t i = 0; i < Length; i++) {
		*(data + i) = *(temp + i);
	}
	delete OldData;
}
template<class T>
void Vector<T>::_setRange(size_t newLength) {
	Length = newLength;
}
template<class T>
void Vector<T>::_setDataRef(size_t arrLength, T* arr) {
	if (arrLength <= Length) {
		_clearData();
		data = arr;
		Length = arrLength;
	}
	else {
		_expand(arrLength, arr);
	}
}
template<class T>
void Vector<T>::_setDataCopy(size_t arrLength, T* arr) {
	if (arrLength <= Length) {
		_shrink(arrLength, arr);
	}
	else {
		_expand(arrLength, arr);
	}
}
template<class T>
bool Vector<T>::_sizeFit(size_t size) {
	bool _valid = true;
	if (size > Length) {
		_valid = false;
	}
	if (size < 0) {
		_valid = false;
	}
	return _valid;
}
template<class T>
bool Vector<T>::_sizeValid(size_t size) {
	bool _valid = true;
	if (size < 1) {
		return false;
	}
	return _valid;
}
template<class T>
bool Vector<T>::_indexValid(size_t index) {
	bool _valid = true;
	if (index > Length - 1) {
		_valid = false;
	}
	if (index < 0) {
		_valid = false;
	}
	return _valid;
}
template<class T>
void Vector<T>::_fill(T t) {
	if (Length == 0) { return; }
	if (data == nullptr) {
		_init();
	}
	for (int i = 0; i < Length; i++) {
		*(data + i) = t;
	}
}
template<class T>
void Vector<T>::_set(T* arr, size_t size) {
	_setDataCopy(size, arr);
}
template<class T>
void Vector<T>::_setV(T t, size_t size) {
	Length = size;
	_init();
	_fill(t);
}
template<class T>
void Vector<T>::Show() {
	cout << "[";
	for (int i = 0; i < Length - 1; i++) {
		cout << *(data + i) << ",";
	}
	cout << *(data + Length - 1) << "]" << endl;
}
template<class T>
T Vector<T>::operator [](int i) {
	return data[i];
}
template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T>& V2) {
	_set(V2.data, V2.Length);
	return *this;
}
template<class T>
Vector<T> Vector<T>::operator + (const Vector<T>& V2) {
	if (this->Length == V2.Length) {
		Vector<T> temp(this->Length);
		for (int i = 0; i < this->Length; i++) {
			temp.data[i] = this->data[i] + V2.data[i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Vector<T> Vector<T>::operator - (const Vector<T>& V2) {
	if (this->Length == V2.Length) {
		Vector<T> temp(this->Length);
		for (int i = 0; i < this->Length; i++) {
			temp.data[i] = this->data[i] - V2.data[i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Vector<T> Vector<T>::operator * (const Vector<T>& V2) {
	if (this->Length == V2.Length) {
		Vector<T> temp(this->Length);
		for (int i = 0; i < this->Length; i++) {
			temp.data[i] = this->data[i] * V2.data[i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Vector<T> Vector<T>::operator / (const Vector<T>& V2) {
	if (this->Length == V2.Length) {
		Vector<T> temp(this->Length);
		for (int i = 0; i < this->Length; i++) {
			temp.data[i] = this->data[i] / V2.data[i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator += (const Vector<T>& V2) {
	if (this->Length != V2.Length) { return *this; }
	for (int i = 0; i < Length; i++) {
		data[i] += V2.data[i];
	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator *= (const Vector<T>& V2) {
	if (this->Length != V2.Length) { return *this; }
	for (int i = 0; i < Length; i++) {
		data[i] *= V2.data[i];
	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator = (const T& t) {
	_fill(t);
	return *this;
}
template<class T>
Vector<T> Vector<T>::operator + (const T& t) {
	Vector<T> temp(this->Length);
	for (int i = 0; i < this->Length; i++) {
		temp.data[i] = this->data[i] + t;
	}
	return temp;
}
template<class T>
Vector<T> Vector<T>::operator - (const T& t) {
	Vector<T> temp(this->Length);
	for (int i = 0; i < this->Length; i++) {
		temp.data[i] = this->data[i] - t;
	}
	return temp;
}
template<class T>
Vector<T> Vector<T>::operator * (const T& t) {
	Vector<T> temp(this->Length);
	for (int i = 0; i < this->Length; i++) {
		temp.data[i] = this->data[i] * t;
	}
	return temp;
}
template<class T>
Vector<T> Vector<T>::operator / (const double& t) {
	Vector<T> temp(this->Length);
	if (t) {
		Vector<T> temp(this->Length);
		for (int i = 0; i < this->Length; i++) {
			temp.data[i] = this->data[i] / (Number)t;
		}
	}
	temp = *this;
	return temp;
}
template<class T>
Vector<T>& Vector<T>::operator += (const T& t) {
	for (int i = 0; i < Length; i++) {
		data[i] += t;
	}
	return *this;
}
template<class T>
Vector<T>& Vector<T>::operator *= (const T& t) {
	for (int i = 0; i < Length; i++) {
		data[i] *= t;
	}
	return *this;
}
template<class T>
void Vector<T>::Randomize(T max) {
	for (size_t i = 0; i < Length; i++) {
		data[i] = Number::RandFloat(0,max);
	}
}

template<class T>
void Matrix<T>::_clearData() {
	if (data != nullptr) {
		delete[] data[0];
		data = nullptr;
	}
	data = nullptr;
}
template<class T>
void Matrix<T>::_clear() {
	_clearData();
	_setRange(0, 0);
}
template<class T>
void Matrix<T>::_init() {
	_clearData();
	if (Length != 0) {
		this->data = new T * [Height];
		this->data[0] = new T[Length];
		for (int i = 1; i < Height; i++) {
			this->data[i] = this->data[i - 1] + Width;
		}
		for (int i = 0; i < Length; i++) {
			this->data[0][i] = 0;
		}
		dataLinear = data[0];
	}
	else {
		data = nullptr;
	}
}
template<class T>
void Matrix<T>::_setRange(size_t w, size_t h) {
	Width = w;
	Height = h;
	Length = w * h;
}
template<class T>
void Matrix<T>::_set(T* arr, size_t w, size_t h) {
	_setRange(w, h);
	_init();
	for (int i = 0; i < Length; i++) {
		*(*data + i) = *(arr + i);
	}
}
template<class T>
bool Matrix<T>::_sizeFit(size_t size) {
	bool _valid = true;
	if (size > Length) {
		_valid = false;
	}
	if (size < 0) {
		_valid = false;
	}
	return _valid;
}
template<class T>
bool Matrix<T>::_sizeFit(size_t w, size_t h) {
	bool _valid = true;
	if (Width != w) {
		_valid = false;
	}
	if (Height != h) {
		_valid = false;
	}
	return _valid;
}
template<class T>
bool Matrix<T>::_sizeValid(size_t size) {
	bool _valid = true;
	if (size < 1) {
		return false;
	}
	return _valid;
}
template<class T>
bool Matrix<T>::_indexValid(size_t index) {
	bool _valid = true;
	if (index > Length - 1) {
		_valid = false;
	}
	if (index < 0) {
		_valid = false;
	}
	return _valid;
}
template<class T>
void Matrix<T>::_fill(T t) {
	if (Length == 0) { return; }
	if (data == nullptr) {
		_init();
	}
	for (int i = 0; i < Length; i++) {
		*(*data + i) = t;
	}
}
template<class T>
T Matrix<T>::_sigma2(T** a, T** b, size_t hNow, size_t wNow, size_t length) {
	double tmp = 0;
	for (int i = 0; i < length; i++) {
		tmp += a[hNow][i] * b[i][wNow];
	}
	return tmp;
}
template<class T>
void Matrix<T>::Show() {
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			cout << setw(5) << data[i][j];
		}
		cout << endl;
	}
}
template<class T>
T* Matrix<T>::operator[](int i) {
	return data[i];
}
template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& M2) {
	_set(M2.data[0], M2.Width, M2.Height);
	return *this;
}
template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& M2) {
	if (_sizeFit(M2.Width, M2.Height)) {
		size_t w = M2.Width;
		size_t h = M2.Height;
		Matrix<T> temp(w, h);
		for (size_t i = 0; i < w * h; i++) {
			temp.data[0][i] = this->data[0][i] + M2.data[0][i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& M2) {
	if (_sizeFit(M2.Width, M2.Height)) {
		size_t w = M2.Width;
		size_t h = M2.Height;
		Matrix<T> temp(w, h);
		for (size_t i = 0; i < w * h; i++) {
			temp.data[0][i] = this->data[0][i] + M2.data[0][i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& M2) {
	if (_sizeFit(M2.Width, M2.Height)) {
		size_t w = M2.Width;
		size_t h = M2.Height;
		Matrix<T> temp(w, h);
		for (size_t i = 0; i < w * h; i++) {
			temp.data[0][i] = this->data[0][i] * M2.data[0][i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Matrix<T> Matrix<T>::operator/(const Matrix<T>& M2) {
	if (_sizeFit(M2.Width, M2.Height)) {
		size_t w = M2.Width;
		size_t h = M2.Height;
		Matrix<T> temp(w, h);
		for (size_t i = 0; i < w * h; i++) {
			temp.data[0][i] = this->data[0][i] / M2.data[0][i];
		}
		return temp;
	}
	return *this;
}
template<class T>
Matrix<T> Matrix<T>::operator^(const Matrix<T>& M2) {
	size_t w = this->Width;
	size_t h = this->Height;
	size_t w2 = M2.Width;
	size_t h2 = M2.Height;
	size_t NewW = M2.Width;
	size_t NewH = this->Height;
	if (w == h2) {
		Matrix<T> temp(NewW, NewH); //1, 2
		for (size_t H = 0; H < NewH; H++) {
			for (size_t W = 0; W < NewW; W++) {
				temp.data[H][W] = _sigma2(data, M2.data, H, W, NewW);
			}
		}
		return temp;
	}
	return *this;
}
template<class T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& M2) {
	if (_sizeFit(M2.Width, M2.Height)) {
		for (size_t i = 0; i < Length; i++) {
			data[0][i] = data[0][i] + M2.data[0][i];
		}
	}
	return *this;
}
template<class T>
Matrix<T>& Matrix<T>::operator/=(const double& n) {
	if (n) {
		for (size_t i = 0; i < Length; i++) {
			data[0][i] = data[0][i] / (Number)n;
		}
	}
	return *this;
}
template<class T>
Matrix<T> Matrix<T>::RotationMatrix(double radias) {
	Matrix<T> rot(2, 2);
	rot.data[0][0] = std::cos(radias);
	rot.data[0][1] = -std::sin(radias);
	rot.data[0][2] = std::sin(radias);
	rot.data[0][3] = std::cos(radias);
	return rot;
}
template<class T>
void Matrix<T>::Randomize(T max) {
	for (size_t i = 0; i < Length; i++) {
		data[0][i] = Number::RandFloat(0, max);
	}
}

template<class T>
void Phalanx<T>::_clearData() {
	if (data != nullptr) {
		for (int i = 0; i < Depth; i++) {
			data[i][0].Clear();
			delete data[i];
		}
		delete[] data;
	}
	data = nullptr;
}
template<class T>
void Phalanx<T>::_clear() {
	_clearData();
	_setRange(0, 0, 0);
}
template<class T>
void Phalanx<T>::_init() {
	_clearData();
	if (Length != 0) {
		this->data = new Matrix<T>*[Depth];
		for (int i = 0; i < Depth; i++) {
			data[i] = new Matrix<T>(Width, Height);
			data[i][0].Initiate();
		}
	}
	else {
		data = nullptr;
	}
}
template<class T>
void Phalanx<T>::_setRange(size_t w, size_t h, size_t d) {
	Width = w;
	Height = h;
	Depth = d;
	Length = w * h * d;
}
template<class T>
void Phalanx<T>::_set(const Phalanx<T> P2) {
	Width = P2.Width;
	Height = P2.Height;
	Depth = P2.Depth;
	_init();
	for (int i = 0; i < Depth; i++) {
		data[i][0] = P2.data[i][0];
	}
}
template<class T>
bool Phalanx<T>::_sizeFit(size_t size) {
	bool _valid = true;
	if (size > Length) {
		_valid = false;
	}
	if (size < 0) {
		_valid = false;
	}
	return _valid;
}
template<class T>
bool Phalanx<T>::_sizeFit(Matrix<T> M2) {
	bool _valid = true;
	if (M2.Width != Width) {
		_valid = false;
	}
	if (M2.Height != Height) {
		_valid = false;
	}
	return _valid;
}
template<class T>
bool Phalanx<T>::_sizeFit(size_t w, size_t h, size_t d) {
	bool _valid = true;
	if (w != Width) {
		_valid = false;
	}
	if (h != Height) {
		_valid = false;
	}
	if (d != Depth) {
		_valid = false;
	}
	return _valid;
}
template<class T>
bool Phalanx<T>::_sizeValid(size_t size) {
	bool _valid = true;
	if (size < 1) {
		return false;
	}
	return _valid;
}
template<class T>
bool Phalanx<T>::_indexValid(size_t index) {
	bool _valid = true;
	if (index > Length - 1) {
		_valid = false;
	}
	if (index < 0) {
		_valid = false;
	}
	return _valid;
}
template<class T>
void Phalanx<T>::_fill(T t) {
	if (Length == 0) { return; }
	if (data == nullptr) {
		_init();
	}
	for (int i = 0; i < Depth; i++) {
		data[i][0].FillWith(t);
	}
}
template<class T>
Phalanx<T>::Phalanx(const Phalanx<T>& P2) {
	_setRange(P2.Width, P2.Height, P2.Depth);
	_init();
	for (int i = 0; i < Depth; i++) {
		data[i][0] = P2.data[i][0];
	}
}
template<class T>
void Phalanx<T>::Show() {
	for (int i = 0; i < Depth; i++) {
		cout << "mat" << i << endl;
		data[i][0].Show();
	}
}
template<class T>
void Phalanx<T>::AddMatrix(Matrix<T>& M2) {
	if (!_sizeFit(M2)) {
		return;
	}
	size_t oldDep = Depth;
	Depth += 1;
	Matrix<T>** temp = data;
	data = new Matrix<T>*[Depth];
	for (size_t i = 0; i < oldDep; i++) {
		data[i] = temp[i];
	}
	data[Depth - 1][0] = M2;
	_setRange(Width, Height, Depth);
	temp = nullptr;
}
template<class T>
Matrix<T> Phalanx<T>::ToMatrixAvg() {
	Matrix<T> m = ToMatrixSum();
	m /= Depth;
	return m;
}
template<class T>
Matrix<T> Phalanx<T>::ToMatrixSum() {
	Matrix<T> m(Width, Height);
	for (int i = 0; i < Depth; i++) {
		m += data[i][0];
	}
	return m;
}
template<class T>
Matrix<T> Phalanx<T>::ToMatrixParrallels() {
	size_t newMatWidth = Width * Depth;
	Matrix<T> m(newMatWidth, Height);
	size_t iNow = 0;
	for (int i = 0; i < Width * Height; i++) {
		for (int j = 0; j < Depth; j++) {
			m.AddTo(data[j][0][0][i], iNow);
			iNow++;
		}
	}
	return m;
}
template<class T>
Phalanx<T>& Phalanx<T>::operator = (const Phalanx<T>& P2) {
	_setRange(P2.Width, P2.Height, P2.Depth);
	_init();
	for (int i = 0; i < Depth; i++) {
		data[i][0] = P2.data[i][0];
	}
	return *this;
}
template<class T>
Phalanx<T> Phalanx<T>::operator+(const Phalanx<T>& P2) {
	if (_sizeFit(P2.Width, P2.Height, P2.Depth)) {
		Phalanx<T> _temp(Width, Height, Depth);
		for (int i = 0; i < Depth; i++) {
			_temp.data[i][0] = data[i][0] + P2.data[i][0];
		}
		return _temp;
	}
	return *this;
}
template<class T>
void Phalanx<T>::Randomize(T max) {
	for (size_t i = 0; i < Depth; i++) {
		data[i][0].Randomize(max);
	}
}

#pragma region templateType

template class Vector<unsigned>;
template class Matrix<unsigned char>;
template class Vector<int>;
template class Vector<float>;
template class Vector<double>;
template class Vector<long>;
template class Vector<char>;
template class Vector<unsigned char>;
template class Vector<Number>;

template class Matrix<unsigned>;
template class Matrix<unsigned char>;
template class Matrix<int>;
template class Matrix<float>;
template class Matrix<double>;
template class Matrix<long>;
template class Matrix<Number>;

template class Phalanx<unsigned>;
template class Phalanx<unsigned char>;
template class Phalanx<int>;
template class Phalanx<float>;
template class Phalanx<double>;
template class Phalanx<long>;
template class Phalanx<Number>;

#pragma endregion