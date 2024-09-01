#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

namespace MyUM
{
    // 두 개의 관련된 데이터를 하나의 쌍으로 묶기 위해 사용
    template <typename T1, typename T2>
    struct MyPair
    {
        T1 first;
        T2 second;

        MyPair()
            : first(T1()), second(T2())
        {}

        MyPair(const T1& a, const T2& b)
            : first(a), second(b)
        {}
    };

    // makePair 함수
    template <typename T1, typename T2>
    MyPair<T1, T2> makePair(T1 f, T2 s)
    {
        return MyPair<T1, T2>(f, s);
    }


    template<typename KeyType, typename ValueType>
    struct Node
    {
        MyPair<KeyType, ValueType> data; // 키-값 쌍을 저장

        Node* next;  // 해시 테이블의 체이닝에 사용되는 포인터

        Node(const MyPair<KeyType, ValueType>& _myPair)
            : data(_myPair), next(nullptr)
        {}
    };

    const int TABLE_SIZE = 10;

    template<typename KeyType, typename ValueType>
    class MyUnorderedMap
    {
    private:
        vector<Node<KeyType, ValueType>*> table;

        // 해시 함수: 키의 해시 값을 계산하여 hash index반환
        int hashFunction(const KeyType& key)
        {
            return hash<KeyType>{}(key) % TABLE_SIZE;
        }

    public:

        //테이블 크기만큼 nullptr로 초기화된 벡터를 생성
        MyUnorderedMap()
            : table(TABLE_SIZE, nullptr)
        {}

        ~MyUnorderedMap()
        {
            for (int i = 0; i < TABLE_SIZE; ++i)
            {
                Node<KeyType, ValueType>* current = table[i];
                Node<KeyType, ValueType>* toDelete = current;
                while (current != nullptr)
                {
                    current = current->next;
                    delete toDelete;
                    toDelete = current;
                }
            }
        }

        // 키가 없으면 기본값으로 새로 추가하여 반환
        ValueType& operator[](const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType, ValueType>* current = table[hashIndex];

            // 리스트를 순회하면서 키를 찾기
            while (current != nullptr)
            {
                if (current->data.first == key)
                {
                    return current->data.second;  // 키를 찾으면 값을 참조로 반환
                }
                current = current->next;
            }

            // 키가 없으면 새로 추가하고
            //ValueType()은 해당타입에 맞게 초기화(기본값)하는 것
            insert(makePair(key, ValueType()));
            //참조로 반환
            current = table[hashIndex];
            return current->data.second;
        }

        // insert 함수: 주어진 키-값 쌍을 해시 테이블에 삽입합니다.
        // 이미 존재하는 키라면 값을 업데이트합니다.
        void insert(const MyPair<KeyType, ValueType>& _myPair)
        {
            int hashIndex = hashFunction(_myPair.first);  // 키의 해시 값을 계산하여 해시 인덱스를 얻음

            Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(_myPair);  // 새로운 노드를 생성

            // 해당 인덱스에 아직 노드가 없다면, 새 노드를 첫 번째 노드로 설정
            if (!table[hashIndex])
            {
                table[hashIndex] = newNode;
            }
            // 해당 인덱스에 이미 노드가 있는 경우
            else
            {
                //현재를 가리키고 있는 노드와, 이전 노드를 생성
                Node<KeyType, ValueType>* current = table[hashIndex];
                Node<KeyType, ValueType>* prev = nullptr;

                // 리스트를 순회하면서 키가 이미 존재하는지 확인
                while (current != nullptr)
                {
                    // 똑같은 키가 이미 존재하면 값을 업데이트
                    if (current->data.first == _myPair.first)
                    {
                        current->data.second = _myPair.second;
                        delete newNode;  // 새로 생성한 노드는 필요 없으므로 삭제
                        return;
                    }
                    //리스트의 맨 끝으로 이동
                    prev = current;
                    current = current->next;
                }
                // 키가 존재하지 않는다면 (해시충돌) 리스트의 끝에 새 노드를 추가
                prev->next = newNode;
            }
        }

        void erase(const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType, ValueType>* current = table[hashIndex];
            Node<KeyType, ValueType>* prev = nullptr;

            // 리스트를 순회하면서 삭제할 노드를 찾습니다.
            while (current != nullptr)
            {
                if (current->data.first == key)
                {
                    if (prev == nullptr)
                    {
                        // 첫 번째 노드를 삭제하는 경우
                        table[hashIndex] = current->next;
                    }
                    else
                    {
                        // 중간 또는 끝 노드를 삭제하는 경우
                        prev->next = current->next;
                    }
                    delete current;
                    return;
                }
                prev = current;
                current = current->next;
            }
        }

        ValueType& find(const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType, ValueType>* current = table[hashIndex];

            // 리스트를 순회하면서 키를 찾기
            while (current != nullptr)
            {
                if (current->data.first == key)
                {
                    return current->data.second;
                }
                current = current->next;
            }
            // 키가 없으면 새로 추가하고
            //ValueType()은 해당타입에 맞게 초기화(기본값)하는 것
            insert(makePair(key, ValueType()));
            //참조로 반환
            current = table[hashIndex];
            return current->data.second;
        }
    };
}