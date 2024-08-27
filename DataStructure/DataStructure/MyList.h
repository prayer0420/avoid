#pragma once

#include <assert.h>

template<typename T>
struct Node
{
	T		 Data;
	Node<T>* _next;
	Node<T>* _prev;

	Node()
		: Data()
		, _next(nullptr)
		, _prev(nullptr)
	{}

	Node(const T& _Data, Node<T>* _Next, Node<T>* _Prev)
		: Data(_Data)
		, _next(_Next)
		, _prev(_Prev)
	{}
};

template<typename T>
class MyList
{
private:
	Node<T>* _head;
	Node<T>* _tail;
	int		 _size;

public:
	void push_back(const T& _Data);
	void push_front(const T& _Data);
	int size() { return _size; }

	class iterator;

	iterator begin() { return iterator(this, _head); }
	iterator end() { return iterator(this, nullptr); }


	// _targetIter 가 가리키는곳에 _Data 를 저장시키고, 새로 저장한 데이터를 가리키는 iterator 를 반환해준다.
	iterator insert(iterator _targetIter, const T& _Data);

	// _targetIter 가 가리키는 데이터를 삭제하고, 삭제한 다음을 가리키는 iterator 를 반환
	iterator erase(iterator _targetIter);


public:
	MyList()
		: _head(nullptr)
		, _tail(nullptr)
		, _size(0)
	{}

	~MyList()
	{
		Node<T>* pNode = _head;

		while (pNode)
		{
			Node<T>* pNext = pNode->_next;
			delete pNode;
			pNode = pNext;
		}
	}

public:
	class iterator
	{
	private:
		MyList<T>* owner;
		Node<T>* targetNode;

	public:
		T& operator *()
		{
			// Owner(List) 가 설정되어있지 않으면, 정상적인 iterator 가 아니다.
			// Owner 가 설정되어 있어도, m_TargetNode 가 nullptr 이면 End Iterator 이기 때문에
			// 마지막의 다음을 가리키는 상태의 iterator 에게 * 로 접근기능을 쓰면 에러
			assert(owner && targetNode);
			return targetNode->Data;
		}

		// 1. ++, -- 반환타입 문제
		// 2. ++, -- 후위연산자 문제
		iterator& operator ++()
		{
			// enditerator 에서 ++ 하는 경우
			assert(owner && targetNode);
			targetNode = targetNode->_next;

			return *this;
		}

		iterator operator++(int)
		{
			iterator copyiter = *this;

			++(*this);

			return copyiter;
		}

		iterator& operator --()
		{
			assert(owner);
			assert(owner->_head != targetNode); // iterator 가 begin 이다.

			if (nullptr == targetNode)
			{
				// 현재 iterator 가 end 상태인데 -- 함수가 호출된 경우
				// 마지막 노드를 가리키게 한다.
				targetNode = owner->_tail;
			}
			else
			{
				// 현재 가리키고 있는 노드의 이전 노드를 가리키게 한다.
				targetNode = targetNode->_prev;
			}

			return *this;
		}

		iterator operator --(int)
		{
			iterator copyiter = *this;

			++(*this);

			return copyiter;
		}

		bool operator == (const iterator& _otheriter)
		{
			if (owner == _otheriter.owner && targetNode == _otheriter.targetNode)
				return true;
			else
				return false;
		}

		bool operator != (const iterator& _otheriter)
		{
			return !((*this) == _otheriter);
		}

	public:
		iterator()
			: owner(nullptr)
			, targetNode(nullptr)
		{}

		iterator(MyList<T>* _Owner, Node<T>* _targetNode)
			: owner(_Owner)
			, targetNode(_targetNode)
		{}

		~iterator()
		{}

		friend class MyList<T>;
	};
};

template<typename T>
void MyList<T>::push_back(const T& _Data)
{
	Node<T>* pNewNode = new Node<T>(_Data, nullptr, nullptr);

	if (0 == _size) //nullptr == m_pHead)
	{
		_head = pNewNode;
		_tail = pNewNode;
	}
	else
	{
		_tail->_next = pNewNode;
		pNewNode->_prev = _tail;
		_tail = pNewNode;
	}

	++_size;
}

template<typename T>
inline void MyList<T>::push_front(const T& _Data)
{
	Node<T>* pNewNode = new Node<T>(_Data, _head, nullptr);

	if (nullptr != _head)
	{
		_head->_prev = pNewNode;
	}
	else
	{
		_tail = pNewNode;
	}

	_head = pNewNode;
	++_size;
}


// 반환타입이 이너클래스인 경우 앞에 typename 을 붙여주어야 한다.
template<typename T>
typename MyList<T>::iterator MyList<T>::insert(iterator _targetIter, const T& _Data)
{
	// iterator 가 해당 리스트가 소유한 데이터를 가리키는 상태인지 확인
	assert(_targetIter.owner == this);

	//enditerator에 insert할수 없음
	if (_targetIter.targetNode == nullptr)
		assert(nullptr);


	Node<T>* newNode = new Node<T>();
	newNode->Data = _Data;

	// insert 위치가 맨 처음이라면, push_front 로 처리한다.
	if (_targetIter.targetNode == _head)
	{
		_targetIter.targetNode->_prev = newNode;
		newNode->_next = _targetIter.targetNode;
		_head = newNode;
	}

	else
	{
		newNode->_prev = _targetIter.targetNode->_prev;
		newNode->_next = _targetIter.targetNode;

		_targetIter.targetNode->_prev->_next = newNode;
		_targetIter.targetNode->_prev = newNode;
	}

	_size++;

	return iterator(this, newNode);
	
}

template<typename T>
typename MyList<T>::iterator MyList<T>::erase(iterator _targetIter)
{
	// iterator 가 해당 리스트가 소유한 데이터를 가리키는 상태인지 확인
	assert(_targetIter.owner == this);


	// _targetIter 가 가리키고 있는 노드(삭제할 노드)		
	if (_targetIter.targetNode == _head)
	{
		// 예외상황(삭제할 노드가 Head 인 경우)
		// 두번째 노드를 새로운 헤드로 지정
		_head = _targetIter.targetNode->_next;

		if (_head == nullptr)
		{
			// 리스트안에 데이터가 1개였다면,(삭제할 노드가 처음이자 마지막 노드였다)
			_tail = nullptr;
		}
		else
		{
			// 새롭게 지정된 헤드노드의 이전을 nullptr 로 바꾼다(삭제될 노드를 가리키고 있기 때문에)
			_head->_prev = nullptr;
		}
	}
	else if (_targetIter.targetNode == _tail)
	{
		// 삭제할 노드의 이전을 새로운 Tail 로 지정
		_tail = _targetIter.targetNode->_prev;

		// 새로 지정된 Tail 노드의 Next 를 null 로 바꿈
		_tail->_next = nullptr;
	}

	// 삭제할 노드가 Head 도 아니고 Tail 도 아니다(중간이다)
	else
	{
		// 삭제할 노드 이전노드의 Next 를 삭제할 노드 Next 로 교체
		_targetIter.targetNode->_prev->_next = _targetIter.targetNode->_next;

		// 삭제할 노드 다음 노드의 Prev 를 삭제할 노드 Prev 로 교체
		_targetIter.targetNode->_next->_prev = _targetIter.targetNode->_prev;
	}

	// 삭제된 노드의 다음을 가리키는 iterator 를 만든다.
	iterator nextiter(this, _targetIter.targetNode->_next);

	// _targetIter 가 가리키고 있는 노드를 delete(동적할당 해제)
	delete _targetIter.targetNode;

	// 데이터 카운트 감소
	--_size;

	return nextiter;
}
// 테스트 함수들
void test_push_back() {
	MyList<int> myList;
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);

	assert(myList.size() == 3);
	MyList<int>::iterator it = myList.begin();
	assert(*it == 1);
	++it;
	assert(*it == 2);
	++it;
	assert(*it == 3);
	std::cout << "test_push_back passed!" << std::endl;
}

void test_push_front() {
	MyList<int> myList;
	myList.push_front(1);
	myList.push_front(2);
	myList.push_front(3);

	assert(myList.size() == 3);
	MyList<int>::iterator it = myList.begin();
	assert(*it == 3);
	++it;
	assert(*it == 2);
	++it;
	assert(*it == 1);
	std::cout << "test_push_front passed!" << std::endl;
}

void test_insert() {
	MyList<int> myList;
	myList.push_back(1);
	myList.push_back(3);

	MyList<int>::iterator it = myList.begin();
	++it;
	myList.insert(it, 2); // 3 앞에 2 삽입

	assert(myList.size() == 3);
	it = myList.begin();
	assert(*it == 1);
	++it;
	assert(*it == 2);
	++it;
	assert(*it == 3);
	std::cout << "test_insert passed!" << std::endl;
}

void test_erase() {
	MyList<int> myList;
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);

	MyList<int>::iterator it = myList.begin();
	++it; // 가리키는 위치가 2
	myList.erase(it); // 2를 삭제

	assert(myList.size() == 2);
	it = myList.begin();
	assert(*it == 1);
	++it;
	assert(*it == 3);
	std::cout << "test_erase passed!" << std::endl;
}

void test_iterators() {
	MyList<int> myList;
	myList.push_back(1);
	myList.push_back(2);
	myList.push_back(3);

	MyList<int>::iterator it = myList.begin();
	assert(*it == 1);
	++it;
	assert(*it == 2);
	++it;
	assert(*it == 3);
	++it;
	assert(it == myList.end());
	std::cout << "test_iterators passed!" << std::endl;
}