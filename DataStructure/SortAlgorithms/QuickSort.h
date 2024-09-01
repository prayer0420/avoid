#pragma once
#include <vector>
#include <cstdlib>  // rand() �Լ� ����� ���� ���
#include <ctime>    // srand() �Լ� ����� ���� ���
#include <stack>
using namespace std;

void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

//�ǹ��� �ǿ��� ��ҷ� ������ �� ��Ƽ�� ����(�������� ���ĵǾ��ִ� �迭 �� ���� �ð����⵵ ����)
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

// �������� �ε��� ���� �� �� �ε����� ���� ������ ���� �ǹ����� ������ �� ��Ƽ���� ����
int RandomPivotPartition(vector<int>& arr, int left, int right) 
{
	srand(time(0));
	// ���� �ǹ��ε��� ����
	int pivotIndex = left + rand() % (right - left + 1);  // left�� right ������ ���� �ε��� ����
	Swap(arr[pivotIndex], arr[right]);  // �������� ���õ� �ǹ��� ������ ��ҿ� ��ȯ

	int pivot = arr[right];  // ���� �ǹ��� ������ ��ҿ� ��ġ
	int i=left-1;  // i�� �ǹ����� ���� ��ҵ��� ������ �ε���.  ���

	for (int j = left; j < right; j++) 
	{
		// ���� ��Ұ� �ǹ����� ������ i�� ������Ű�� ��ȯ
		if (arr[j] < pivot) 
		{
			i++; //���
			Swap(arr[i], arr[j]);  
		}
	}

	Swap(arr[i + 1], arr[right]);  // �ǹ��� �ùٸ� ��ġ�� �̵�

	return i + 1;  // �ǹ��� ���� ��ġ�� ��ȯ
}

// ����� ����Ʈ �Լ�
void QuickSort(vector<int>& arr) 
{
	stack<int> partitionStack;

	// �ʱ� ������ ���ÿ� Ǫ��
	partitionStack.push(0);
	partitionStack.push(arr.size() - 1);

	while (!partitionStack.empty()) 
	{
		int end = partitionStack.top();
		partitionStack.pop();
		int start = partitionStack.top();
		partitionStack.pop();

		int partitionIndex = RandomPivotPartition(arr, start, end);

		// ���� �κ� �迭�� ���ÿ� Ǫ��
		if (partitionIndex - 1 > start) {
			partitionStack.push(start);
			partitionStack.push(partitionIndex - 1);
		}

		// ������ �κ� �迭�� ���ÿ� Ǫ��
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

