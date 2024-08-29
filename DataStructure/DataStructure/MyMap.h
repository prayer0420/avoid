#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

namespace MyMap
{
    // MyPair ���ø� ����ü
    template <typename T1, typename T2>
    struct MyPair
    {
        T1 first;
        T2 second;

        MyPair() : first(T1()), second(T2()) {} // �⺻ ������
        MyPair(const T1& a, const T2& b) : first(a), second(b) {} // �Ű����� ������
    };

    // makePair �Լ�
    template <typename T1, typename T2>
    MyPair<T1, T2> makePair(T1 f, T2 s)
    {
        return MyPair<T1, T2>(f, s);
    }

    // Node ����ü (BST ���)
    template <typename KeyType, typename ValueType>
    struct Node
    {
        MyPair<KeyType, ValueType> data; // Ű-�� ���� ����
        Node* left;
        Node* right;
        Node* parent;

        Node(const MyPair<KeyType, ValueType>& d, Node* p = nullptr)
            : data(d), left(nullptr), right(nullptr), parent(p)
        {}
    };

    // MyMap Ŭ���� (BST ���)
    template <typename KeyType, typename ValueType>
    class MyMap
    {
    private:
        Node<KeyType, ValueType>* root;

        Node<KeyType, ValueType>* find(Node<KeyType, ValueType>* node, const KeyType& key)
        {
            if (node == nullptr || node->data.first == key)
                return node;

            if (key < node->data.first)
                return find(node->left, key);
            else
                return find(node->right, key);
        }

        Node<KeyType, ValueType>* findMin(Node<KeyType, ValueType>* node)
        {
            while (node->left != nullptr)
                node = node->left;
            return node;
        }

        void removeNode(Node<KeyType, ValueType>*& node, const KeyType& key)
        {
            if (node == nullptr)
                return;

            if (key < node->data.first)
            {
                removeNode(node->left, key);
            }
            else if (key > node->data.first)
            {
                removeNode(node->right, key);
            }
            else
            {
                // ������ ��带 ã���� ��

                // �ڽ��� ���� ���(�������)
                if (node->left == nullptr && node->right == nullptr)
                {
                    if (node->parent)
                    {
                        // �θ� ��忡�� �� ��带 ����
                        if (node == node->parent->left)
                            node->parent->left = nullptr;
                        else
                            node->parent->right = nullptr;
                    }
                    delete node;
                    node = nullptr;
                }
                // �ڽ��� �ϳ��� �ִ� ���
                else if (node->left == nullptr)
                {
                    Node<KeyType, ValueType>* temp = node->right;
                    temp->parent = node->parent;
                    delete node;
                    node = temp;
                }
                else if (node->right == nullptr)
                {
                    Node<KeyType, ValueType>* temp = node->left;
                    temp->parent = node->parent;
                    delete node;
                    node = temp;
                }
                else
                {
                    // �ڽ��� �� �� �ִ� ���
                    Node<KeyType, ValueType>* temp = findMin(node->right);
                    node->data = temp->data;
                    removeNode(node->right, temp->data.first);
                }
            }
        }

        void inOrderTraversal(Node<KeyType, ValueType>* node)
        {
            if (node == nullptr)
                return;

            inOrderTraversal(node->left);
            cout << node->data.first << ": " << node->data.second << " ";
            inOrderTraversal(node->right);
        }

    public:
        MyMap() : root(nullptr) {}

        // ���� �Լ�
        void insert(const MyPair<KeyType, ValueType>& pair)
        {
            if (root == nullptr)
            {
                root = new Node<KeyType, ValueType>(pair);
                return;
            }

            Node<KeyType, ValueType>* parentNode = nullptr;
            Node<KeyType, ValueType>* currentNode = root;

            while (currentNode != nullptr)
            {
                parentNode = currentNode;

                if (pair.first < currentNode->data.first)
                {
                    if (currentNode->left == nullptr)
                    {
                        currentNode->left = new Node<KeyType, ValueType>(pair, parentNode);
                        return;
                    }
                    currentNode = currentNode->left;
                }
                else if (pair.first > currentNode->data.first)
                {
                    if (currentNode->right == nullptr)
                    {
                        currentNode->right = new Node<KeyType, ValueType>(pair, parentNode);
                        return;
                    }
                    currentNode = currentNode->right;
                }
                else
                {
                    // Ű�� �̹� �����ϸ� ���� ������Ʈ
                    currentNode->data.second = pair.second;
                    return;
                }
            }
        }

        // operator[] �����ε�
        ValueType& operator[](const KeyType& key)
        {
            Node<KeyType, ValueType>* node = find(root, key);
            if (node != nullptr)
            {
                return node->data.second;
            }
            else
            {
                // Ű�� ������ ���� �߰��ϰ� ���� ��ȯ
                insert(makePair(key, ValueType())); // �⺻ ���� ValueType()���� �ʱ�ȭ
                node = find(root, key);
                return node->data.second;
            }
        }

        // �˻� �Լ�
        ValueType& search(const KeyType& key)
        {
            Node<KeyType, ValueType>* node = find(root, key);

            if (node == nullptr)
                throw runtime_error("Key not found");

            return node->data.second;
        }

        // ���� �Լ�
        void remove(const KeyType& key)
        {
            removeNode(root, key);
        }

        // ��� �Լ� (���� ��ȸ)
        void print()
        {
            inOrderTraversal(root);
            cout << endl;
        }
    };
}
