#pragma once
#include <iostream>
using namespace std;

namespace MySet
{
    template<typename T>
    struct Node
    {
        T value;
        Node* left;
        Node* right;
        Node* parent;

        Node(T v, Node* p = nullptr) : value(v), left(nullptr), right(nullptr), parent(p) {}
    };

    template<typename T>
    class MySet
    {
    public:
        Node<T>* root = nullptr;

        // 삽입 함수
        void insert(T value) {

            // 처음 삽입하는 값이라면, 루트 노드로 설정
            if (root == nullptr)
            {
                root = new Node<T>(value);
                return;
            }

            Node<T>* compareNode = root;  // 루트부터 시작해서 트리를 탐색
            Node<T>* parentNode = nullptr; // 부모 노드를 추적하기 위한 포인터

            while (compareNode != nullptr)
            {
                parentNode = compareNode;  // 현재 노드를 부모로 설정

                // 삽입하려는 값이 현재 노드의 값보다 작으면 왼쪽으로 이동
                if (value < compareNode->value)
                {
                    if (compareNode->left == nullptr)
                    {
                        // 왼쪽 자식이 없으면 새로운 노드를 이 위치에 삽입하고, 부모를 설정
                        compareNode->left = new Node<T>(value, compareNode); // 부모 노드를 설정
                        return;
                    }
                    compareNode = compareNode->left; // 왼쪽 자식으로 이동
                }
                // 삽입하려는 값이 현재 노드의 값보다 크면 오른쪽으로 이동
                else if (value > compareNode->value)
                {
                    if (compareNode->right == nullptr)
                    {
                        // 오른쪽 자식이 없으면 새로운 노드를 이 위치에 삽입하고, 부모를 설정
                        compareNode->right = new Node<T>(value, compareNode); // 부모 노드를 설정
                        return;
                    }
                    compareNode = compareNode->right; // 오른쪽 자식으로 이동
                }
                else
                {
                    // 중복된 값은 삽입하지 않음
                    return;
                }
            }
        }

        // 값이 포함되어있는지 확인하는 함수
        bool contains(T value)
        {
            Node<T>* compareNode = root;  // 루트부터 시작해서 트리를 탐색

            while (compareNode != nullptr)  // 다 찾아봤는데도 없으면 종료
            {
                if (value == compareNode->value)
                {
                    return true;  // 값을 찾으면 true 반환
                }
                else if (value < compareNode->value)
                {
                    compareNode = compareNode->left;  // 값이 현재 노드보다 작으면 왼쪽으로 이동
                }
                else
                {
                    compareNode = compareNode->right; // 값이 현재 노드보다 크면 오른쪽으로 이동
                }
            }
            return false;  // 값을 찾지 못하면 false 반환
        }

        // 중위 순회 함수: 왼쪽 자식 -> 현재 노드 -> 오른쪽 자식 순서로 방문 (오름차순 출력)
        void inOrderTraversal(Node<T>* node)
        {
            if (node == nullptr)
                return;  // 노드가 null이면 아무것도 하지 않음

            inOrderTraversal(node->left);  // 왼쪽 자식 방문
            cout << node->value << " ";    // 현재 노드의 값 출력
            inOrderTraversal(node->right); // 오른쪽 자식 방문
        }

        // 노드 삭제 함수
        void remove(T value)
        {
            removeNode(root, value);
        }

        void removeNode(Node<T>*& node, T value)
        {
            if (node == nullptr)
                return;

            if (value < node->value)
            {
                // 삭제할 값이 현재 노드보다 작으면 왼쪽으로 이동
                removeNode(node->left, value);
            }
            else if (value > node->value)
            {
                // 삭제할 값이 현재 노드보다 크면 오른쪽으로 이동
                removeNode(node->right, value);
            }
            else // 삭제할 노드를 찾았을 때
            {
                // 자식이 없는 경우 (리프 노드)
                if (node->left == nullptr && node->right == nullptr)
                {
                    // 부모 노드에서 이 노드를 제거
                    if (node->parent != nullptr)
                    {
                        if (node->parent->left == node)
                            node->parent->left = nullptr;  // 부모의 왼쪽 자식으로부터 제거
                        else
                            node->parent->right = nullptr; // 부모의 오른쪽 자식으로부터 제거
                    }
                    delete node;
                }
                // 하나의 자식만 있는 경우
                else if (node->left == nullptr)
                {
                    Node<T>* temp = node->right;  // 오른쪽 자식으로 대체
                    temp->parent = node->parent; // 자식의 부모를 현재 노드의 부모로 설정
                    delete node;
                    node = temp;
                }
                else if (node->right == nullptr)
                {
                    Node<T>* temp = node->left;  // 왼쪽 자식으로 대체
                    temp->parent = node->parent; // 자식의 부모를 현재 노드의 부모로 설정
                    delete node;
                    node = temp;
                }
                else
                {
                    // 두 개의 자식을 가진 경우, 오른쪽 서브트리에서 최소값을 찾음
                    Node<T>* temp = findMin(node->right);
                    node->value = temp->value;
                    removeNode(node->right, temp->value);
                }
            }
        }

        // 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 찾는 함수
        Node<T>* findMin(Node<T>* node)
        {
            while (node->left != nullptr)
            {
                node = node->left;
            }
            return node;
        }
    };

}
