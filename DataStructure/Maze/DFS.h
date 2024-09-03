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

//발견한 목록
vector<bool> discovered;

void CreatGraph()
{
	vertices.resize(6);

	//인접리스트
	adjacent = vector<vector<int>>(6);
	adjacent[0] = { 1,3 };
	adjacent[1] = { 0,2,3 };
	adjacent[3] = { 4 };
	adjacent[5] = { 4 };

	//인접 행렬
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
	//ex) 누구에 의해 발견되었는지?
	vector<int> parent(6, -1);
	//ex) 시작점에서 얼만큼 떨어져 있는지?
	vector<int> dist(6, -1);

	queue<int> q;
	q.push(here);
	discovered[here] = true;

	//처음에 부모는 자기자신
	parent[here] = here;
	dist[here] = 0; //처음은 시작점으로 0

	while (q.empty() == false)
	{
		//방문 및 인접한 노드 찾기위해 큐에서 꺼내고 값을 받아놓기
		here = q.front();
		q.pop();

		//방문 도장
		cout << "Visited: " << here << endl;

		//인접한 정점 찾기
		int size = adjacent[here].size();
		for (int i = 0; i < size; i++)
		{
			//인접한 다음 정점
			int there = adjacent[here][i];
			//인접한 다음 정점이 이미 발견한 곳이라면 스킵~
			if (discovered[there])
				continue;

			//여기까지 왔으면 발견하지 않은 정점이니까 큐에 넣기
			q.push(there);
			//이미 발견한곳이라고 체크
			discovered[there] = true;
			//부모
			parent[there] = here;
			//거리 (각 정점간의 거리를 1로 봤을 때)
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

