#pragma once
#include <vector>
using namespace std;

void shiftDown(vector<int>& v, int parentIdx, int size)
{
	//�ִ��� ���� : �θ�� �ڽĺ��� ũ�ų� ����
	//�ִ����� ������ �ٲٸ� �ּ����� �ȴ�.
	//�θ��ε������� �ڽ��ε����� ���ؼ� ��
	int leftIdx = 2 * parentIdx + 1;
	int rightIdx = leftIdx + 1;
	int largeIdx = -1; //�ε����� ����� �� ���� ������ �ʱ�ȭ
	int temp = 0;

	if (leftIdx < size)
		largeIdx = leftIdx; //���� �ε����� ū �ε���

	if (rightIdx < size && v[largeIdx] < v[rightIdx])
		largeIdx = rightIdx;

	//largeIdx != -1 : �ڽ��� ���� ���� ������ �н�!!!
	if (largeIdx != -1 && v[largeIdx] > v[parentIdx]) //�ڽ��� ū �� > �θ��� ��
	{
		//�ڽ��� ū ���� �θ��� ���� ��ȯ
		temp = v[largeIdx];
		v[largeIdx] = v[parentIdx];
		v[parentIdx] = temp;

		shiftDown(v, largeIdx, size); //���ȣ��(����� ���� �ڽĺ��� ���� �� �ֱ� ������)
	}
}

void heapSort(vector<int>& v , int size) //O(N * logN)
{
	int i, temp;
	//shiftDown => O(logN)
	for (i = size / 2 - 1; i >= 0; i--) //parent�ε����� ÷��
		shiftDown(v, i, size);


	for (i = size - 1; i > 0; i--) //O(N)
	{
		//�������� ���� ū ���� ����
		temp = v[0];
		v[0] = v[i];
		v[i] = temp;
		shiftDown(v, 0, i); //0������ shiftDown ==> i���� �پ��� ������ ������ �ǹ���
	}

	////�������� ���� ū ���� ����
	//temp = arr[0];
	//arr[0] = arr[9];
	//arr[9] = temp;

	//shiftDown(arr, 0, size - 1);

	////�������� ���� ū ���� ����
	//temp = arr[0];
	//arr[0] = arr[8];
	//arr[8] = temp;
	//shiftDown(arr, 0, size - 2);	
}

