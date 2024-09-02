#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;


//// �ּ� �� ����ü ����
//typedef struct {
//    int* arr;  // ���� ��Ÿ���� �迭
//    int capacity;  // ���� �ִ� ũ��
//    int size;  // ���� ���� ����� ������ ����
//} Heap;
//
//// �� ���� �Լ�
//Heap* createHeap(Heap* pHp, int count) {
//    pHp->arr = (int*)malloc(count * sizeof(int));
//    pHp->size = 0;
//    pHp->capacity = count;
//
//    return pHp;
//}

template< typename T, typename ComparePredicate = less<T>>
class MyPriorityQueue
{
private: 

    vector<T> v;
    ComparePredicate _predicate;

public:

    MyPriorityQueue()
    {
        v.reserve(100);
    }

    //shift up : �ڽ� ��尡 �ö󰡸鼭 �θ� ��带 ��
    void shiftUp(int childIdx)
    {
        //Max Heap
        int parentIdx = (childIdx - 1) / 2;
        T temp;

        //�θ� �ڽĺ��� �۴ٸ� ����
        if (childIdx != 0 && _predicate(v[parentIdx],v[childIdx]))
        {
            temp = v[parentIdx];
            v[parentIdx] = v[childIdx];
            v[childIdx] = temp;

            shiftUp(parentIdx); //���ȣ��
        }
    }

    // ���� ���Ҹ� �����ϴ� �Լ�  O(logN)
    void push(T value)
    {
        // ���� �� ���� ���ο� ���Ҹ� �߰�
        v.push_back(value);

        //�ڽĺ��� �θ�� ���ϸ鼭 �ڸ� ã��
        shiftUp(v.size()-1);
    }

    //��ȭ(heapify) : �迭�� �� ������ ����(�ִ��� : �θ� �ڽĺ��� ũ�ų� ����)
    void shiftDown(int parentIdx)
    {
        //Max Heap : �θ� �ڽĺ��� ũ�ų� ����.
        int leftIdx = 2 * parentIdx + 1;
        int rightIdx = leftIdx + 1;
        int largeIdx = -1;
        T temp;

        if (leftIdx < v.size())
            largeIdx = leftIdx;

        if (rightIdx < v.size() && _predicate(v[leftIdx], v[rightIdx]))
            largeIdx = rightIdx;

        //�ڽ��� ���� ��� -1���� ����
        if (largeIdx != -1 && _predicate(v[parentIdx],v[largeIdx])) //�ڽ� �� ū �� > �θ��� ��
        {
            //�� ��ȯ
            temp = v[largeIdx];
            v[largeIdx] = v[parentIdx];
            v[parentIdx] = temp;

            shiftDown(largeIdx); //���ȣ��
        }
    }

    // �ִ� ������ �ִ��� �����ϰ� ��ȯ�ϴ� �Լ� O(logN)
    T pop()
    {

        if (v.size() <= 0)
        {
            printf("���� ��� �ֽ��ϴ�.\n");
            return -1;
        }

        // ���� ��Ʈ�� �ִ� �ִ��� ����
        T maxValue = v[0];

        // ���� �� ���� �ִ� ���Ҹ� ��Ʈ�� �̵�
        v[0] = v[v.size() - 1];
        v.pop_back();
        shiftDown(0);

        return maxValue;
    }

    T top()
    {
        if (v.size() <= 0)
        {
            printf("���� ��� �ֽ��ϴ�.\n");
            return -1;
        }

        return v[0];
    }

    bool empty() 
    {
        return v.empty();
    }

    void printHeap() 
    {
        printf("Heap display : ");
        for (int i = 0; i < v.size(); i++) 
        {
            printf("%d ", v[i]);
        }
        printf("\n");
    }
};