#include <iostream>
#include <vector>
#include "BubbleSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "HeapSort.h"




int main()
{
	vector<int> v{ 1,5,3,4,2 };
	cout << "Merge 전" << endl;
	for (auto vi : v)
	{
		cout << vi << " ";
	}
	cout << endl;
	cout << "=================================" << endl;

	////BubbleSort(v);
	////SelectionSort(v);
	////InsertionSort(v);
	////MergetSort(v, 0, v.size() - 1);
	////IterativeMergeSort(v);
	////QuickSort(v);
	////RecursiveQuickSort(v, 0, v.size() - 1);
	heapSort(v, v.size());

	cout << "Merge 후" << endl;
	for (auto vi : v)
	{
		cout << vi << " ";
	}
	cout << endl;

}

