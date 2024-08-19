#pragma once
#include <iostream>
#include<assert.h>
using namespace std;

template<typename T>
class MyVector
{
private:
    T* _arr; //동적 메모리를 가리키는 포인터
    int _size;//현재 개수
    int _capacity;//최대 개수

public:
    //기본생성자
    MyVector()
        :_arr(nullptr)
        , _size(0)
        , _capacity(2)
    {
        //최초 int타입 2칸짜리 배열 생성후 이 배열을 가리키도록
        _arr = new int[_capacity];
    }

    //인자받는 기본생성자
    MyVector(int* arr, int size, int capacity)
        :_arr(arr), _size(size), _capacity(_capacity)
    {
        //깊은 복사
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

    //첨자연산, 인덱스 접근
    int operator[](int idx)
    {
        assert(idx >= 0 && idx < _size);
        return _arr[idx];
    }

    //Add
    void Add(T value)
    {
        //재할당
        if (_size >= _capacity)
        {
            Reserve(_capacity * 2);
        }

        //size에 해당하는 칸에 value입력
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
        //최초 할당했던 _arr이 가리키는 메모리(배열)는 쓸모 없으므로 해제
        delete[] _arr;
        //MyVector는 새로 할당한 TempArr가 가리키던 메모리(배열)를 똑같이 가리킨다
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

    //배열에 value값이 있는지 확인하고 있으면 값을, 없으면 0을 반환
    bool FindValue(T value)
    {
        for (int i = 0; i < _size; i++)
        {
            if (_arr[i] == value)
                return true;
        }
        return false;
    }
    //인덱스로 찾기
    T FindIdx(int idx)
    {
        assert(idx >= 0 && idx < _size);
        if (_arr[idx] != 0)
            return _arr[idx];

        return 0;
    }

    //특정 값을 제거
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
    //특정 인덱스의 값을 제거
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