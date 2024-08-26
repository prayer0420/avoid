#pragma once
#include <iostream>
#include <assert.h>
using namespace std;


template<typename T>
class MyVector
{

private:
	T* _ptrArr;
	int _size;
	int _capacity;

public:

	class iterator;
	iterator begin();
	iterator end();
	iterator insert(iterator pos, const T& value);
	iterator erase(iterator pos);


	class iterator
	{
	private:
		MyVector* _pArr = nullptr;
		T* _ptr = nullptr;
		int _idx;

	public:
		iterator()
			:_pArr(nullptr)
			, _ptr(nullptr)
			, _idx(-1)
		{}

		iterator(MyVector* pArr, T* ptr, int idx)
			:_pArr(pArr)
			, _ptr(ptr)
			, _idx(idx)
		{}

		~iterator() {}

		//*����
		T& operator*()
		{
			if (_pArr->_ptrArr != _ptr || -1 == _idx)
				assert(nullptr);

			return _ptr[_idx];
		}

		//����++
		iterator& operator ++()
		{
			if (_pArr->_ptrArr != _ptr || -1 == _idx)
				assert(nullptr);
			//iterator�� ������ �����͸� ����Ű�� ��� enditerator��
			if (_idx == _pArr->size() - 1)
				_idx = -1;
			else
				++_idx;
			return *this;
		}

		//����++
		iterator operator ++(int)
		{
			iterator tempIt = *this;
			++(*this);
			return tempIt;
		}

		//����--
		iterator& operator --()
		{
			//���ͷ����Ͱ� ó���� ����Ų ���
			if (_pArr->_ptrArr != _ptr || _idx == 0)
				assert(nullptr);
			else
				_idx--;
			return *this;
		}

		//����--
		iterator operator --(int)
		{
			iterator tempIt = *this;
			--(*this);
			return tempIt;
		}

		//�� ==
		bool operator ==(const iterator other)
		{
			if (_ptr == other._ptr && _idx == other._idx)
				return true;
			return false;
		}

		//��!=
		bool operator !=(const iterator other)
		{
			return !(*this == other);
		}
		friend class MyVector;
	};

	//�⺻ ������
	MyVector()
		: _size(0)
		, _capacity(2)
		, _ptrArr(nullptr)
	{
		_ptrArr = new int[_capacity];
	}

	//���ڹ޴� �⺻ ������
	MyVector(T* ptrArr, int size, int capacity)
		:_ptrArr(new T[capacity])
		, _size(size)
		, _capacity(capacity)
	{
		for (int i = 0; i < _size; i++)
		{
			_ptrArr[i] = ptrArr[i];
		}
	}

	//���� ������
	MyVector(const MyVector* other)
		:_size(other->_size)
		, _capacity(other->_capacity)
		, _ptrArr(new T[other->_capacity])
	{
		//���� ����
		for (int i = 0; i < _size; i++)
		{
			_ptrArr[i] = other->_ptrArr[i];
		}
	}

	//���� ���� ������
	MyVector& operator =(const MyVector& other)
	{
		if (&other != this)
		{
			delete[] _ptrArr;
			_size = other._size;
			_capacity = other._capacity;
			_ptrArr = new T[_capacity];
			//���� ����
			for (int i = 0; i < other._size; i++)
			{
				_ptrArr[i] = other._ptrArr[i];
			}
		}
		return *this;
	}

	~MyVector()
	{
		delete[] _ptrArr;
	}

	T& operator [](int idx)
	{
		assert(idx >= 0 && idx < _size);
		assert(idx == -1);

		//end iterator�� ����ų ��

		return _ptrArr[idx];

	}

	void push_back(T value)
	{
		if (_size >= _capacity)
		{
			//���Ҵ�
			Reserve(_capacity * 2);
			//Resize(_capacity*2);
		}
		_ptrArr[_size++] = value;
	}

	void Reserve(int capacity)
	{
		if (capacity <= _capacity)
			assert(nullptr);

		T* newArrPtr = new T[capacity];
		for (int i = 0; i < _size; i++)
		{
			newArrPtr[i] = _ptrArr[i];
		}
		delete[] _ptrArr;
		_ptrArr = newArrPtr;
		_capacity = capacity;
	}

	void Resize(int capacity)
	{
		if (capacity <= _capacity)
			assert(nullptr);

		T* newArrPtr = new T[capacity];
		for (int i = 0; i < _size; i++)
		{
			newArrPtr[i] = _ptrArr[i];
		}

		for (int i = _size; i < capacity; i++)
		{
			newArrPtr[i] = 0;
		}

		delete[] _ptrArr;
		_ptrArr = newArrPtr;
		_capacity = capacity;
		_size = capacity;
	}

	int size()
	{
		return _size;
	}

	int capacity()
	{
		return _capacity;
	}

};

template<typename T>
inline typename MyVector<T>::iterator MyVector<T>::begin()
{
	if (_size == 0)
		return iterator(this, _ptrArr, -1); //�����Ͱ� ���°�� end���ͷ�����
	else
		return iterator(this, _ptrArr, 0);
}

template<typename T>
inline typename MyVector<T>::iterator MyVector<T>::end()
{
	return iterator(this, _ptrArr, -1);
}

template<typename T>
inline typename  MyVector<T>::iterator MyVector<T>::insert(iterator pos, const T& value)
{
	int index = pos._idx;

	if (_size >= _capacity)
	{
		Resize(_capacity * 2);
	}

	for (int i = index; i < _size; i++)
	{
		_ptrArr[i + 1] = _ptrArr[i];
	}
	_ptrArr[index] = value;
	_size++;
	return iterator(this, _ptrArr, index);
}

template<typename T>
inline typename MyVector<T>::iterator MyVector<T>::erase(iterator pos)
{
	int index = pos._idx;

	for (int i = index; i < _size - 1; i++)
	{
		_ptrArr[i] = _ptrArr[i + 1];
	}

	_size--;

	return iterator(this, _ptrArr, index);
}
