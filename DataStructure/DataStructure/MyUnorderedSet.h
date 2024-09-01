#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
using namespace std;

namespace MyUS
{
    // �ؽ� ���̺��� ũ��
    const int TABLE_SIZE = 10;

    template<typename KeyType>
    struct Node
    {
        KeyType data;  // ��Ҹ� ����
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
            // ��带 ���������� ����
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

        // �̹� �����ϴ� ��Ҷ�� �������� ����
        void insert(const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType>* newNode = new Node<KeyType>(key);

            // �ش� �ε����� ���� ��尡 ���ٸ�, �� ��带 ù ��° ���� ����
            if (!table[hashIndex])
            {
                table[hashIndex] = newNode;
            }
            else
            {
                // �ش� �ε����� �̹� ��尡 �ִ� ��� 
                Node<KeyType>* current = table[hashIndex];
                Node<KeyType>* prev = nullptr;

                // ����Ʈ�� ��ȸ�ϸ鼭 �����Ͱ� �̹� �����ϴ��� Ȯ��
                while (current != nullptr)
                {
                    //�ؽ� �浹
                    if (current->data == key)
                    {
                        delete newNode;  // �Ȱ��� �����Ͱ� �����ϸ� �� ��带 �����ϰ� ����
                        return;
                    }
                    prev = current;
                    current = current->next;
                }
                // �Ȱ��� �����Ͱ� �������� �ʴٸ� ����Ʈ�� ���� �� ��带 �߰�
                prev->next = newNode;
            }
        }

        void erase(const KeyType& key)
        {
            const int hashIndex = hashFunction(key);
            Node<KeyType>* current = table[hashIndex];
            Node<KeyType>* prev = nullptr;

            // ����Ʈ�� ��ȸ�ϸ鼭 ������ ��带 ã��
            while (current != nullptr)
            {
                if (current->data == key)
                {
                    if (prev == nullptr)
                    {
                        // ù ��° ��带 �����ϴ� ���
                        table[hashIndex] = current->next;
                    }
                    else
                    {
                        // �߰� �Ǵ� �� ��带 �����ϴ� ���
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

            // ����Ʈ�� ��ȸ�ϸ鼭 ��Ҹ� ã��
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