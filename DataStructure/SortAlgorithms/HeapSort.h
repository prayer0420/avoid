#pragma once
#include <vector>
using namespace std;

void shiftDown(vector<int>& v, int parentIdx, int size)
{
	//최대힙 구현 : 부모는 자식보다 크거나 같다
	//최대힙의 조건을 바꾸면 최소힙이 된다.
	//부모인덱스에서 자식인덱스를 구해서 비교
	int leftIdx = 2 * parentIdx + 1;
	int rightIdx = leftIdx + 1;
	int largeIdx = -1; //인덱스로 사용할 수 없는 값으로 초기화
	int temp = 0;

	if (leftIdx < size)
		largeIdx = leftIdx; //왼쪽 인덱스가 큰 인덱스

	if (rightIdx < size && v[largeIdx] < v[rightIdx])
		largeIdx = rightIdx;

	//largeIdx != -1 : 자식이 없는 경우는 조건을 패스!!!
	if (largeIdx != -1 && v[largeIdx] > v[parentIdx]) //자식중 큰 값 > 부모의 값
	{
		//자식중 큰 값과 부모의 값을 교환
		temp = v[largeIdx];
		v[largeIdx] = v[parentIdx];
		v[parentIdx] = temp;

		shiftDown(v, largeIdx, size); //재귀호출(변경된 값이 자식보다 작을 수 있기 때문에)
	}
}

void heapSort(vector<int>& v , int size) //O(N * logN)
{
	int i, temp;
	//shiftDown => O(logN)
	for (i = size / 2 - 1; i >= 0; i--) //parent인덱스의 첨자
		shiftDown(v, i, size);


	for (i = size - 1; i > 0; i--) //O(N)
	{
		//마지막에 제일 큰 값을 대입
		temp = v[0];
		v[0] = v[i];
		v[i] = temp;
		shiftDown(v, 0, i); //0번부터 shiftDown ==> i값이 줄어드는 원소의 개수를 의미함
	}

	////마지막에 제일 큰 값을 대입
	//temp = arr[0];
	//arr[0] = arr[9];
	//arr[9] = temp;

	//shiftDown(arr, 0, size - 1);

	////마지막에 제일 큰 값을 대입
	//temp = arr[0];
	//arr[0] = arr[8];
	//arr[8] = temp;
	//shiftDown(arr, 0, size - 2);	
}

