#pragma once
#include<vector>
template <class Elem>
class node {
public:
	Elem key;
	int grade;
	bool mark;
	node* left = nullptr;
	node* right = nullptr;
	node* child = nullptr;
	node* father = nullptr;
	node(Elem k) {
		this->key = k;
		this->grade = 0;
		this->mark = false;
	}
	~node() {
		this->left = nullptr;
		this->right = nullptr;
		this->father = nullptr;
	}
};
template <class Elem>
class fibonacciHeap
{
public:
	
	fibonacciHeap() {
		this->minH = nullptr;
		this->size = 0;
	}
	node<Elem>* getMin() {
		return this->minH;
	}
	int getSize() {
		return this->size;
	}
	void insert(Elem key);
	void deleteMin();
	void reduceKey(node<Elem>* x, Elem key);
	node<Elem>* search(node<Elem>* n,Elem key);
private:
	void insertNode(node<Elem>* x, node<Elem>* y);
	void cut(node<Elem>* x, node<Elem>* y);
	void cascadingCut(node<Elem>* y);
	void foundMin();
	void consolidate();
	node<Elem>* minH;
	float ro = (1 + sqrt(5)) / 2;
	int size;
};

template<class Elem>
inline void fibonacciHeap<Elem>::insert(Elem key)
{
	node<Elem>* nuevo = new node<Elem>(key);
	if (this->minH)
	{
		this->insertNode(this->minH, nuevo);
		if (this->minH->key>key)
		{
			this->minH = nuevo;
		}
	}
	else
	{
		this->minH = nuevo;
		this->minH->right = this->minH;
		this->minH->left = this->minH;
	}
	this->size++;
}

template<class Elem>
inline void fibonacciHeap<Elem>::deleteMin()
{
	node<Elem>* z = this->minH;
	
	
	if (z)
	{
		if (z->child)
		{

			node<Elem>* pivot = z->child;
			node<Elem>* next = z->child;
			do
			{
				next->father = nullptr;
				node<Elem>* temp = next->right;
				this->insertNode(this->minH, next);
				next = temp;
			} while (pivot != next);
		}
		this->minH->left->right = this->minH->right;
		this->minH->right->left = this->minH->left;
		this->minH = nullptr;
		if (z!=z->right) 
		{
			this->minH = z->right;
		}

		delete z;
		this->size--;
		if (size>0)
		{
			this->foundMin();
			this->consolidate();
		}
		
	}
}

template<class Elem>
inline void fibonacciHeap<Elem>::reduceKey(node<Elem>* x, Elem key)
{
	if (x->key<key)
	{
		std::cout << "New key its greater than current key\n";
		return;
	}
	x->key = key;
	node<Elem>* y = x->father;
	if (y && x->key<y->key)
	{
		this->cut(x, y);
		this->cascadingCut(y);
	}
	if (x->key<this->minH->key)
	{
		this->minH = x;
	}
}

template<class Elem>
inline node<Elem>* fibonacciHeap<Elem>::search(node<Elem>* n,Elem key)
{
	node<Elem>* init = n;
	node<Elem>* last = n;
	do
	{
		if (init->key==key)
		{
			return init;
		}
		if (init->child)
		{
			return search(init->child, key);
		}
		init = init->right;
	} while (init!=last);
	return nullptr;
}

template<class Elem>
inline void fibonacciHeap<Elem>::insertNode(node<Elem>* x, node<Elem>* y)
{
	y->right = x->right;
	x->right->left = y;
	x->right = y;
	y->left = x;
	if (x->left == x)
	{
		x->left = y;
	}
}

template<class Elem>
inline void fibonacciHeap<Elem>::cut(node<Elem>* x, node<Elem>* y)
{
	y->grade--;
	if (y->child==x)
	{
		if (x->right != x)
		{
			y->child = x->right;
		}
		else
		{
			y->child = nullptr;
		}
	}
	x->father = nullptr;
	x->mark = false;
	x->right->left = x->left;
	x->left->right = x->right;
	this->insertNode(this->minH, x);
}

template<class Elem>
inline void fibonacciHeap<Elem>::cascadingCut(node<Elem>* y)
{
	node<Elem>* z = y->father;
	if (z)
	{
		if (!y->mark)
		{
			y->mark = true;
		}
		else
		{
			this->cut(y, z);
			this->cascadingCut(z);
		}
	}
}

template<class Elem>
inline void fibonacciHeap<Elem>::foundMin()
{
	node<Elem>* pivot = this->minH;
	node<Elem>* next = this->minH;
	do
	{
		if (next->key < this->minH->key)
		{
			this->minH = next;
		}
		next = next->right;
	} while (pivot!=next);
}

template<class Elem>
inline void fibonacciHeap<Elem>::consolidate()
{

	int n = (int)(log(this->size) / log(this->ro)) + 1;
	std::vector<node<Elem>*> A(n, nullptr);
	node<Elem>* pivot = this->minH;
	node<Elem>* next = this->minH;
	do
	{
		
		node<Elem>* x = next;
		int d = next->grade;
		while (A[d])
		{
			node<Elem>* y = A[d];
			if (x->key>y->key)
			{
				node<Elem>* aux = x;
				x = y;
				y = aux;
			}
			x->grade++;
			y->mark = false;
			y->right->left = y->left;
			y->left->right = y->right;
			if (x->child)
			{
				this->insertNode(x->child, y);
				if (x->child->key>y->key)
				{
					x->child = y;
				}
			}
			else {
				
				if (y)
				{
					x->child = y;
					y->left = y;
					y->right = y;
				}
				
			}
			if (y)
			{
				y->father = x;
			}
			
			A[d] = nullptr;
			d++;
		}
		A[d] = x;
		next = x->right;
	} while (next != pivot);
}
