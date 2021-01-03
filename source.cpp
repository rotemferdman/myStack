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
	bool isTop = true;
	bool isClean = true;
	node<T>* top;
public:
	stack() : top(new node<T>) {};
	void push(T data);
	T pop();
	void clean();
	T operator[](int);
	int size();
};

int main()
{
	stack<int> s;
	s.push(4);
	s.push(8);
	std::cout << s.pop();
	std::cout << s.pop();
	std::cout << s.pop();
	s.push(9);
	s.push(6);
	std::cout << std::endl;
	s.clean();
	s.push(10);
	s.push(10);
	s.push(8);
	int a = s[2];
	a = s[1];
	a = s.size();
	s.clean();

	std::cout << s.pop();
}

template<class T>
void stack<T>::push(T data)
{
	this->isClean = false;
	node<T>* n = new node<T>;
	n->data = data;
	n->next = nullptr;

	if (this->isTop)
	{
		this->isTop = false;
		this->top = n;
	}
	else
	{
		n->next = this->top;
		this->top = n;
	}
}

template<class T>
T stack<T>::pop()
{
	node<T>* n;
	if (!this->isClean)
	{
		n = this->top;
		if (this->top->next) //moving to next node
		{
			this->top = this->top->next;
		}
		else //returnning top and thats all
		{
			this->isTop = true;
			this->isClean = true;
			return n->data;
		}
	}
	else
	{
		std::cout << "stack is clean" << std::endl;
		return NULL;
	}
	return n->data;
}

template<class T>
void stack<T>::clean()
{
	top->data = NULL;
	top->next = nullptr;
	this->isClean = true;
	this->isTop = true;
	
}

template<class T>
T stack<T>::operator[](int index)
{
	node<T>* n = this->top;
	if (index == 0)
	{
		return n->data;
	}

	for (int i = 0; i < index; i++)
	{
		if (n->next == nullptr && i != index - 1) //where not in the end yet and in the end of the linked list
		{
			return NULL;
		}
		n = n->next;
	}
	if (n == nullptr) //before we returnning n just in case
	{
		return 0;
	}
	return n->data; //else...
}

template<class T>
int stack<T>::size()
{
	int i = 0;
	node<T>* n = this->top;
	while (true)
	{
		i++;
		if (n->next != nullptr)
		{
			n = n->next;
		}
		else
		{
			return i;
		}
	}
}
