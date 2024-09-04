#include <iostream>


int map[6][6] =
{
	{0, 1, 1, 0, 0, 0},
	{0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0}
};

char value[6] = { 'E', 'A', 'U', 'R', 'Q', 'Y' };

struct Node
{
	int num;
	int level;
};

Node queue[7] = { {0,0} };
int head = 0;
int tail = 1;

int main()
{
	while (head != tail)
	{
		Node now = queue[head];
		std::cout << value[now.num] << std::endl;
		std::cout << "------------" << std::endl;

		for (int i = 0; i < 6; i++)
		{
			if (map[now.num][i] == 1)
			{
				queue[tail] = { i, now.level + 1 };
				tail++;
			}
		}

		head++;
	}

	return 0;
}