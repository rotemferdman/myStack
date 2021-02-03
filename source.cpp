#include <iostream>
#include <stdlib.h>
#include <string.h>

template <class T>
class node
{
public:
	T data;
	node* next;
};

template <class T>
class sequence
{
protected:
	bool isClean = true;
public:
	virtual void push(T data) = 0;
	virtual void clean() = 0;
	virtual int size() = 0;
	virtual T operator[](int) = 0;
};


template<class T>
class stack : public sequence<T>
{
private:
	bool isTop = true;
	bool isClean = true;
	node<T>* top;
public:
	stack() : top(new node<T>) {};
	~stack() { delete this->top; }
	virtual void push(T data);
	T pop();
	virtual void clean();
	virtual T operator[](int);
	virtual int size();
};

template<class T>
class arr : public sequence<T>
{
private:
	bool isClean = true;
	size_t size_arr = 0;
	T* p_arr = new T(this->size_arr);
public:
	virtual void push(T data);
	virtual void clean();
	virtual int size();
	virtual T operator[](int);
};

template<class T, class U>
class pair
{
private:
	bool isClean = true;
	size_t size_pair = 0;
	arr<T> arr1;
	arr<U> arr2;
public:
	void push(T key, U val);
	U pop(T key);
	size_t size();
	U operator[](T key);
	void clean();
};


class str
{
private:
	bool isClean = true;
	size_t size_str = 0;
	char* string = (char*)malloc(sizeof(char) * size_str);

public:
	void operator=(char*);
	void operator+=(char*);
	char operator[](size_t);
	void print();
	int find(const char a);
	void zelda();


};

int main()
{
	char p[20] = { 'a' };
	char* s = (char*)"string";
	int length = strlen(s);
	int i;
	for (i = 0; i < length; i++)
	{
		p[i] = s[length - i];
	}
	printf("%s", p);
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

template<class T>
void arr<T>::push(T data)
{
	this->isClean = false;
	this->size_arr++;
	realloc(this->p_arr, sizeof(T) * this->size_arr);
	this->p_arr[this->size_arr - 1] = data;
}

template<class T>
void arr<T>::clean()
{
	this->size_arr = 0;
	this->p_arr = new T[this->size_arr];
}

template<class T>
int arr<T>::size()
{
	return this->size_arr;
}

template<class T>
T arr<T>::operator[](int index)
{
	if (this->size_arr < index || index < 0)
	{
		return -1; //error with index
	}
	return this->p_arr[index];
}

template<class T, class U>
void pair<T, U>::push(T key, U val)
{
	this->arr1.push(key); //pushing the key
	this->arr2.push(val); //pushing the value
	this->size_pair++;
}

template<class T, class U>
U pair<T, U>::pop(T key)
{
	for (int i = 0; i < this->arr1.size(); i++)
	{
		if (this->arr1[i] == key) //i is our index
		{
			return this->arr2[i]; //the value we looking for
		}
	}
	return new U;
}

template<class T, class U>
size_t pair<T, U>::size()
{
	return this->size_pair;
}

template<class T, class U>
U pair<T, U>::operator[](T key)
{
	for (int i = 0; i < this->arr1.size(); i++)
	{
		if (this->arr1[i] == key) //i is our index
		{
			return this->arr2[i]; //the value we looking for
		}
	}
	U u = key;
	return u;
}

template<class T, class U>
void pair<T, U>::clean()
{
	this->arr1.clean();
	this->arr2.clean();
	this->size_pair = this->size_pair ^ this->size_pair;
}

void str::operator=(char* other)
{
	this->isClean = false;
	this->size_str = sizeof(other);
	this->string = (char*)malloc(sizeof(char) * this->size_str);
	this->string = other;
}

void str::operator+=(char* other)
{
	char* a = (char*)calloc(sizeof(this->string) + sizeof(other) + 2, sizeof(char));
	strcat(a, this->string);
	strcat(a, other);
	this->string = a;
}

char str::operator[](size_t z)
{
	return this->string[z];
}

void str::print()
{
	std::cout << this->string << std::endl;
}
