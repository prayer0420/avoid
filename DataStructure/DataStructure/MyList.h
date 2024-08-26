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

	//_targetIter 가 가리키는곳 앞에 _Data 를 저장시키고, 새로 저장한 데이터를 가리키는 iterator 를 반환
	iterator insert(iterator _targetIter, const T& Data);

	//_targetIter 가 가리키는 데이터를 삭제하고, 삭제한 다음을 가리키는 iterator 를 반환
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
			// Owner(List) 가 설정되어있지 않으면, 정상적인 iterator 가 아니다.
			// Owner 가 설정되어 있어도, m_TargetNode 가 nullptr 이면 End Iterator 이기 때문에
			// 마지막의 다음을 가리키는 상태의 iterator 에게 * 로 접근기능을 쓰면 에러
			assert(Owner && TargetNode);
			return TargetNode->_value;
		}

		//전위 ++
		iterator& operator ++()
		{
			//enditerator의 경우 에러
			assert(Owner && TargetNode);
			TargetNode = TargetNode->_next;
			return *this;
		}

		//후위 ++
		iterator operator ++ (int)
		{
			assert(Owner && TargetNode);
			iterator tempit = *this;
			++(*this);
			return tempit;
		}

		//전위--
		iterator& operator --()
		{
			assert(Owner);

			//targetnode가 begin일 경우 에러(begin보다 --로 갈순 없음)
			assert(Owner->_head != TargetNode);

			if (nullptr == TargetNode)
			{
				//현재 iterator가 end상태인데 --가 호출된경우
				TargetNode = Owner->_tail;
			}
			else
				TargetNode = TargetNode->_prev;
			return *this;
		}

		//후위--
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

		//처음 이라면
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

	//node앞에 추가
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
	//현재 리스트에 타겟 이터레이터가 속해있는지
	assert(this == _targetIter.Owner);

	Node<T>* newNode = new Node<T>();
	newNode->_value = Data;

	//ister위치가 맨처음이라면, head앞에 노드 붙임
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
	//현재 리스트에 타겟 이터레이터가 속해있는지
	assert(_targetIter.Owner == this);

	//삭제할 노드가 헤드노드인지
	if (_targetIter.TargetNode == _head)
	{
		_head = _targetIter.TargetNode->_next;
		//리스트에 노드가 단 1개였던 경우
		if (_head == nullptr)
		{
			_tail = nullptr;
		}
		_head->_prev = nullptr;
	}

	//삭제할 노드가 테일노드인지
	else if (_targetIter.TargetNode == _tail)
	{
		_tail = _targetIter.TargetNode->_prev;

		_tail->_next = nullptr;
	}

	//삭제할 노드가 중간인지
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
