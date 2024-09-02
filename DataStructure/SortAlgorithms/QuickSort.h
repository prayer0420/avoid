#pragma once
#include <vector>
#include <cstdlib>  // rand() 함수 사용을 위한 헤더
#include <ctime>    // srand() 함수 사용을 위한 헤더
#include <stack>
using namespace std;

namespace quicksort
{

	void Swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}

	//피벗을 중앙으로
	void Centerquick(int* arr, int left, int right)
	{
		int pl = left;
		int pr = right;
		int pivot = arr[(pl + pr) / 2]; // 피벗

		while (pl <= pr)
		{
			while (arr[pl] < pivot)
				pl++;
			while (arr[pr] > pivot)
				pr--;

			if (pl <= pr) // 교차되지 않았다면??
			{
				Swap(arr[pl], arr[pr]);
				pl++;
				pr--;
			}
		}

		// 원소가 한 개 일 때까지 재귀 호출
		if (left < pr)
			Centerquick(arr, left, pr); // 왼쪽 원소 재귀호출
		if (pl < right)
			Centerquick(arr, pl, right); // 오른쪽 원소 재귀호출
	}

	void CenterquickSort(int* arr, int size)
	{
		Centerquick(arr, 0, size - 1); // 배열, 첫번째 인덱스, 마지막 인덱스
	}



	//피벗을 맨 왼쪽으로
	int LeftPivotPartition(vector<int>& v, int left, int right)
	{
		int pivot = v[left];
		int low = left + 1;
		int high = right;

		while (low <= high)
		{
			while (low <= right && pivot >= v[low])
				low++;

			while (high >= left + 1 && pivot <= v[high])
				high--;

			if (low > high)
				swap(v[low], v[high]);
		}

		Swap(v[left], v[high]);
		return high;
	}

	//피벗을 랜덤으로 설정 후 오른쪽으로
	int RandomPivotPartition(vector<int>& arr, int left, int right)
	{
		srand(time(0));

		int pivotIdx = left + rand() % (right - left + 1); //left와 right사이의 랜덤 인덱스 선택
		Swap(arr[pivotIdx], arr[right]); //랜덤으로 선택된 피벗을 마지막 요소와 교환

		int pivot = arr[right]; //이제 피벗은 마지막 요소에 위치
		int i = left - 1; //i는 피벗보다 작은 요ㅕ소들의 마지막 인덱스 , 장미 
		for (int j = 0; j < right; j++)
		{
			if (arr[j] < pivot)
			{
				i++;
				Swap(arr[i], arr[j]);
			}

		}
		Swap(arr[i + 1], arr[right]); //피벗을 올바른 위치로 이동
		return i + 1;
	}


	//비재귀 Sort
	void QuickSort(vector<int>& arr)
	{
		stack<int> partitionStack;

		//초기 범위를 스택에 푸시
		partitionStack.push(0);
		partitionStack.push(arr.size() - 1);

		while (!partitionStack.empty())
		{
			int end = partitionStack.top();
			partitionStack.pop();
			int start = partitionStack.top();
			partitionStack.pop();

			int partitionidx = RandomPivotPartition(arr, start, end);

			//왼쪽 부분 배열을 스택에 푸시
			if (partitionidx - 1 > start)
			{
				partitionStack.push(start);
				partitionStack.push(partitionidx - 1);
			}
		}
	}

	//재귀 Sort
	void RecursiveQuickSort(vector<int>& v, int left, int right)
	{
		if (left > right)
			return;

		int pivot = LeftPivotPartition(v, left, right);
		RecursiveQuickSort(v, left, pivot - 1);
		RecursiveQuickSort(v, pivot + 1, right);
	}
}