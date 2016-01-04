#ifndef SHARED_PTR
#define SHARED_PTR
#include <iostream>

using namespace std;

template<class T>class Shared_ptr
{
private:
	T * m_ptr;
	int * count_ptr;
public:
	explicit Shared_ptr(T * ptr = 0);
	Shared_ptr(const Shared_ptr&);
	Shared_ptr<T>& operator=(const Shared_ptr<T>&);
	T& operator*()const;
	~Shared_ptr();
};

template<class T>Shared_ptr<T>::Shared_ptr(T * ptr)
{
	if (ptr)
	{
		m_ptr = ptr;
		count_ptr = new int();
		(*count_ptr)++;
	}
	else
	{
		m_ptr = ptr;
		count_ptr = nullptr;
	}
}
template<class T>Shared_ptr<T>::Shared_ptr(const Shared_ptr& s)
{
	this->m_ptr = s.m_ptr;
	this->count_ptr = s.count_ptr;
	(*(this->count_ptr))++;
}
template<class T>Shared_ptr<T>::~Shared_ptr()
{
	if (*(this->count_ptr) == 1)
	{
		cout << "object deleted \n";
		delete this->m_ptr;
		delete this->count_ptr;
	}
	else
		(*(this->count_ptr))--;
}
template<class T>T& Shared_ptr<T>::operator*()const
{
	return *m_ptr;
}
template<class T> Shared_ptr<T>& Shared_ptr<T>::operator=(const Shared_ptr<T>& source)
{
	if (this == &source)
		return *this;
	if (*(this->count_ptr) == 1)
	{
		cout << *(this->m_ptr) << " object deleted\n";
		delete this->m_ptr;
		delete this->count_ptr;
	}
	else
		(*(this->count_ptr))--;

	this->m_ptr = source.m_ptr;
	this->count_ptr = source.count_ptr;
	(*(this->count_ptr))++;

	return *this;
}
#endif
