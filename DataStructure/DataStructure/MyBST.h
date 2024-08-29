#include <iostream>
using namespace std;

namespace BST
{
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node* parent;

        Node(int v, Node* p = nullptr) : value(v), left(nullptr), right(nullptr), parent(p) {}
    };

    class MyBST
    {
    public:
        Node* root = nullptr;

        // 값 삽입
        void insert(int value)
        {
            if (root == nullptr)
            {
                root = new Node(value);
                return;
            }
            Node* current = root;
            Node* parent = nullptr;

            while (current != nullptr)
            {
                parent = current; // 부모 노드 설정

                if (value < current->value)
                {
                    if (current->left == nullptr)
                    {
                        current->left = new Node(value, parent); // 새로운 노드의 부모 설정
                        return;
                    }
                    current = current->left;
                }
                else if (value > current->value)
                {
                    if (current->right == nullptr)
                    {
                        current->right = new Node(value, parent); // 새로운 노드의 부모 설정
                        return;
                    }
                    current = current->right;
                }
                else {
                    break; // 중복된 값은 삽입하지 않음
                }
            }
        }

        // 값 검색
        bool search(int value)
        {
            Node* current = root;
            while (current != nullptr)
            {
                if (value == current->value)
                {
                    return true;
                }
                else if (value < current->value)
                {
                    current = current->left;
                }
                else {
                    current = current->right;
                }
            }
            return false;
        }

        // 값 삭제
        void remove(int value)
        {
            removeNode(root, value);
        }

        // 중위 순회 (In-order Traversal)
        void inOrderTraversal(Node* node)
        {
            if (node == nullptr) return;
            inOrderTraversal(node->left);
            cout << node->value << " ";
            inOrderTraversal(node->right);
        }

    private:
        void removeNode(Node* &node, int value)
        {
            if (node == nullptr) 
                return;

            if (value < node->value)
            {
                removeNode(node->left, value);
            }
            else if (value > node->value)
            {
                removeNode(node->right, value);
            }
            else 
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
                //자식이 오른쪽에만 있는 경우
                else if (node->left == nullptr)
                {
                    Node* temp = node->right;
                    temp->parent = node->parent; // 자식의 부모를 현재 노드의 부모로 설정
                    delete node;
                    node = temp;
                }
                //자식이 왼쪽에만 있는 경우
                else if (node->right == nullptr)
                {
                    Node* temp = node->left;
                    temp->parent = node->parent; // 자식의 부모를 현재 노드의 부모로 설정
                    delete node;
                    node = temp;
                }
                //자식이 둘다 있는 경우
                else
                {
                    Node* temp = findMin(node->right);
                    node->value = temp->value;
                    removeNode(node->right, temp->value);
                }
            }
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