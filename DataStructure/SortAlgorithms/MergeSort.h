#pragma once
#include <iostream>
#include <vector>
using namespace std;


void MergeResult(vector<int>& v, int left, int mid, int right)
{
	int leftIdx = left;
	int rightIdx = mid + 1;

	vector<int> temp;

	//실질적인 정복 전투
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


	//왼쪽이 먼저 끝났으면
	if (leftIdx > mid)
	{	//오른쪽 값들을 다 넣어줌
		while (rightIdx <= right)
		{
			temp.push_back(v[rightIdx]);
			rightIdx++;
		}
	}
	//오른쪽이 먼저 끝났으면
	else /*rightIdx > right*/
	{
		//왼쪽 값들을 다 넣어줌
		while (leftIdx<= mid)
		{
			temp.push_back(v[leftIdx]);
			leftIdx++;
		}
	}

	//temp를 원본 벡터에 옮기기;
	for (int i = 0; i < temp.size(); i++)
		v[left + i] = temp[i];
}


void IterativeMergeSort(vector<int>& v) 
{
	int n = v.size();
	//mergeSzie : 병합해야할 요소의 개수(크기)
	//mid = 병합해야할 2개의 요소 중에 왼쪽 요소의 끝 인덱스
	//end = 병합해야할 2개의 요소 중에 오른쪽 요소의 끝 인덱스
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

	//반으로 분할
	MergetSort(v, left, mid);
	MergetSort(v, mid+1, right);

	//합치기
	MergeResult(v, left, mid, right);
}