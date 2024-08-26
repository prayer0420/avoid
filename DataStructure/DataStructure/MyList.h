#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

template<typename T>
struct Node
{
	T _value;
	Node<T>* _next;
	Node<T>* _prev;

public:
	Node()
		:_value(0)
		, _next(nullptr)
		, _prev(nullptr)
	{}

	Node(T value)
		:_value(value)
		, _next(nullptr)
		, _prev(nullptr)
	{}

	Node(T value, Node<T>* next, Node<T>* prev)
		:_value(value)
		, _next(next)
		, _prev(prev)
	{}

};

template<typename T>
class MyList
{
private:
	Node<T>* _head = nullptr;
	Node<T>* _tail = nullptr;
	int _size = 0;
public:

	MyList() {}
	~MyList() {}

	class iterator;
	iterator begin() { return iterator(this, _head); }
	iterator end() { return iterator(this, nullptr); }

	//_targetIter �� ����Ű�°� �տ� _Data �� �����Ű��, ���� ������ �����͸� ����Ű�� iterator �� ��ȯ
	iterator insert(iterator _targetIter, const T& Data);

	//_targetIter �� ����Ű�� �����͸� �����ϰ�, ������ ������ ����Ű�� iterator �� ��ȯ
	iterator erase(iterator _targetIter);

	class iterator
	{
	private:
		MyList<T>* Owner;
		Node<T>* TargetNode;
	public:
		friend class MyList<T>;

		iterator()
			:Owner(nullptr)
			, TargetNode(nullptr)
		{}

		iterator(MyList<T>* _Owner, Node<T>* _TargetNode)
			:Owner(_Owner)
			, TargetNode(_TargetNode)
		{}

		~iterator() {}

		T& operator*()
		{
			// Owner(List) �� �����Ǿ����� ������, �������� iterator �� �ƴϴ�.
			// Owner �� �����Ǿ� �־, m_TargetNode �� nullptr �̸� End Iterator �̱� ������
			// �������� ������ ����Ű�� ������ iterator ���� * �� ���ٱ���� ���� ����
			assert(Owner && TargetNode);
			return TargetNode->_value;
		}

		//���� ++
		iterator& operator ++()
		{
			//enditerator�� ��� ����
			assert(Owner && TargetNode);
			TargetNode = TargetNode->_next;
			return *this;
		}

		//���� ++
		iterator operator ++ (int)
		{
			assert(Owner && TargetNode);
			iterator tempit = *this;
			++(*this);
			return tempit;
		}

		//����--
		iterator& operator --()
		{
			assert(Owner);

			//targetnode�� begin�� ��� ����(begin���� --�� ���� ����)
			assert(Owner->_head != TargetNode);

			if (nullptr == TargetNode)
			{
				//���� iterator�� end�����ε� --�� ȣ��Ȱ��
				TargetNode = Owner->_tail;
			}
			else
				TargetNode = TargetNode->_prev;
			return *this;
		}

		//����--
		iterator operator --(int)
		{
			assert(Owner && TargetNode);
			iterator tempIt = *this;
			--(*this);
			return tempIt;
		}

		bool operator == (const iterator& otherIterator)
		{
			if (Owner == otherIterator.Owner && TargetNode == otherIterator.TargetNode)
				return true;
			return false;
		}

		bool operator != (const iterator& otherIterator)
		{
			return !(*this == otherIterator);
		}

	};


	void push_back(T value)
	{
		//Node* newNode = new Node(value);
		Node<T>* newNode = new Node<T>(value, nullptr, nullptr);

		//ó�� �̶��
		if (_tail == nullptr)
		{
			_head = newNode;
		}

		else
		{
			newNode->_prev = _tail;
			_tail->_next = newNode;
		}
		_tail = newNode;
		_size++;
	}

	void push_front(T value)
	{
		Node* newNode = new Node(value, nullptr, nullptr);
		if (_head == nullptr)
		{
			_tail = newNode;
		}
		else
		{
			_head->_prev = newNode;
			newNode->_next = _head;
		}
		_head = newNode;
		_size++;
	}

	//node�տ� �߰�
	void Insert(Node<T>* node, int value)
	{
		if (node == nullptr)
		{
			return;
		}

		Node<T>* newNode = new Node<T>(value, nullptr, nullptr);
		node->_prev->_next = newNode;
		node->_prev = newNode;

		newNode->_next = node;
		newNode->_prev = node->_prev;
		_size++;

	}

	void Delete(Node<T>* node)
	{
		node = Search(node);

		if (node == nullptr)
			return;

		node->_next->_prev = node->_prev;
		node->_prev->_next = node->_next;

		delete node;
	}

	Node<T>* Search(Node<T>* node)
	{
		Node<T>* SearchNode = _head;
		for (int i = 0; i < _size; i++)
		{
			if (SearchNode == node)
			{
				return SearchNode;
			}
			SearchNode = SearchNode->_next;
		}
	}

	void Release()
	{
		Node<T>* deleteNode = _head;
		while (deleteNode)
		{
			Node* node = deleteNode->_next;
			delete deleteNode;
			deleteNode = node;
		}
	}

	Node<T>* GetNode(int idx)
	{
		if (idx > _size)
			return nullptr;


		Node<T>* tempNode = _head;

		for (int i = 0; i < idx - 1; i++)
		{
			if (tempNode == nullptr)
				return nullptr;

			tempNode = tempNode->_next;
		}

		return tempNode;

	}


};

template<typename T>
typename MyList<T>::iterator MyList<T>::insert(iterator _targetIter, const T& Data)
{
	//���� ����Ʈ�� Ÿ�� ���ͷ����Ͱ� �����ִ���
	assert(this == _targetIter.Owner);

	Node<T>* newNode = new Node<T>();
	newNode->_value = Data;

	//ister��ġ�� ��ó���̶��, head�տ� ��� ����
	if (_head == _targetIter.TargetNode)
	{
		_head->_prev = newNode;
		newNode->_next = _head;

		_head = newNode;
	}
	_size++;
	return iterator(this, newNode);
}

template<typename T>
typename MyList<T>::iterator MyList<T>::erase(iterator _targetIter)
{
	//���� ����Ʈ�� Ÿ�� ���ͷ����Ͱ� �����ִ���
	assert(_targetIter.Owner == this);

	//������ ��尡 ���������
	if (_targetIter.TargetNode == _head)
	{
		_head = _targetIter.TargetNode->_next;
		//����Ʈ�� ��尡 �� 1������ ���
		if (_head == nullptr)
		{
			_tail = nullptr;
		}
		_head->_prev = nullptr;
	}

	//������ ��尡 ���ϳ������
	else if (_targetIter.TargetNode == _tail)
	{
		_tail = _targetIter.TargetNode->_prev;

		_tail->_next = nullptr;
	}

	//������ ��尡 �߰�����
	else
	{
		_targetIter.TargetNode->_prev->_next = _targetIter.TargetNode->_next;
		_targetIter.TargetNode->_next->_prev = _targetIter.TargetNode->_prev;
	}

	iterator nextIt(this, _targetIter.TargetNode->_next);
	delete _targetIter.TargetNode;
	_size--;

	return nextIt;
}
