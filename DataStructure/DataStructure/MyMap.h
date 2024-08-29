#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

namespace MyMap
{
    // MyPair 템플릿 구조체
    template <typename T1, typename T2>
    struct MyPair
    {
        T1 first;
        T2 second;

        MyPair() : first(T1()), second(T2()) {} // 기본 생성자
        MyPair(const T1& a, const T2& b) : first(a), second(b) {} // 매개변수 생성자
    };

    // makePair 함수
    template <typename T1, typename T2>
    MyPair<T1, T2> makePair(T1 f, T2 s)
    {
        return MyPair<T1, T2>(f, s);
    }

    // Node 구조체 (BST 기반)
    template <typename KeyType, typename ValueType>
    struct Node
    {
        MyPair<KeyType, ValueType> data; // 키-값 쌍을 저장
        Node* left;
        Node* right;
        Node* parent;

        Node(const MyPair<KeyType, ValueType>& d, Node* p = nullptr)
            : data(d), left(nullptr), right(nullptr), parent(p)
        {}
    };

    // MyMap 클래스 (BST 기반)
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
                // 삭제할 노드를 찾았을 때

                // 자식이 없는 경우(리프노드)
                if (node->left == nullptr && node->right == nullptr)
                {
                    if (node->parent)
                    {
                        // 부모 노드에서 이 노드를 제거
                        if (node == node->parent->left)
                            node->parent->left = nullptr;
                        else
                            node->parent->right = nullptr;
                    }
                    delete node;
                    node = nullptr;
                }
                // 자식이 하나만 있는 경우
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
                    // 자식이 둘 다 있는 경우
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

        // 삽입 함수
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
                    // 키가 이미 존재하면 값을 업데이트
                    currentNode->data.second = pair.second;
                    return;
                }
            }
        }

        // operator[] 오버로딩
        ValueType& operator[](const KeyType& key)
        {
            Node<KeyType, ValueType>* node = find(root, key);
            if (node != nullptr)
            {
                return node->data.second;
            }
            else
            {
                // 키가 없으면 새로 추가하고 참조 반환
                insert(makePair(key, ValueType())); // 기본 값을 ValueType()으로 초기화
                node = find(root, key);
                return node->data.second;
            }
        }

        // 검색 함수
        ValueType& search(const KeyType& key)
        {
            Node<KeyType, ValueType>* node = find(root, key);

            if (node == nullptr)
                throw runtime_error("Key not found");

            return node->data.second;
        }

        // 삭제 함수
        void remove(const KeyType& key)
        {
            removeNode(root, key);
        }

        // 출력 함수 (중위 순회)
        void print()
        {
            inOrderTraversal(root);
            cout << endl;
        }
    };
}
