#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;


//// 최소 힙 구조체 정의
//typedef struct {
//    int* arr;  // 힙을 나타내는 배열
//    int capacity;  // 힙의 최대 크기
//    int size;  // 힙에 현재 저장된 원소의 개수
//} Heap;
//
//// 힙 생성 함수
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

    //shift up : 자식 노드가 올라가면서 부모 노드를 비교
    void shiftUp(int childIdx)
    {
        //Max Heap
        int parentIdx = (childIdx - 1) / 2;
        T temp;

        //부모가 자식보다 작다면 스왑
        if (childIdx != 0 && _predicate(v[parentIdx],v[childIdx]))
        {
            temp = v[parentIdx];
            v[parentIdx] = v[childIdx];
            v[childIdx] = temp;

            shiftUp(parentIdx); //재귀호출
        }
    }

    // 힙에 원소를 삽입하는 함수  O(logN)
    void push(T value)
    {
        // 힙의 맨 끝에 새로운 원소를 추가
        v.push_back(value);

        //자식부터 부모로 비교하면서 자리 찾기
        shiftUp(v.size()-1);
    }

    //힙화(heapify) : 배열을 힙 구조로 변경(최대힙 : 부모가 자식보다 크거나 같다)
    void shiftDown(int parentIdx)
    {
        //Max Heap : 부모가 자식보다 크거나 같다.
        int leftIdx = 2 * parentIdx + 1;
        int rightIdx = leftIdx + 1;
        int largeIdx = -1;
        T temp;

        if (leftIdx < v.size())
            largeIdx = leftIdx;

        if (rightIdx < v.size() && _predicate(v[leftIdx], v[rightIdx]))
            largeIdx = rightIdx;

        //자식이 없는 경우 -1값을 유지
        if (largeIdx != -1 && _predicate(v[parentIdx],v[largeIdx])) //자식 중 큰 값 > 부모의 값
        {
            //값 교환
            temp = v[largeIdx];
            v[largeIdx] = v[parentIdx];
            v[parentIdx] = temp;

            shiftDown(largeIdx); //재귀호출
        }
    }

    // 최대 힙에서 최댓값을 삭제하고 반환하는 함수 O(logN)
    T pop()
    {

        if (v.size() <= 0)
        {
            printf("힙이 비어 있습니다.\n");
            return -1;
        }

        // 힙의 루트에 있는 최댓값을 추출
        T maxValue = v[0];

        // 힙의 맨 끝에 있는 원소를 루트로 이동
        v[0] = v[v.size() - 1];
        v.pop_back();
        shiftDown(0);

        return maxValue;
    }

    T top()
    {
        if (v.size() <= 0)
        {
            printf("힙이 비어 있습니다.\n");
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