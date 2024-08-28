#pragma once
#include <iostream>
#include <string>
using namespace std;

namespace MyMap
{
    struct Node
    {
        string key;  // Ű (���ڿ��� ����)
        int value;   // �� (������ ����)
        Node* left;
        Node* right;
        Node* parent;

        Node(string k, int v, Node* p = nullptr) : key(k), value(v), left(nullptr), right(nullptr), parent(p) {}
    };

    // Ű-�� ���� �����ϸ�, Ű�� �������� ����
    class MyMap
    {
    public:
        Node* root = nullptr;

        // �ʿ� ���ο� Ű-�� ���� ����
        void insert(string key, int value)
        {
            // ó���̶�� ��Ʈ���� ����
            if (root == nullptr)
            {
                root = new Node(key, value);
                return;
            }

            Node* compareNode = root;  // ��Ʈ���� �����ؼ� Ʈ���� Ž��
            Node* parentNode = nullptr; // �θ� ��带 �����ϱ� ���� ������

            while (compareNode != nullptr)
            {
                parentNode = compareNode; // ���� ��带 �θ� ���� ����

                // �����Ϸ��� Ű�� ���� ����� Ű���� ������ �������� �̵�
                if (key < compareNode->key)
                {
                    // �� �̻� ���� �ڽ��� ������ ���ο� ��带 �� ��ġ�� �����ϰ�, �θ� ����
                    if (compareNode->left == nullptr)
                    {
                        compareNode->left = new Node(key, value, parentNode); // �θ� ��带 ����
                        return;
                    }
                    compareNode = compareNode->left; // ���� �ڽ����� �̵�
                }
                // �����Ϸ��� Ű�� ���� ����� Ű���� ũ�� ���������� �̵�
                else if (key > compareNode->key)
                {
                    // �� �̻� ������ �ڽ��� ������ ���ο� ��带 �� ��ġ�� �����ϰ�, �θ� ����
                    if (compareNode->right == nullptr)
                    {
                        compareNode->right = new Node(key, value, parentNode); // �θ� ��带 ����
                        return;
                    }
                    compareNode = compareNode->right; // ������ �ڽ����� �̵�
                }
                // �����Ϸ��� Ű�� �̹� Ʈ���� �����ϸ� ���� ������Ʈ
                else
                {
                    compareNode->value = value; // Ű�� ���ٸ� ���� ������Ʈ
                    return;
                }
            }
        }

        // search �Լ�: �ʿ��� Ư�� Ű�� �˻��Ͽ� �ش� ���� ��ȯ
        // Ű�� �����ϸ� �ش� ���� ������ ��ȯ�ϰ�, ������ ���ܸ� ����
        int& search(string key)
        {
            Node* compareNode = root;  // ��Ʈ���� �����ؼ� Ʈ���� Ž��
            while (compareNode != nullptr)
            {
                if (key == compareNode->key)
                {
                    return compareNode->value;  // Ű�� ã���� ���� ������ ��ȯ
                }
                else if (key < compareNode->key)
                {
                    compareNode = compareNode->left;  // Ű�� ���� ��庸�� ������ �������� �̵�
                }
                else
                {
                    compareNode = compareNode->right; // Ű�� ���� ��庸�� ũ�� ���������� �̵�
                }
            }
            throw std::runtime_error("Key not found");  // Ű�� ã�� ���ϸ� ���ܸ� ����
        }

        // ���� ��ȸ(in-order traversal)�ϸ鼭 Ű-�� ���� ���
        // ���� ��ȸ�� ���� �ڽ� -> ���� ��� -> ������ �ڽ� ������ ��带 �湮�ϹǷ�, Ű���� ������������ ���
        void inOrderTraversal(Node* node)
        {
            if (node == nullptr)
                return;  // ��尡 null�̸� �ƹ��͵� ���� ����

            inOrderTraversal(node->left);  // ���� �ڽ� �湮
            cout << node->key << ": " << node->value << " ";  // ���� ����� Ű-�� �� ���
            inOrderTraversal(node->right); // ������ �ڽ� �湮
        }

        // ���� �Լ�: Ư�� Ű�� �ش��ϴ� ��带 ����
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
            else // ������ ��带 ã���� �� 
            {
                // �ڽ��� ���� ��� (���� ���)
                if (node->left == nullptr && node->right == nullptr)
                {
                    // �θ� ��忡�� �� ��带 ����
                    if (node->parent != nullptr)
                    {
                        if (node->parent->left == node)
                            node->parent->left = nullptr;  // �θ��� ���� �ڽĿ��� ����
                        else
                            node->parent->right = nullptr; // �θ��� ������ �ڽĿ��� ����
                    }
                    delete node;
                    return nullptr;
                }

                // �ϳ��� �ڽĸ� �ִ� ���
                else if (node->left == nullptr)
                {
                    Node* temp = node->right;  // ������ �ڽ����� ��ü
                    temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    return temp;
                }
                else if (node->right == nullptr)
                {
                    Node* temp = node->left;  // ���� �ڽ����� ��ü
                    temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    return temp;
                }

                // �� ���� �ڽ��� ���� ���, ������ ����Ʈ������ �ּҰ��� ã��
                Node* temp = findMin(node->right);

                node->key = temp->key;
                node->value = temp->value;

                node->right = removeNode(node->right, temp->key);
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