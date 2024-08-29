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
            removeNode(root, value);
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
                // �ڽ��� ���� ��� (���� ���)
                if (node->left == nullptr && node->right == nullptr)
                {
                    // �θ� ��忡�� �� ��带 ����
                    if (node->parent != nullptr)
                    {
                        if (node->parent->left == node)
                            node->parent->left = nullptr;  // �θ��� ���� �ڽ����κ��� ����
                        else
                            node->parent->right = nullptr; // �θ��� ������ �ڽ����κ��� ����
                    }
                    delete node;
                }
                //�ڽ��� �����ʿ��� �ִ� ���
                else if (node->left == nullptr)
                {
                    Node* temp = node->right;
                    temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    node = temp;
                }
                //�ڽ��� ���ʿ��� �ִ� ���
                else if (node->right == nullptr)
                {
                    Node* temp = node->left;
                    temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    node = temp;
                }
                //�ڽ��� �Ѵ� �ִ� ���
                else
                {
                    Node* temp = findMin(node->right);
                    node->value = temp->value;
                    removeNode(node->right, temp->value);
                }
            }
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