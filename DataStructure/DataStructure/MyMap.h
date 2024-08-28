#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace MyMap
{
    struct Node
    {
        string key;  // 키 (문자열로 저장)
        int value;   // 값 (정수로 저장)
        Node* left;
        Node* right;
        Node* parent;

        Node(string k, int v, Node* p = nullptr) : key(k), value(v), left(nullptr), right(nullptr), parent(p) {}
    };

    // 키-값 쌍을 저장하며, 키를 기준으로 정렬
    class MyMap
    {
    public:
        Node* root = nullptr;

        // 맵에 새로운 키-값 쌍을 삽입
        void insert(string key, int value)
        {
            // 처음이라면 루트노드로 설정
            if (root == nullptr)
            {
                root = new Node(key, value);
                return;
            }

            Node* compareNode = root;  // 루트부터 시작해서 트리를 탐색
            Node* parentNode = nullptr; // 부모 노드를 추적하기 위한 포인터

            while (compareNode != nullptr)
            {
                parentNode = compareNode; // 현재 노드를 부모 노드로 설정

                // 삽입하려는 키가 현재 노드의 키보다 작으면 왼쪽으로 이동
                if (key < compareNode->key)
                {
                    // 더 이상 왼쪽 자식이 없으면 새로운 노드를 이 위치에 삽입하고, 부모를 설정
                    if (compareNode->left == nullptr)
                    {
                        compareNode->left = new Node(key, value, parentNode); // 부모 노드를 설정
                        return;
                    }
                    compareNode = compareNode->left; // 왼쪽 자식으로 이동
                }
                // 삽입하려는 키가 현재 노드의 키보다 크면 오른쪽으로 이동
                else if (key > compareNode->key)
                {
                    // 더 이상 오른쪽 자식이 없으면 새로운 노드를 이 위치에 삽입하고, 부모를 설정
                    if (compareNode->right == nullptr)
                    {
                        compareNode->right = new Node(key, value, parentNode); // 부모 노드를 설정
                        return;
                    }
                    compareNode = compareNode->right; // 오른쪽 자식으로 이동
                }
                // 삽입하려는 키가 이미 트리에 존재하면 값을 업데이트
                else
                {
                    compareNode->value = value; // 키가 같다면 값을 업데이트
                    return;
                }
            }
        }

        // search 함수: 맵에서 특정 키를 검색하여 해당 값을 반환
        // 키가 존재하면 해당 값을 참조로 반환하고, 없으면 예외를 던짐
        int& search(string key)
        {
            Node* compareNode = root;  // 루트부터 시작해서 트리를 탐색
            while (compareNode != nullptr)
            {
                if (key == compareNode->key)
                {
                    return compareNode->value;  // 키를 찾으면 값을 참조로 반환
                }
                else if (key < compareNode->key)
                {
                    compareNode = compareNode->left;  // 키가 현재 노드보다 작으면 왼쪽으로 이동
                }
                else
                {
                    compareNode = compareNode->right; // 키가 현재 노드보다 크면 오른쪽으로 이동
                }
            }
            throw std::runtime_error("Key not found");  // 키를 찾지 못하면 예외를 던짐
        }

        // 중위 순회(in-order traversal)하면서 키-값 쌍을 출력
        // 중위 순회는 왼쪽 자식 -> 현재 노드 -> 오른쪽 자식 순서로 노드를 방문하므로, 키들이 오름차순으로 출력
        void inOrderTraversal(Node* node)
        {
            if (node == nullptr)
                return;  // 노드가 null이면 아무것도 하지 않음

            inOrderTraversal(node->left);  // 왼쪽 자식 방문
            cout << node->key << ": " << node->value << " ";  // 현재 노드의 키-값 쌍 출력
            inOrderTraversal(node->right); // 오른쪽 자식 방문
        }

        // 삭제 함수: 특정 키에 해당하는 노드를 삭제
        void remove(string key)
        {
            root = removeNode(root, key);
        }

        Node* removeNode(Node* node, string key)
        {
            if (node == nullptr)
                return nullptr;

            if (key < node->key)
            {
                node->left = removeNode(node->left, key);
            }
            else if (key > node->key)
            {
                node->right = removeNode(node->right, key);
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
                            node->parent->left = nullptr;  // 부모의 왼쪽 자식에서 제거
                        else
                            node->parent->right = nullptr; // 부모의 오른쪽 자식에서 제거
                    }
                    delete node;
                    return nullptr;
                }

                // 하나의 자식만 있는 경우
                else if (node->left == nullptr)
                {
                    Node* temp = node->right;  // 오른쪽 자식으로 대체
                    temp->parent = node->parent; // 자식의 부모를 현재 노드의 부모로 설정
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr)
                {
                    Node* temp = node->left;  // 왼쪽 자식으로 대체
                    temp->parent = node->parent; // 자식의 부모를 현재 노드의 부모로 설정
                    delete node;
                    return temp;
                }

                // 두 개의 자식을 가진 경우, 오른쪽 서브트리에서 최소값을 찾음
                Node* temp = findMin(node->right);

                node->key = temp->key;
                node->value = temp->value;

                node->right = removeNode(node->right, temp->key);
            }
            return node;
        }

        // 오른쪽 서브트리에서 가장 작은 값을 가진 노드를 찾는 함수
        Node* findMin(Node* node)
        {
            while (node->left != nullptr)
            {
                node = node->left;
            }
            return node;
        }
    };
}