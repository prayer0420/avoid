#pragma once
#include <iostream>
#include<assert.h>
using namespace std;

template<typename T>
class MyVector
{
private:
    T* _arr; //���� �޸𸮸� ����Ű�� ������
    int _size;//���� ����
    int _capacity;//�ִ� ����

public:
    //�⺻������
    MyVector()
        :_arr(nullptr)
        , _size(0)
        , _capacity(2)
    {
        //���� intŸ�� 2ĭ¥�� �迭 ������ �� �迭�� ����Ű����
        _arr = new int[_capacity];
    }

    //���ڹ޴� �⺻������
    MyVector(int* arr, int size, int capacity)
        :_arr(arr), _size(size), _capacity(_capacity)
    {
        //���� ����
        _arr = new int[_capacity];
        for (int i = 0; i < size; i++)
        {
            _arr[i] = arr[i];
        }
    }

    ~MyVector()
    {
        delete[] _arr;
    }

    //÷�ڿ���, �ε��� ����
    int operator[](int idx)
    {
        assert(idx >= 0 && idx < _size);
        return _arr[idx];
    }

    //Add
    void Add(T value)
    {
        //���Ҵ�
        if (_size >= _capacity)
        {
            Reserve(_capacity * 2);
        }

        //size�� �ش��ϴ� ĭ�� value�Է�
        _arr[_size++] = value;

    }

    int Size()
    {
        return _size;
    }

    void Reserve(int capacity)
    {
        assert(capacity > _capacity);

        T* TempArr = new T[capacity];
        for (int i = 0; i < _size; i++)
        {
            TempArr[i] = _arr[i];
        }
        //���� �Ҵ��ߴ� _arr�� ����Ű�� �޸�(�迭)�� ���� �����Ƿ� ����
        delete[] _arr;
        //MyVector�� ���� �Ҵ��� TempArr�� ����Ű�� �޸�(�迭)�� �Ȱ��� ����Ų��
        _arr = TempArr;
        _capacity = capacity;
    }
    void AddRange(const MyVector<T>* otherVector)
    {
        Reserve(_size + otherVector->_size);
        for (int i = 0; i < otherVector->_size; i++)
        {
            _arr[_size++] = otherVector->_arr[i];
        }
    }

    //Clear
    void Clear()
    {
        delete[] _arr;
        _size = 0;
        _capacity = 0;
        _arr = nullptr;
    }

    //�迭�� value���� �ִ��� Ȯ���ϰ� ������ ����, ������ 0�� ��ȯ
    bool FindValue(T value)
    {
        for (int i = 0; i < _size; i++)
        {
            if (_arr[i] == value)
                return true;
        }
        return false;
    }
    //�ε����� ã��
    T FindIdx(int idx)
    {
        assert(idx >= 0 && idx < _size);
        if (_arr[idx] != 0)
            return _arr[idx];

        return 0;
    }

    //Ư�� ���� ����
    void Remove(T value)
    {
        for (int i = 0; i < _size; i++)
        {
            if (_arr[i] == value)
            {
                for (int j = i; j < _size - 1; j++)
                {
                    _arr[j] = _arr[j + 1];
                }
                _size--;
                i--;
            }
        }

    }
    //Ư�� �ε����� ���� ����
    void RemoveAt(int idx)
    {
        assert(idx >= 0 && idx < _size);
        for (int i = idx; i < _size - 1; i++)
        {
            _arr[i] = _arr[i + 1];
        }
        _size--;
    }
};