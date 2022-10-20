//#pragma once
//#ifndef MY_ITERATOR_H
//#define MY_ITERATOR_H
//
//
//namespace cyh::data {
//	template<class T>
//	class MyIterator {
//	protected:
//		const T* pCurrent;
//	public:
//		MyIterator() noexcept : pCurrent() {}
//		MyIterator(const T* pt) noexcept : pCurrent(pt) { }
//		MyIterator& operator=(T* pt) {
//			pCurrent = pt;
//			return *this;
//		}
//		MyIterator& operator++() {
//			if (pCurrent) {
//				pCurrent++;
//			}
//			return *this;
//		}
//		MyIterator operator++() {
//			MyIterator<T> iterator = *this;
//			++* this;
//			return iterator;
//		}
//		bool operator!=(const MyIterator& iterator)
//		{
//			return pCurrent != iterator.pCurrent;
//		}
//		int operator*()
//		{
//			return *pCurrent;
//		}
//	};
//}
//
//#endif // !MY_ITERATOR_H
