//#pragma once
//#ifndef MY_ALLOCATOR_H
//#define MY_ALLOCATOR_H
//
//namespace cyh::data {
//	template<class T>
//	class MyAllocator {
//	public:
//		using value_type = T;
//		using pointer = T*;
//		using const_pointer = const T*;
//		using void_pointer = void*;
//		using const_void_pointer = const void*;
//		using size_type=size_t;
//		using difference_type = std::ptrdiff_t;
//
//		MyAllocator() = default;
//		~MyAllocator() = default;
//
//
//		pointer allocate(size_type numObjs) {
//			return static_cast<pointer>(operator new(sizeof(T) * numObjs));
//		}
//		pointer allocate(size_type numObjs, const_void_pointer hit) {
//			return allocate(numObjs);
//		}
//		void deallocate(pointer p, size_type numObjs) {
//			operator delete(p);
//		}
//		size_type get_allocations() const
//		{
//			return allocCount;
//		}
//
//	};
//}
//
//#endif // !MY_ALLOCATOR_H
