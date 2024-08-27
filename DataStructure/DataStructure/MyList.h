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


	// _targetIter �� ����Ű�°��� _Data �� �����Ű��, ���� ������ �����͸� ����Ű�� iterator �� ��ȯ���ش�.
	iterator insert(iterator _targetIter, const T& _Data);

	// _targetIter �� ����Ű�� �����͸� �����ϰ�, ������ ������ ����Ű�� iterator �� ��ȯ
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
			// Owner(List) �� �����Ǿ����� ������, �������� iterator �� �ƴϴ�.
			// Owner �� �����Ǿ� �־, m_TargetNode �� nullptr �̸� End Iterator �̱� ������
			// �������� ������ ����Ű�� ������ iterator ���� * �� ���ٱ���� ���� ����
			assert(owner && targetNode);
			return targetNode->Data;
		}

		// 1. ++, -- ��ȯŸ�� ����
		// 2. ++, -- ���������� ����
		iterator& operator ++()
		{
			// enditerator ���� ++ �ϴ� ���
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
			assert(owner->_head != targetNode); // iterator �� begin �̴�.

			if (nullptr == targetNode)
			{
				// ���� iterator �� end �����ε� -- �Լ��� ȣ��� ���
				// ������ ��带 ����Ű�� �Ѵ�.
				targetNode = owner->_tail;
			}
			else
			{
				// ���� ����Ű�� �ִ� ����� ���� ��带 ����Ű�� �Ѵ�.
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


// ��ȯŸ���� �̳�Ŭ������ ��� �տ� typename �� �ٿ��־�� �Ѵ�.
template<typename T>
typename MyList<T>::iterator MyList<T>::insert(iterator _targetIter, const T& _Data)
{
	// iterator �� �ش� ����Ʈ�� ������ �����͸� ����Ű�� �������� Ȯ��
	assert(_targetIter.owner == this);

	//enditerator�� insert�Ҽ� ����
	if (_targetIter.targetNode == nullptr)
		assert(nullptr);


	Node<T>* newNode = new Node<T>();
	newNode->Data = _Data;

	// insert ��ġ�� �� ó���̶��, push_front �� ó���Ѵ�.
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
	// iterator �� �ش� ����Ʈ�� ������ �����͸� ����Ű�� �������� Ȯ��
	assert(_targetIter.owner == this);


	// _targetIter �� ����Ű�� �ִ� ���(������ ���)		
	if (_targetIter.targetNode == _head)
	{
		// ���ܻ�Ȳ(������ ��尡 Head �� ���)
		// �ι�° ��带 ���ο� ���� ����
		_head = _targetIter.targetNode->_next;

		if (_head == nullptr)
		{
			// ����Ʈ�ȿ� �����Ͱ� 1�����ٸ�,(������ ��尡 ó������ ������ ��忴��)
			_tail = nullptr;
		}
		else
		{
			// ���Ӱ� ������ ������� ������ nullptr �� �ٲ۴�(������ ��带 ����Ű�� �ֱ� ������)
			_head->_prev = nullptr;
		}
	}
	else if (_targetIter.targetNode == _tail)
	{
		// ������ ����� ������ ���ο� Tail �� ����
		_tail = _targetIter.targetNode->_prev;

		// ���� ������ Tail ����� Next �� null �� �ٲ�
		_tail->_next = nullptr;
	}

	// ������ ��尡 Head �� �ƴϰ� Tail �� �ƴϴ�(�߰��̴�)
	else
	{
		// ������ ��� ��������� Next �� ������ ��� Next �� ��ü
		_targetIter.targetNode->_prev->_next = _targetIter.targetNode->_next;

		// ������ ��� ���� ����� Prev �� ������ ��� Prev �� ��ü
		_targetIter.targetNode->_next->_prev = _targetIter.targetNode->_prev;
	}

	// ������ ����� ������ ����Ű�� iterator �� �����.
	iterator nextiter(this, _targetIter.targetNode->_next);

	// _targetIter �� ����Ű�� �ִ� ��带 delete(�����Ҵ� ����)
	delete _targetIter.targetNode;

	// ������ ī��Ʈ ����
	--_size;

	return nextiter;
}
// �׽�Ʈ �Լ���
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
	myList.insert(it, 2); // 3 �տ� 2 ����

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
	++it; // ����Ű�� ��ġ�� 2
	myList.erase(it); // 2�� ����

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