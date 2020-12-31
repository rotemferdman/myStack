#include <iostream>

template <class T>
class node
{
public:
	T data;
	node* next;
};
template<class T>
class stack
{
private:
	node<T>* top;
public:
	stack() : top(new node<T>) {};
	void push(T data);
	T pop();
};

int main()
{
	stack<int> s;
	s.push(4);
	s.push(8);
	std::cout << s.pop();
}

template<class T>
void stack<T>::push(T data)
{
	node<T>* n = new node<T>;
	n->data = data;
	n->next = this->top;
	this->top = n;
}

template<class T>
T stack<T>::pop()
{
	node<T>* n = this->top;
	this->top = this->top->next;
	return n->data;
}
