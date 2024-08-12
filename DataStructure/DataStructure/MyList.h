#pragma once
#include <iostream>
#include<assert.h>
using namespace std;

template <typename T>
struct MyNode
{
    T _data; //��
    MyNode<T>* _next; //���� ���
    MyNode<T>* _prev; //���� ���

    MyNode()
        :_data(0)
        , _next(nullptr)
        , _prev(nullptr)
    {}

    MyNode(int data)
        :_data(data)
        , _next(nullptr)
        , _prev(nullptr)
    {}
};

template <typename T>
class MyList
{
private:
    int _size; //���� ����
    MyNode<T>* _head; //ù��° ���
    MyNode<T>* _tail; //�ι�° ���

public:
    MyList()
        :_size(0)
        , _head(nullptr)
        , _tail(nullptr)
    {}

    MyList(int size, MyNode<T>* head, MyNode<T>* tail)
        :_size(size)
        , _head(head)
        , _tail(tail)
    {}

    ~MyList()
    {
        MyNode<T>* deleteNode = _head;
        for (int i = 0; i < _size; i++)
        {
            MyNode* tempNode = deleteNode->_next;
            delete deleteNode;
            deleteNode = tempNode;
            if (deleteNode == nullptr)
                break;
        }
    }
    //�� �տ� �ֱ�
    void push_front(T data)
    {
        //�ϴ� data�� ������ MyNode ����
        MyNode<T>* newNode = new MyNode<T>(data);

        //������ ���� �����ٸ�
        if (_head == nullptr)
        {
            _tail = newNode;
        }
        //������ ���� 1���̻� �־�����
        else
        {
            newNode->_next = _head;
            _head->_prev = newNode;
        }

        //ù��° ��带 ���� �߰��� ���� ����
        _head = newNode;

        //���� ���� ����
        _size++;
    }

    //�� �ڿ� �ֱ�
    void push_back(T data)
    {
        MyNode<T>* newNode = new MyNode<T>(data);

        //������ ���� �����ٸ�
        if (_head == nullptr)
        {
            _head = newNode;
        }
        //������ ���� 1���̻� �־�����
        else
        {
            newNode->_prev = _tail;
            _tail->_next = newNode;
        }

        //ù��° ��带 ���� �߰��� ���� ����
        _tail = newNode;

        //���� ���� ����
        _size++;

    }

    //�ǵ� ����
    void pop_back()
    {
        if (_tail == _head)
        {
            delete _tail;
            _tail = nullptr;
            _head = nullptr;
        }
        else
        {
            _tail = _tail->_prev;
            delete _tail->_next;
            _tail->_next = nullptr;
        }
        _size--;

    }

    void pop_front()
    {
        if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
        }
        else
        {
            _head = _head->_next;
            delete _head->_prev;
            _head->_prev = nullptr;
        }
        _size--;

    }

    MyNode<T>* Find(T data)
    {
        MyNode<T>* tempNode = _head;
        for (int i = 0; i < _size; i++)
        {
            if (tempNode == nullptr)
                return nullptr;
            if (tempNode->_data == data)
                return tempNode;
            tempNode = tempNode->_next;
        }
        return nullptr;
    }

    //Ư�� �� �տ� Ư�� �� �ֱ�
    void insert(T findData, T data)
    {
        MyNode<T>* newNode = new MyNode<T>(data);
        MyNode<T>* findNode = Find(findData);

        newNode->_prev = findNode->_prev;

        if (findNode->_prev != nullptr)
            findNode->_prev->_next = newNode;

        newNode->_next = findNode;
        findNode->_prev = newNode;

        if (findNode == _head)
            _head = newNode;

        _size++;
    }

    //Ư�� �� ����
    void erase(T data)
    {
        MyNode<T>* findNode = Find(data);

        findNode->_prev->_next = findNode->_next;
        findNode->_next->_prev = findNode->_prev;
        delete findNode;
        _size--;
    }

    void AddRanage(const MyList<T>* other)
    {
        _tail->_next = other->_head;
        other->_head->_prev = _tail;
        _tail = other->_tail;
    }

};