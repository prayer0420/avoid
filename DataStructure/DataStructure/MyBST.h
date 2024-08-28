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

        // �� ����
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
                parent = current; // �θ� ��� ����

                if (value < current->value)
                {
                    if (current->left == nullptr)
                    {
                        current->left = new Node(value, parent); // ���ο� ����� �θ� ����
                        return;
                    }
                    current = current->left;
                }
                else if (value > current->value)
                {
                    if (current->right == nullptr)
                    {
                        current->right = new Node(value, parent); // ���ο� ����� �θ� ����
                        return;
                    }
                    current = current->right;
                }
                else {
                    break; // �ߺ��� ���� �������� ����
                }
            }
        }

        // �� �˻�
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

        // �� ����
        void remove(int value)
        {
            root = removeNode(root, value);
        }

        // ���� ��ȸ (In-order Traversal)
        void inOrderTraversal(Node* node)
        {
            if (node == nullptr) return;
            inOrderTraversal(node->left);
            cout << node->value << " ";
            inOrderTraversal(node->right);
        }

    private:
        Node* removeNode(Node* node, int value)
        {
            if (node == nullptr) return nullptr;

            if (value < node->value)
            {
                node->left = removeNode(node->left, value);
            }
            else if (value > node->value)
            {
                node->right = removeNode(node->right, value);
            }
            else {
                if (node->left == nullptr)
                {
                    Node* temp = node->right;
                    if (temp != nullptr) temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr)
                {
                    Node* temp = node->left;
                    if (temp != nullptr) temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    return temp;
                }

                Node* temp = findMin(node->right);
                node->value = temp->value;
                node->right = removeNode(node->right, temp->value);
            }
            return node;
        }

        // ������ ����Ʈ������ ���� ���� ���� ���� ��带 ã�� �Լ�
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