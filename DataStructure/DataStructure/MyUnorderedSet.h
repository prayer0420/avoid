#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

namespace MyUS
{
    // 해시 테이블의 크기
    const int TABLE_SIZE = 10;

    template<typename KeyType>
    struct Node
    {
        KeyType data;  // 요소를 저장
        Node* next;

        Node(const KeyType& d)
            : data(d)
            , next(nullptr)
        {}
    };

    template<typename KeyType>
    class MyUnorderedSet
    {
    private:
        vector<Node<KeyType>*> table;

        int hashFunction(const KeyType& key)
        {
            return hash<KeyType>{}(key) % TABLE_SIZE;
        }

    public:

        MyUnorderedSet()
            : table(TABLE_SIZE, nullptr)
        {}


        ~MyUnorderedSet()
        {
            // 노드를 순차적으로 삭제
            for (int i = 0; i < TABLE_SIZE; ++i)
            {
                Node<KeyType>* current = table[i];
                while (current != nullptr)
                {
                    Node<KeyType>* toDelete = current;
                    current = current->next;
                    delete toDelete;
                }
            }
        }

        // 이미 존재하는 요소라면 삽입하지 않음
        void insert(const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType>* newNode = new Node<KeyType>(key);

            // 해당 인덱스에 아직 노드가 없다면, 새 노드를 첫 번째 노드로 설정
            if (!table[hashIndex])
            {
                table[hashIndex] = newNode;
            }
            else
            {
                // 해당 인덱스에 이미 노드가 있는 경우 
                Node<KeyType>* current = table[hashIndex];
                Node<KeyType>* prev = nullptr;

                // 리스트를 순회하면서 데이터가 이미 존재하는지 확인
                while (current != nullptr)
                {
                    //해시 충돌
                    if (current->data == key)
                    {
                        delete newNode;  // 똑같은 데이터가 존재하면 새 노드를 삭제하고 종료
                        return;
                    }
                    prev = current;
                    current = current->next;
                }
                // 똑같은 데이터가 존재하지 않다면 리스트의 끝에 새 노드를 추가
                prev->next = newNode;
            }
        }

        void erase(const KeyType& key)
        {
            const int hashIndex = hashFunction(key);
            Node<KeyType>* current = table[hashIndex];
            Node<KeyType>* prev = nullptr;

            // 리스트를 순회하면서 삭제할 노드를 찾기
            while (current != nullptr)
            {
                if (current->data == key)
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

        bool find(const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType>* current = table[hashIndex];

            // 리스트를 순회하면서 요소를 찾기
            while (current != nullptr)
            {
                if (current->data == key)
                {
                    return true;
                }
                current = current->next;
            }
            return false;
        }
    };
}