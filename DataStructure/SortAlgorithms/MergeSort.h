#pragma once
#include <iostream>
#include <vector>
using namespace std;


void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;

	vector<int> temp;

	//�������� ���� ����
	while (leftIdx <= mid && rightIdx<= right)
	{
		if (v[leftIdx] <= v[rightIdx]) 
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
		else
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}


	//������ ���� ��������
	if (leftIdx > mid)
	{	//������ ������ �� �־���
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	//�������� ���� ��������
	else /*rightIdx > right*/
	{
		//���� ������ �� �־���
		while (leftIdx<= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	//temp�� ���� ���Ϳ� �ű��;
	for (int i = 0; i < temp.size(); i++)
		v[left + i] = temp[i];
}


void IterativeMergeSort(vector<int>& v) 
{
	int n = v.size();
	//mergeSzie : �����ؾ��� ����� ����(ũ��)
	//mid = �����ؾ��� 2���� ��� �߿� ���� ����� �� �ε���
	//end = �����ؾ��� 2���� ��� �߿� ������ ����� �� �ε���
	for (int mergeSize = 1; mergeSize < n; mergeSize *= 2) 
	{
		for (int left = 0; left < n - 1; left += 2 * mergeSize) 
		{
			int mid = min(left + mergeSize - 1, n - 1);
			int right = min(left + 2 * mergeSize - 1, n - 1);

			// Merge subarrays
			MergeResult(v, left, mid, right);
		}
	}
}

void MergetSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int mid = left + (right-left)/2;

	//������ ����
	MergetSort(v, left, mid);
	MergetSort(v, mid+1, right);

	//��ġ��
	MergeResult(v, left, mid, right);
}