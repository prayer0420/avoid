#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

namespace MyUM
{
    // �� ���� ���õ� �����͸� �ϳ��� ������ ���� ���� ���
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

    // makePair �Լ�
    template <typename T1, typename T2>
    MyPair<T1, T2> makePair(T1 f, T2 s)
    {
        return MyPair<T1, T2>(f, s);
    }


    template<typename KeyType, typename ValueType>
    struct Node
    {
        MyPair<KeyType, ValueType> data; // Ű-�� ���� ����

        Node* next;  // �ؽ� ���̺��� ü�̴׿� ���Ǵ� ������

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

        // �ؽ� �Լ�: Ű�� �ؽ� ���� ����Ͽ� hash index��ȯ
        int hashFunction(const KeyType& key)
        {
            return hash<KeyType>{}(key) % TABLE_SIZE;
        }

    public:

        //���̺� ũ�⸸ŭ nullptr�� �ʱ�ȭ�� ���͸� ����
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

        // Ű�� ������ �⺻������ ���� �߰��Ͽ� ��ȯ
        ValueType& operator[](const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType, ValueType>* current = table[hashIndex];

            // ����Ʈ�� ��ȸ�ϸ鼭 Ű�� ã��
            while (current != nullptr)
            {
                if (current->data.first == key)
                {
                    return current->data.second;  // Ű�� ã���� ���� ������ ��ȯ
                }
                current = current->next;
            }

            // Ű�� ������ ���� �߰��ϰ�
            //ValueType()�� �ش�Ÿ�Կ� �°� �ʱ�ȭ(�⺻��)�ϴ� ��
            insert(makePair(key, ValueType()));
            //������ ��ȯ
            current = table[hashIndex];
            return current->data.second;
        }

        // insert �Լ�: �־��� Ű-�� ���� �ؽ� ���̺� �����մϴ�.
        // �̹� �����ϴ� Ű��� ���� ������Ʈ�մϴ�.
        void insert(const MyPair<KeyType, ValueType>& _myPair)
        {
            int hashIndex = hashFunction(_myPair.first);  // Ű�� �ؽ� ���� ����Ͽ� �ؽ� �ε����� ����

            Node<KeyType, ValueType>* newNode = new Node<KeyType, ValueType>(_myPair);  // ���ο� ��带 ����

            // �ش� �ε����� ���� ��尡 ���ٸ�, �� ��带 ù ��° ���� ����
            if (!table[hashIndex])
            {
                table[hashIndex] = newNode;
            }
            // �ش� �ε����� �̹� ��尡 �ִ� ���
            else
            {
                //���縦 ����Ű�� �ִ� ����, ���� ��带 ����
                Node<KeyType, ValueType>* current = table[hashIndex];
                Node<KeyType, ValueType>* prev = nullptr;

                // ����Ʈ�� ��ȸ�ϸ鼭 Ű�� �̹� �����ϴ��� Ȯ��
                while (current != nullptr)
                {
                    // �Ȱ��� Ű�� �̹� �����ϸ� ���� ������Ʈ
                    if (current->data.first == _myPair.first)
                    {
                        current->data.second = _myPair.second;
                        delete newNode;  // ���� ������ ���� �ʿ� �����Ƿ� ����
                        return;
                    }
                    //����Ʈ�� �� ������ �̵�
                    prev = current;
                    current = current->next;
                }
                // Ű�� �������� �ʴ´ٸ� (�ؽ��浹) ����Ʈ�� ���� �� ��带 �߰�
                prev->next = newNode;
            }
        }

        void erase(const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType, ValueType>* current = table[hashIndex];
            Node<KeyType, ValueType>* prev = nullptr;

            // ����Ʈ�� ��ȸ�ϸ鼭 ������ ��带 ã���ϴ�.
            while (current != nullptr)
            {
                if (current->data.first == key)
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

        ValueType& find(const KeyType& key)
        {
            int hashIndex = hashFunction(key);
            Node<KeyType, ValueType>* current = table[hashIndex];

            // ����Ʈ�� ��ȸ�ϸ鼭 Ű�� ã��
            while (current != nullptr)
            {
                if (current->data.first == key)
                {
                    return current->data.second;
                }
                current = current->next;
            }
            // Ű�� ������ ���� �߰��ϰ�
            //ValueType()�� �ش�Ÿ�Կ� �°� �ʱ�ȭ(�⺻��)�ϴ� ��
            insert(makePair(key, ValueType()));
            //������ ��ȯ
            current = table[hashIndex];
            return current->data.second;
        }
    };
}