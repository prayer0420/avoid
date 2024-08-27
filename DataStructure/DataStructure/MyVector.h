//#pragma once
//#include <assert.h>
//
//template<typename T>
//class MyVector
//{
//public:
//	T* pData;
//	int size;
//	int capacity;
//
//public:
//
//	class iterator;
//	iterator begin();
//	iterator end();
//	iterator insert(const iterator& pos, const T& data);
//	iterator erase(const iterator& pos);
//
//
//	class iterator
//	{
//	private:
//		MyVector* pArr;		//iterator�� ����ų �����͸� �����ϴ� �����迭 �ּ�
//		T* it_pData;	//�����͵��� �����ּ�
//		int			idx;		//����Ű�� �������� �ε���
//	public:
//		friend class Myvector;
//
//		iterator()
//			:pArr(nullptr)
//			, it_pData(nullptr)
//			, idx(-1)
//		{
//		}
//
//		iterator(MyVector* _pArr, T* _it_pData, int _idx)
//			:pArr(_pArr)
//			, it_pData(_it_pData)
//			, idx(_idx)
//		{}
//
//		T& operator *()
//		{
//			if (pArr->pData != it_pData || -1 == idx)
//				assert(nullptr);
//
//			return it_pData[idx];
//		}
//
//		iterator& operator++()
//		{
//			if (pArr->pData != pArr->pData || -1 == idx)
//				assert(nullptr);
//
//			//���������� ++ �ϸ� enditerator��
//			if (idx == pArr->size - 1)
//				idx = -1;
//
//			else
//				++idx;
//
//			return *this;
//		}
//		iterator operator++(int)
//		{
//			iterator tempIt = *this;
//			++(*this);
//			return tempIt;
//		}
//
//		iterator& operator--()
//		{
//			if (pArr->it_pData != it_pData || 0 == idx)
//				assert(nullptr);
//
//			//enditerator���� --�ϸ� ���� ��������° ����Ű����
//			if (-1 == idx)
//			{
//				idx = pArr->size() - 1;
//			}
//			else
//				--idx;
//
//			return *this;
//		}
//		iterator operator--(int)
//		{
//			iterator tempIt = *this;
//			--(*this);
//			return tempIt;
//		}
//
//		bool operator==(const iterator& other)
//		{
//			if (pArr == other.pArr && idx == other.idx)
//				return true;
//			return false;
//		}
//
//		bool operator!=(const iterator& other)
//		{
//			return !((*this) == other);
//		}
//
//		friend class MyVector;
//
//	};
//
//	//�⺻ ������
//	MyVector()
//		:pData(nullptr)
//		, size(0)
//		, capacity(2)
//	{
//		pData = new T[capacity];
//	}
//
//	//���ڹ޴� �⺻ ������
//	MyVector<T>(T* _pData, int _size, int _capacity)
//		:pData(new T[_capacity])
//		, size(size)
//		, capacity(_capacity)
//	{
//		for (int i = 0; i < _size; i++)
//		{
//			pData[i] = _pData[i];
//		}
//	}
//
//	//���� ������
//	MyVector(const MyVector& other)
//		:pData(new T[other.capacity])
//		, size(other.size)
//		, capacity(other.capacity)
//	{
//		for (int i = 0; i < other.size; i++)
//		{
//			pData[i] = other.pData[i];
//		}
//	}
//
//	//���� ���� ������
//	MyVector& operator =(const MyVector& other)
//	{
//		if (&other != this)
//		{
//			delete[] pData;
//			size = other.size;
//			capacity = other.capacity;
//			pData = new int[other.capacity];
//			for (int i = 0; i < other.size; i++)
//			{
//				pData[i] = other.pData[i];
//			}
//		}
//		return *this;
//	}
//	~MyVector()
//	{
//		delete[] pData;
//	}
//
//	int& operator[] (int idx)
//	{
//		assert(idx < size && idx >= 0);
//
//		return pData[idx];
//	}
//
//	void resize(int _capacity)
//	{
//		if (_capacity <= capacity)
//			assert(nullptr);
//
//		T* pNewData = new T[_capacity];
//		for (int i = 0; i < size; i++)
//		{
//			pNewData[i] = pData[i];
//		}
//
//		for (int i = size; i < _capacity; i++)
//		{
//			pNewData[i] = 0;
//		}
//
//		delete[] pData;
//
//		pData = pNewData;
//		capacity = _capacity;
//	}
//
//
//	void reserve(int _size)
//	{
//		if (_size <= capacity)
//			assert(nullptr);
//
//		T* pNewData = new T[_size];
//		for (int i = 0; i < size; i++)
//		{
//			pNewData[i] = pData[i];
//		}
//
//		delete[] pData;
//
//		pData = pNewData;
//
//		capacity = _size;
//	}
//
//	void push_back(T data)
//	{
//		if (size >= capacity)
//		{
//			reserve(capacity * 2);
//		}
//
//		pData[size++] = data;
//	}
//
//};
//
//template<typename T>
//inline typename MyVector<T>::iterator MyVector<T>::begin()
//{
//	if (size == 0)
//		return iterator(this, pData, -1);
//	else
//		return iterator(this, pData, 0);
//}
//
//template<typename T>
//inline typename MyVector<T>::iterator MyVector<T>::end()
//{
//	return iterator(this, pData, -1);
//}
//
//template<typename T>
//inline typename MyVector<T>::iterator MyVector<T>::insert(const iterator& pos, const T& data)
//{
//	if (this != pos.pArr || pos.idx == -1 || size <= pos.idx)
//	{
//		assert(nullptr);  // ��ȿ���� ���� ���ͷ����Ϳ� ���� ���α׷� ����
//	}
//
//	int index = pos.idx;
//
//	if (size >= capacity)
//	{
//		resize(capacity * 2);
//	}
//
//	//pos�ڸ� �տ� �������� ����Ȯ�� ����!
//	for (int i = size; i > index; i--)
//	{
//		pData[i] = pData[i - 1];
//	}
//
//	//index�ڸ��� �ֱ�
//	pData[index] = data;
//	size++;
//
//	return iterator(this, pData, index);
//}
//
//template<typename T>
//inline typename MyVector<T>::iterator MyVector<T>::erase(const iterator& pos)
//{
//	if (this != pos.pArr || end() == pos || size <= pos.idx)
//	{
//		assert(nullptr);  // ��ȿ���� ���� ���ͷ����Ϳ� ���� ���α׷� ����
//	}
//
//	int index = pos.idx;
//
//	//������ ���ܹ���
//	for (int i = index; i < size - 1; i++)
//	{
//		pData[i] = pData[i + 1];
//	}
//
//	size--;
//
//	return iterator(this, pData, index);
//}
//
//// �׽�Ʈ ���̽� �ۼ�
//void test_push_back()
//{
//	MyVector<int> vec;
//	vec.push_back(1);
//	vec.push_back(2);
//	vec.push_back(3);
//
//	assert(vec[0] == 1);
//	assert(vec[1] == 2);
//	assert(vec[2] == 3);
//	assert(vec.size == 3);
//}
//
//void test_insert()
//{
//	MyVector<int> vec;
//	vec.push_back(1);
//	vec.push_back(3);
//
//	MyVector<int>::iterator it = vec.begin();
//	++it; // ����Ű�� ��ġ�� 3�� ��ġ
//	vec.insert(it, 2); // 3 �տ� 2�� ����
//
//	assert(vec[0] == 1);
//	assert(vec[1] == 2);
//	assert(vec[2] == 3);
//	assert(vec.size == 3);
//}
//
//void test_erase()
//{
//	MyVector<int> vec;
//	vec.push_back(1);
//	vec.push_back(2);
//	vec.push_back(3);
//
//	MyVector<int>::iterator it = vec.begin();
//	++it; // ����Ű�� ��ġ�� 2�� ��ġ
//	vec.erase(it); // 2�� ����
//
//	assert(vec[0] == 1);
//	assert(vec[1] == 3);
//	assert(vec.size == 2);
//}
//
//void test_resize()
//{
//	MyVector<int> vec;
//	vec.push_back(1);
//	vec.push_back(2);
//
//	vec.resize(10);
//
//	assert(vec.size == 2);
//	assert(vec.capacity == 10);
//}
//
//void test_iterators()
//{
//	MyVector<int> vec;
//	vec.push_back(1);
//	vec.push_back(2);
//	vec.push_back(3);
//
//	MyVector<int>::iterator it = vec.begin();
//
//	assert(*it == 1);
//	++it;
//	assert(*it == 2);
//	++it;
//	assert(*it == 3);
//	++it;
//	assert(it == vec.end());
//}