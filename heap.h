#pragma once
#include<iostream>
#include<vector>
#include <algorithm>

template <class Elem>
class heap: std::vector<Elem>
{
public:
	heap();
	heap(std::vector<Elem>& a);
	~heap();
	void heapify(std::vector< Elem >& A);
	void sink(std::vector< Elem >& A, int k, int n); // hundir
	static void sort(std::vector< Elem >& A);
	bool operator< (const Elem& e) const {
		return this->at(0) < e;
	}
private:
	void swim(int k); //flotar
};

template<class Elem>
inline heap<Elem>::heap()
{
}

template<class Elem>
inline heap<Elem>::heap(std::vector<Elem>& a)
{
	
}

template<class Elem>
inline heap<Elem>::~heap()
{
}

template<class Elem>
inline void heap<Elem>::heapify(std::vector<Elem>& A)
{
	int n = A.size();
	for (int i = n / 2; i >= 0; i--)
		this->sink(A, i, n);
}

template<class Elem>
inline void heap<Elem>::sink(std::vector<Elem>& A, int k, int n)
{
	while (2 * k+1 < n) {
		int j = 2 * k+1;
		// bajo por el más grande de los hijos
		// si es un maxheap
		if (j < n-1 && A[j] < A[j + 1]) j++;
		if (!(A[k] < A[j])) break;
		std::swap(A[k], A[j]);
		k = j;
	}
}
	
template<class Elem>
inline void heap<Elem>::sort(std::vector<Elem>& A)
{
	heap a;
	a.heapify(A);
	int n = A.size();
	for (int i = n-1; i > 0; i--) {
		std::swap(A[0], A[i]);
		a.sink(A, 0, --n);
	}
}

template<class Elem>
inline void heap<Elem>::swim(int k)
{
}
