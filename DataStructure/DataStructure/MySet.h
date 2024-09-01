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

        // ���� �Լ�
        void insert(T value) {

            // ó�� �����ϴ� ���̶��, ��Ʈ ���� ����
            if (root == nullptr)
            {
                root = new Node<T>(value);
                return;
            }

            Node<T>* compareNode = root;  // ��Ʈ���� �����ؼ� Ʈ���� Ž��
            Node<T>* parentNode = nullptr; // �θ� ��带 �����ϱ� ���� ������

            while (compareNode != nullptr)
            {
                parentNode = compareNode;  // ���� ��带 �θ�� ����

                // �����Ϸ��� ���� ���� ����� ������ ������ �������� �̵�
                if (value < compareNode->value)
                {
                    if (compareNode->left == nullptr)
                    {
                        // ���� �ڽ��� ������ ���ο� ��带 �� ��ġ�� �����ϰ�, �θ� ����
                        compareNode->left = new Node<T>(value, compareNode); // �θ� ��带 ����
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
                        compareNode->right = new Node<T>(value, compareNode); // �θ� ��带 ����
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
        bool contains(T value)
        {
            Node<T>* compareNode = root;  // ��Ʈ���� �����ؼ� Ʈ���� Ž��

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
        void inOrderTraversal(Node<T>* node)
        {
            if (node == nullptr)
                return;  // ��尡 null�̸� �ƹ��͵� ���� ����

            inOrderTraversal(node->left);  // ���� �ڽ� �湮
            cout << node->value << " ";    // ���� ����� �� ���
            inOrderTraversal(node->right); // ������ �ڽ� �湮
        }

        // ��� ���� �Լ�
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
                // ������ ���� ���� ��庸�� ������ �������� �̵�
                removeNode(node->left, value);
            }
            else if (value > node->value)
            {
                // ������ ���� ���� ��庸�� ũ�� ���������� �̵�
                removeNode(node->right, value);
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
                            node->parent->left = nullptr;  // �θ��� ���� �ڽ����κ��� ����
                        else
                            node->parent->right = nullptr; // �θ��� ������ �ڽ����κ��� ����
                    }
                    delete node;
                }
                // �ϳ��� �ڽĸ� �ִ� ���
                else if (node->left == nullptr)
                {
                    Node<T>* temp = node->right;  // ������ �ڽ����� ��ü
                    temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    node = temp;
                }
                else if (node->right == nullptr)
                {
                    Node<T>* temp = node->left;  // ���� �ڽ����� ��ü
                    temp->parent = node->parent; // �ڽ��� �θ� ���� ����� �θ�� ����
                    delete node;
                    node = temp;
                }
                else
                {
                    // �� ���� �ڽ��� ���� ���, ������ ����Ʈ������ �ּҰ��� ã��
                    Node<T>* temp = findMin(node->right);
                    node->value = temp->value;
                    removeNode(node->right, temp->value);
                }
            }
        }

        // ������ ����Ʈ������ ���� ���� ���� ���� ��带 ã�� �Լ�
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
