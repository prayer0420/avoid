#pragma once
#include <vector>
#include <cstdlib>  // rand() �Լ� ����� ���� ���
#include <ctime>    // srand() �Լ� ����� ���� ���
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

	//�ǹ��� �߾�����
	void Centerquick(int* arr, int left, int right)
	{
		int pl = left;
		int pr = right;
		int pivot = arr[(pl + pr) / 2]; // �ǹ�

		while (pl <= pr)
		{
			while (arr[pl] < pivot)
				pl++;
			while (arr[pr] > pivot)
				pr--;

			if (pl <= pr) // �������� �ʾҴٸ�??
			{
				Swap(arr[pl], arr[pr]);
				pl++;
				pr--;
			}
		}

		// ���Ұ� �� �� �� ������ ��� ȣ��
		if (left < pr)
			Centerquick(arr, left, pr); // ���� ���� ���ȣ��
		if (pl < right)
			Centerquick(arr, pl, right); // ������ ���� ���ȣ��
	}

	void CenterquickSort(int* arr, int size)
	{
		Centerquick(arr, 0, size - 1); // �迭, ù��° �ε���, ������ �ε���
	}



	//�ǹ��� �� ��������
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

	//�ǹ��� �������� ���� �� ����������
	int RandomPivotPartition(vector<int>& arr, int left, int right)
	{
		srand(time(0));

		int pivotIdx = left + rand() % (right - left + 1); //left�� right������ ���� �ε��� ����
		Swap(arr[pivotIdx], arr[right]); //�������� ���õ� �ǹ��� ������ ��ҿ� ��ȯ

		int pivot = arr[right]; //���� �ǹ��� ������ ��ҿ� ��ġ
		int i = left - 1; //i�� �ǹ����� ���� ��żҵ��� ������ �ε��� , ��� 
		for (int j = 0; j < right; j++)
		{
			if (arr[j] < pivot)
			{
				i++;
				Swap(arr[i], arr[j]);
			}

		}
		Swap(arr[i + 1], arr[right]); //�ǹ��� �ùٸ� ��ġ�� �̵�
		return i + 1;
	}


	//����� Sort
	void QuickSort(vector<int>& arr)
	{
		stack<int> partitionStack;

		//�ʱ� ������ ���ÿ� Ǫ��
		partitionStack.push(0);
		partitionStack.push(arr.size() - 1);

		while (!partitionStack.empty())
		{
			int end = partitionStack.top();
			partitionStack.pop();
			int start = partitionStack.top();
			partitionStack.pop();

			int partitionidx = RandomPivotPartition(arr, start, end);

			//���� �κ� �迭�� ���ÿ� Ǫ��
			if (partitionidx - 1 > start)
			{
				partitionStack.push(start);
				partitionStack.push(partitionidx - 1);
			}
		}
	}

	//��� Sort
	void RecursiveQuickSort(vector<int>& v, int left, int right)
	{
		if (left > right)
			return;

		int pivot = LeftPivotPartition(v, left, right);
		RecursiveQuickSort(v, left, pivot - 1);
		RecursiveQuickSort(v, pivot + 1, right);
	}
}