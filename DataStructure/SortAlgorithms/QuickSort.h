#pragma once
#include <vector>
#include <cstdlib>  // rand() 함수 사용을 위한 헤더
#include <ctime>    // srand() 함수 사용을 위한 헤더
#include <stack>
using namespace std;

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//피벗을 맨왼쪽 요소로 지정한 후 파티션 수행(오름차순 정렬되어있는 배열 일 수록 시간복잡도 증가)
int LeftPivotPartition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int low = left + 1;
	int high = right;

	while (low <= high)
	{
		while (low <= right && pivot >= v[low])
			low++;
		while (high >= left+1 && pivot <= v[high])
			high--;
		if (low > high)
			Swap(v[low], v[high]);
	}

	Swap(v[left], v[high]);
	return high;

}

// 랜덤으로 인덱스 선정 후 그 인덱스를 가장 끝으로 보내 피벗으로 선정한 후 파티션을 수행
int RandomPivotPartition(vector<int>& arr, int left, int right) 
{
	srand(time(0));
	// 랜덤 피벗인덱스 선택
	int pivotIndex = left + rand() % (right - left + 1);  // left와 right 사이의 랜덤 인덱스 선택
	Swap(arr[pivotIndex], arr[right]);  // 랜덤으로 선택된 피벗을 마지막 요소와 교환

	int pivot = arr[right];  // 이제 피벗은 마지막 요소에 위치
	int i=left-1;  // i는 피벗보다 작은 요소들의 마지막 인덱스.  장미

	for (int j = left; j < right; j++) 
	{
		// 현재 요소가 피벗보다 작으면 i를 증가시키고 교환
		if (arr[j] < pivot) 
		{
			i++; //장미
			Swap(arr[i], arr[j]);  
		}
	}

	Swap(arr[i + 1], arr[right]);  // 피벗을 올바른 위치로 이동

	return i + 1;  // 피벗의 최종 위치를 반환
}

// 비재귀 퀵소트 함수
void QuickSort(vector<int>& arr) 
{
	stack<int> partitionStack;

	// 초기 범위를 스택에 푸시
	partitionStack.push(0);
	partitionStack.push(arr.size() - 1);

	while (!partitionStack.empty()) 
	{
		int end = partitionStack.top();
		partitionStack.pop();
		int start = partitionStack.top();
		partitionStack.pop();

		int partitionIndex = RandomPivotPartition(arr, start, end);

		// 왼쪽 부분 배열을 스택에 푸시
		if (partitionIndex - 1 > start) {
			partitionStack.push(start);
			partitionStack.push(partitionIndex - 1);
		}

		// 오른쪽 부분 배열을 스택에 푸시
		if (partitionIndex + 1 < end) {
			partitionStack.push(partitionIndex + 1);
			partitionStack.push(end);
		}
	}
}

void RecursiveQuickSort(vector<int>& v, int left, int right)
{
	if (left > right)
		return;

	int pivot = LeftPivotPartition(v, left, right);
	RecursiveQuickSort(v, left, pivot - 1);
	RecursiveQuickSort(v, pivot+1, right);
}

