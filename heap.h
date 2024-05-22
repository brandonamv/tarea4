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
	Elem getMin();
	void insert(Elem x);
	void heapify(std::vector< Elem >& A);
	void deleteMin();
	void reduceKey(int x,Elem k);
	void sink(std::vector< Elem >& A, int k, int n); // hundir
	int search(Elem k);
	static void sort(std::vector< Elem >& A);
	bool operator< (const Elem& e) const {
		return this->v[0] < e;
	}
private:
	void swim(int k); //flotar
	std::vector<Elem> v;
};

template<class Elem>
inline heap<Elem>::heap()
{
}

template<class Elem>
inline heap<Elem>::heap(std::vector<Elem>& a)
{
	this->v = a;
}

template<class Elem>
inline heap<Elem>::~heap()
{
}

template<class Elem>
inline Elem heap<Elem>::getMin()
{
	return this->v[0];
}

template<class Elem>
inline void heap<Elem>::heapify(std::vector<Elem>& A)
{
	int n = A.size();
	for (int i = n / 2; i >= 0; i--)
		this->sink(A, i, n);
}

template<class Elem>
inline void heap<Elem>::deleteMin()
{
	std::swap(this->v[0], this->v[this->v.size() - 1]);
	this->v.pop_back();
	this->sink(this->v, 0, this->v.size());
}

template<class Elem>
inline void heap<Elem>::reduceKey(int x, Elem k)
{
	if (this->v[x] < k)
	{
		std::cout << "New key its greater than current key\n";
		return;
	}
	this->v[x] = k;
	this->swim(x);
}


template<class Elem>
inline void heap<Elem>::sink(std::vector<Elem>& A, int k, int n)
{
	while (2 * k+1 < n) {
		int j = 2 * k + 1;
		// bajo por el más grande de los hijos
		// si es un maxheap
		if (j < n-1 && A[j] > A[j + 1]) j++;
		if (!(A[k] > A[j])) break;
		std::swap(A[k], A[j]);
		k = j;
	}
}

template<class Elem>
inline int heap<Elem>::search(Elem k)
{
	for (int i = 0; i < this->v.size(); i++)
	{
		if (this->v[i]==k)
		{
			return i;
		}
	}
	return -1;
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
inline void heap<Elem>::insert(Elem x)
{
	this->v.push_back(x);
	this->swim(this->v.size()-1);
}

template<class Elem>
inline void heap<Elem>::swim(int k)
{
	while (k>0&&this->v[k/2]>this->v[k])
	{
		std::swap(this->v[k / 2], this->v[k]);
		k /= 2;
	}
}
