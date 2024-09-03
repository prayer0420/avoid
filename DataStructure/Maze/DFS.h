#pragma once
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


struct Vertex
{
	//int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

//�߰��� ���
vector<bool> discovered;

void CreatGraph()
{
	vertices.resize(6);

	//��������Ʈ
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	//���� ���
	//adjacent = vector<vector<int>>
	//{
	//	{0,1,0,1,0,0},
	//	{1,0,1,1,0,0},
	//	{0,0,0,0,0,0},
	//	{0,0,0,0,1,0},
	//	{0,0,0,0,0,0},
	//	{0,0,0,0,1,0},
	//};

}

void BFS(int here)
{
	//ex) ������ ���� �߰ߵǾ�����?
	vector<int> parent(6, -1);
	//ex) ���������� ��ŭ ������ �ִ���?
	vector<int> dist(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	//ó���� �θ�� �ڱ��ڽ�
	parent[here] = here;
	dist[here] = 0; //ó���� ���������� 0

	while (q.empty() == false)
	{
		//�湮 �� ������ ��� ã������ ť���� ������ ���� �޾Ƴ���
		here = q.front();
		q.pop();

		//�湮 ����
		cout << "Visited: " << here << endl;

		//������ ���� ã��
		int size = adjacent[here].size();
		for (int i = 0; i < size; i++)
		{
			//������ ���� ����
			int there = adjacent[here][i];
			//������ ���� ������ �̹� �߰��� ���̶�� ��ŵ~
			if (discovered[there])
				continue;

			//������� ������ �߰����� ���� �����̴ϱ� ť�� �ֱ�
			q.push(there);
			//�̹� �߰��Ѱ��̶�� üũ
			discovered[there] = true;
			//�θ�
			parent[there] = here;
			//�Ÿ� (�� �������� �Ÿ��� 1�� ���� ��)
			dist[here] = dist[here] + 1;
		}
	}

}

void BFSAll()
{

	discovered = vector<bool>(6, false);

	for (int i = 0; i < 6; i++)
	{
		if (discovered[i] == false)
			BFS(i);
	}

}

int main()
{

	CreatGraph();
	discovered = vector<bool>(6, false);

	BFS(0);
}

