#pragma once
#ifndef TUPLES_H
#define TUPLES_H
#include "../includelist.h"
#include "coord.hpp"
//#include "BaseStruct.hpp"
#include "number.hpp"
using std::vector;
using cyh::data::Coord2D;
namespace cyh::graph {
	template<class T>
	class DrawMat;
}
namespace cyh::data {
	template<class T>
	class Vector;
	template<class T>
	class Matrix;
	template<class T>
	class Phalanx;

	template<class T>
	class Vector {
	private:
		T* data = nullptr;
		void _clearData();
		void _clear();
		void _init();
		void _expand(size_t arrLength, T fill);
		void _expand(size_t arrLength, T* arr);
		void _shrink(size_t arrLength, T* arr);
		void _setRange(size_t length);
		void _setDataRef(size_t length, T* arr);
		void _setDataCopy(size_t length, T* arr);
		bool _sizeFit(size_t size);
		bool _sizeValid(size_t size);
		bool _indexValid(size_t index);
		void _fill(T t);
		void _set(T* arr, size_t size);
		void _setV(T t, size_t size);
	public:
		size_t Length = 0;
		Vector() { _init(); }
		Vector(size_t size) { _setV(0, size); }
		Vector(T* arr, size_t size) { _set(arr, size); }
		Vector(const Vector<T>& V2) { _set(V2.data, V2.Length); }
		~Vector() { _clear(); data = nullptr; }
		void Clear() { _clear(); data = nullptr; }
		void Show();
		T operator[](int i);
		Vector<T>& operator = (const Vector<T>& A2);
		Vector<T> operator + (const Vector<T>& A2);
		Vector<T> operator - (const Vector<T>& A2);
		Vector<T> operator * (const Vector<T>& A2);
		Vector<T> operator / (const Vector<T>& A2);
		Vector<T>& operator += (const Vector<T>& A2);
		Vector<T>& operator *= (const Vector<T>& A2);
		Vector<T>& operator = (const T& t);
		Vector<T> operator + (const T& t);
		Vector<T> operator - (const T& t);
		Vector<T> operator * (const T& t);
		Vector<T> operator / (const double& t);
		Vector<T>& operator += (const T& t);
		Vector<T>& operator *= (const T& t);
		void Randomize(T max);
	};
	template<class T>
	class Matrix {
	private:
		friend class cyh::graph::DrawMat<T>;
		void _clearData();
		void _clear();
		void _init();
		void _setRange(size_t w, size_t h);
		void _set(T* arr, size_t w, size_t h);
		bool _sizeFit(size_t size);
		bool _sizeFit(size_t w, size_t h);
		bool _sizeValid(size_t size);
		bool _indexValid(size_t index);
		void _fill(T t);
		T _sigma2(T** a, T** b, size_t hNow, size_t wNow, size_t length);
	public:
		T** data = nullptr;
		T* dataLinear = nullptr;
		size_t Width = 0;
		size_t Height = 0;
		size_t Length = 0;
		Matrix() { _init(); }
		Matrix(size_t w, size_t h) { _setRange(w, h); _init(); }
		Matrix(T t, size_t w, size_t h) { _setRange(w, h); _fill(t); }
		Matrix(T* arr, size_t w, size_t h) { _set(arr, w, h); }
		Matrix(const Matrix<T>& M2) { _set(M2.data[0], M2.Width, M2.Height); }
		~Matrix() { _clear(); data = nullptr; }

		void Clear() { _clear(); data = nullptr; }
		void AddTo(T t, size_t index) { data[0][index] = t; }
		void Show();
		void Initiate() { _init(); }
		void FillWith(T t) { _fill(t); }

		T* operator[](int i);
		Matrix<T>& operator = (const Matrix<T>& M2);
		Matrix<T> operator + (const Matrix<T>& M2);
		Matrix<T> operator - (const Matrix<T>& M2);
		Matrix<T> operator * (const Matrix<T>& M2);
		Matrix<T> operator / (const Matrix<T>& M2);
		Matrix<T> operator ^ (const Matrix<T>& M2);
		Matrix<T>& operator += (const Matrix<T>& M2);
		Matrix<T>& operator /= (const double& n);
		static Matrix<T> RotationMatrix(double radias);
		void Randomize(T max);
	};
	template<class T>
	class Phalanx {
	private:
		friend class cyh::graph::DrawMat<T>;
		friend class Mat;
		void _clearData();
		void _clear();
		void _init();
		void _setRange(size_t w, size_t h, size_t d);
		void _set(const Phalanx<T> P2);
		bool _sizeFit(size_t size);
		bool _sizeFit(Matrix<T> M2);
		bool _sizeFit(size_t w, size_t h, size_t d);
		bool _sizeValid(size_t size);
		bool _indexValid(size_t index);
		void _fill(T t);
	public:
		Matrix<T>** data = nullptr;
		size_t Length = 0;
		size_t Width = 0;
		size_t Height = 0;
		size_t Depth = 0;
		Phalanx() { _init(); }
		Phalanx(size_t w, size_t h, size_t d) { _setRange(w, h, d); _init(); }
		Phalanx(const Phalanx<T>& P2);
		~Phalanx() { _clear(); data = nullptr; }
		void Clear() { _clear(); data = nullptr; }
		void Show();
		void Initiate() { _init(); }
		void FillWith(T t) { _fill(t); }
		void AddMatrix(Matrix<T>& M2);
		Matrix<T>& operator[](size_t i) { return (data[i][0]); }
		Matrix<T> ToMatrixAvg();
		Matrix<T> ToMatrixSum();
		Matrix<T> ToMatrixParrallels();
		Phalanx<T>& operator = (const Phalanx<T>& P2);
		Phalanx<T> operator + (const Phalanx<T>& P2);
		void Randomize(T max);
	};
}

#endif // !TUPLES_H