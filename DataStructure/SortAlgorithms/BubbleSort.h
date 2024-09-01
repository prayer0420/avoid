#pragma once
#include <iostream>
#include <vector>
using namespace std;

//void Swap(int& a, int& b)
//{
//	int temp = a;
//	a = b;
//	b = temp;
//}

void BubbleSort(vector<int>& v)
{
	int size = v.size();
	for (int i = 0; i < size-1; i++)
	{
		for (int j = 0; j < size-1-i; j++)
		{
			if (v[j] > v[j + 1])
			{
				Swap(v[j], v[j + 1]);
			}
		}
	}
}

void SelectionSort(vector<int>& v)
{
	int size = v.size();
	for (int i = 0; i < size-1; i++)
	{
		int minIdx = i;
		for (int j = i+1; j < size; j++)
		{
			if (v[j] < v[minIdx])
			{
				minIdx = j;
			}
		}
		if(i != minIdx)
			Swap(v[i],v[minIdx]);
	}
}

void InsertionSort(vector<int>& v)
{
	int size = v.size();
	for (int i = 1; i < size; i++)
	{
		int key = v[i];
		int j = i - 1; 
		while(v[j] > key && j>=0)
		{
			v[j+1] = v[j];
			j--;
		}
		v[j+1] = key;
	}
}
