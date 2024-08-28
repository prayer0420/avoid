#pragma once
#include <iostream>
using namespace std;

namespace MySet
{
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node* parent;

        Node(int v, Node* p = nullptr) : value(v), left(nullptr), right(nullptr), parent(p) {}
    };

    // �ߺ��� ���� ������� ������, ���Ե� ���� �ڵ����� ����
    class MySet
    {
    public:
        Node* root = nullptr;  // Ʈ���� ��Ʈ ��带 ����Ű�� ������

        // ���� �Լ�
        void insert(int value) {

            // ó�� �����ϴ� ���̶��, ��Ʈ ���� ����
            if (root == nullptr)
            {
                root = new Node(value);
                return;
            }

            Node* compareNode = root;  // ��Ʈ���� �����ؼ� Ʈ���� Ž��
            Node* parentNode = nullptr; // �θ� ��带 �����ϱ� ���� ������

            while (compareNode != nullptr)
            {
                parentNode = compareNode;  // ���� ��带 �θ�� ����

                // �����Ϸ��� ���� ���� ����� ������ ������ �������� �̵�
                if (value < compareNode->value)
                {
                    if (compareNode->left == nullptr)
                    {
                        // ���� �ڽ��� ������ ���ο� ��带 �� ��ġ�� �����ϰ�, �θ� ����
                        compareNode->left = new Node(value, compareNode); // �θ� ��带 ����
                        return;
                    }
                    compareNode = compareNode->left; // ���� �ڽ����� �̵�
                }
                // �����Ϸ��� ���� ���� ����� ������ ũ�� ���������� �̵�
                else if (value > compareNode->value)
                {
                    if (compareNode->right == nullptr)
                    {
                        // ������ �ڽ��� ������ ���ο� ��带 �� ��ġ�� �����ϰ�, �θ� ����
                        compareNode->right = new Node(value, compareNode); // �θ� ��带 ����
                        return;
                    }
                    compareNode = compareNode->right; // ������ �ڽ����� �̵�
                }
                else
                {
                    // �ߺ��� ���� �������� ����
                    return;
                }
            }
        }

        // ���� ���ԵǾ��ִ��� Ȯ���ϴ� �Լ�
        bool contains(int value)
        {
            Node* compareNode = root;  // ��Ʈ���� �����ؼ� Ʈ���� Ž��

            while (compareNode != nullptr)  // �� ã�ƺôµ��� ������ ����
            {
                if (value == compareNode->value)
                {
                    return true;  // ���� ã���� true ��ȯ
                }
                else if (value < compareNode->value)
                {
                    compareNode = compareNode->left;  // ���� ���� ��庸�� ������ �������� �̵�
                }
                else
                {
                    compareNode = compareNode->right; // ���� ���� ��庸�� ũ�� ���������� �̵�
                }
            }
            return false;  // ���� ã�� ���ϸ� false ��ȯ
        }

        // ���� ��ȸ �Լ�: ���� �ڽ� -> ���� ��� -> ������ �ڽ� ������ �湮 (�������� ���)
        void inOrderTraversal(Node* node)
        {
            if (node == nullptr)
                return;  // ��尡 null�̸� �ƹ��͵� ���� ����

            inOrderTraversal(node->left);  // ���� �ڽ� �湮
            cout << node->value << " ";    // ���� ����� �� ���
            inOrderTraversal(node->right); // ������ �ڽ� �湮
        }

        // ��� ���� �Լ�
        void remove(int value)
        {
            root = removeNode(root, value);
        }

        Node* removeNode(Node* node, int value)
        {
            if (node == nullptr) return nullptr;

            if (value < node->value)
            {
                // ������ ���� ���� ��庸�� ������ �������� �̵�
                node->left = removeNode(node->left, value);
            }
            else if (value > node->value)
            {
                // ������ ���� ���� ��庸�� ũ�� ���������� �̵�
                node->right = removeNode(node->right, value);
            }
            else
            {
                // ������ ��带 ã���� ��

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