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

		//*접근
		T& operator*()
		{
			if (_pArr->_ptrArr != _ptr || -1 == _idx)
				assert(nullptr);

			return _ptr[_idx];
		}

		//전위++
		iterator& operator ++()
		{
			if (_pArr->_ptrArr != _ptr || -1 == _idx)
				assert(nullptr);
			//iterator가 마지막 데이터를 가리키는 경우 enditerator로
			if (_idx == _pArr->size() - 1)
				_idx = -1;
			else
				++_idx;
			return *this;
		}

		//후위++
		iterator operator ++(int)
		{
			iterator tempIt = *this;
			++(*this);
			return tempIt;
		}

		//전위--
		iterator& operator --()
		{
			//이터레이터가 처음을 가리킨 경우
			if (_pArr->_ptrArr != _ptr || _idx == 0)
				assert(nullptr);
			else
				_idx--;
			return *this;
		}

		//후위--
		iterator operator --(int)
		{
			iterator tempIt = *this;
			--(*this);
			return tempIt;
		}

		//비교 ==
		bool operator ==(const iterator other)
		{
			if (_ptr == other._ptr && _idx == other._idx)
				return true;
			return false;
		}

		//비교!=
		bool operator !=(const iterator other)
		{
			return !(*this == other);
		}
		friend class MyVector;
	};

	//기본 생성자
	MyVector()
		: _size(0)
		, _capacity(2)
		, _ptrArr(nullptr)
	{
		_ptrArr = new int[_capacity];
	}

	//인자받는 기본 생성자
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

	//복사 생성자
	MyVector(const MyVector* other)
		:_size(other->_size)
		, _capacity(other->_capacity)
		, _ptrArr(new T[other->_capacity])
	{
		//깊은 복사
		for (int i = 0; i < _size; i++)
		{
			_ptrArr[i] = other->_ptrArr[i];
		}
	}

	//복사 대입 연산자
	MyVector& operator =(const MyVector& other)
	{
		if (&other != this)
		{
			delete[] _ptrArr;
			_size = other._size;
			_capacity = other._capacity;
			_ptrArr = new T[_capacity];
			//깊은 복사
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

		//end iterator를 가리킬 때

		return _ptrArr[idx];

	}

	void push_back(T value)
	{
		if (_size >= _capacity)
		{
			//재할당
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
		return iterator(this, _ptrArr, -1); //데이터가 없는경우 end이터레이터
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
