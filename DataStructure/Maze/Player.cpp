#include "pch.h"
#include "Player.h"
#include "Board.h"

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	//CalculatePath_RightHand();
	//CalculatePath_BFS();
	CalculatePath_AStar();
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
		return;

	_sumTick += deltaTick;
	if (_sumTick >= 100)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}

void Player::CalculatePath_RightHand()
{
	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	// ������
	Pos dest = _board->GetExitPos();

	Pos front[4] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(1, 0), // DOWN
		Pos(0, 1), // RIGHT
	};

	while (pos != dest)
	{
		// 1. ���� �ٶ󺸴� ������ ��������, ���������� �� �� �ִ��� Ȯ��
		int32 newDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[newDir]))
		{
			// ������ �������� 90�� ȸ��
			_dir = newDir;

			// ������ �� �� ����
			pos += front[_dir];

			// ���
			_path.push_back(pos);
		}
		// 2. ���� �ٶ󺸴� ������ �������� ������ �� �ִ��� Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			// ������ �� �� ����
			pos += front[_dir];

			// ���
			_path.push_back(pos);
		}
		else
		{
			// 3. ���� �������� 90�� ȸ��
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}
}

void Player::CalculatePath_BFS()
{
	Pos pos = _pos;
	Pos dest = _board->GetExitPos(); // ������

	Pos front[4] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(1, 0), // DOWN
		Pos(0, 1), // RIGHT
	};

	const int32 size = _board->GetSize();
	vector<vector<bool>> discovered(size, vector<bool>(size, false)); //ã�Ҵ��� 

	// extra)
	// parent[y][x] = pos -> (y, x)�� Pos�� ���� �߰ߵ�.
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	queue<Pos> q; //ť 
	q.push(pos);
	discovered[pos.y][pos.x] = true; //ó���� �� ��
	parent[pos.y][pos.x] = pos; //ó�� �θ�� �ڱ� �ڽ�

	while (q.empty() == false)
	{
		
		pos = q.front();
		q.pop();

		// ������ ����
		if (pos == dest)
			break;

		//������������ �����¿� ��ȸ�ϸ鼭 ��� ã��
		for (int32 dir = 0; dir < DIR_COUNT; dir++)
		{
			Pos nextPos = pos + front[dir];
			
			// �� �� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false)
				continue;

			// �̹� �ٸ� ��ο� ���� �߰��� �������� Ȯ��
			if (discovered[nextPos.y][nextPos.x])
				continue;

			//����������� ���� �ִ� ��, �߰ߵ��� �ʴ� ��
			
			q.push(nextPos);
			discovered[nextPos.y][nextPos.x] = true; //�̹� �߰��� ���̶� üũ
			parent[nextPos.y][nextPos.x] = pos;  // �θ� ����
		}
	}

	_path.clear();

	//�Ųٷ� �Ž��� �ö󰡱�
	pos = dest;

	while (true)
	{
		_path.push_back(pos);

		// ������(�ڱ��ڽ��� �θ��� ���� �������ۿ� ����)
		if (pos == parent[pos.y][pos.x])
			break;

		//�ڱ⸦ �θ��������� ������Ʈ(��� �Ųٷ� ��)
		pos = parent[pos.y][pos.x];
	}


	//���� ������ ������ �� �Ųٷ� �̵��ϱ�

	/*vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
		temp[i] = _path[_path.size() - 1 - i]; //�� ��Һ��� �ֱ�

	_path = temp;*/

	std::reverse(_path.begin(), _path.end());
}

// BFS, ���ͽ�Ʈ��� �������� ������ ����!
// ��Ÿũ����Ʈó�� �Ȱ�ó��?

// ä��
// - �Ա��������� �󸶳� ������ �ִ���?
// - �ⱸ�������� �󸶳� ������ �ִ���?

struct PQNode
{
	PQNode(int32 f, int32 g, Pos pos) : f(f), g(g), pos(pos) { }

	bool operator<(const PQNode& other) const { return f < other.f; }
	bool operator>(const PQNode& other) const { return f > other.f; }

	int32 f; // f = g + h
	int32 g;
	Pos pos;
};

// A* -> Dijikstra -> BFS -> Graph
// PQ
void Player::CalculatePath_AStar()
{
	// F = G + H
	// F = ���� ����(���� ���� ����)
	// G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���
	// H = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ���

	Pos start = _pos;
	Pos dest = _board->GetExitPos(); // ������

	Pos front[] =
	{
		Pos(-1, 0), // UP
		Pos(0, -1), // LEFT
		Pos(1, 0), // DOWN
		Pos(0, 1), // RIGHT
		Pos(-1, -1), // UP_LEFT
		Pos(1, -1), // DOWN_LEFT
		Pos(1, 1), // DOWN_RIGHT
		Pos(-1, 1), // UP_RIGHT
	};

	int32 cost[] =
	{
		10,
		10,
		10,
		10,
		14,
		14,
		14,
		14
	};

	const int32 size = _board->GetSize();

	// best[y][x] -> ���ݱ��� (y,x)�� ���� ���� ���� ��� (���� ���� ����)
	vector<vector<int32>> best(size, vector<int32>(size, INT32_MAX));

	// ClosedList -> closed[y][x] -> (y, x)�� �湮�� �ߴ��� ����
	// Option) ��� best�� �Ǻ� ����
	vector<vector<bool>> closed(size, vector<bool>(size, false));

	// �θ� ���� �뵵
	vector<vector<Pos>> parent(size, vector<Pos>(size, Pos(-1, -1)));

	// 1) ���� �ý��� ����
	// 2) �ڴʰ� �� ���� ��ΰ� �߰ߵ� �� ���� -> ���� ó��!

	// OpenList : ���ݱ��� �߰ߵ� ���
	priority_queue<PQNode, vector<PQNode>, greater<PQNode>> pq;

	// �ʱⰪ
	{
		int32 g = 0;
		int32 h = 10 * (abs(dest.y - start.y) + abs(dest.x - start.x));

		pq.push(PQNode(g + h, g, start));
		best[start.y][start.x] = g + h;
		parent[start.y][start.x] = start;
	}

	while (pq.empty() == false)
	{
		// ���� ���� �ĺ��� ã�´�
		PQNode node = pq.top();
		pq.pop();

		// ������ ��ǥ�� ���� ��η� ã�Ƽ�
		// �� ���� ��η� ���ؼ� �̹� �湮(closed)�� ��� ��ŵ
		if (closed[node.pos.y][node.pos.x])
			continue;
		// �ⲯ ����ߴ��ϸ�. ������ �� ����� �ĺ��� �ִ�?
		if (best[node.pos.y][node.pos.x] < node.f)
			continue;

		// �湮
		closed[node.pos.y][node.pos.x] = true;

		// �������� ���������� �ٷ� ����
		if (node.pos == dest)
			break;

		for (int32 dir = 0; dir < 8; dir++)
		{
			Pos nextPos = node.pos + front[dir];
			// �� �� �ִ� ������ �´��� Ȯ��
			if (CanGo(nextPos) == false)
				continue;
			if (closed[nextPos.y][nextPos.x])
				continue;

			int32 g = node.g + cost[dir];
			int32 h = 10 * (abs(dest.y - nextPos.y) + abs(dest.x - nextPos.x));

			// �ٸ� ��ο��� �� ���� ���� ã������ ��ŵ
			if (best[nextPos.y][nextPos.x] <= g + h)
				continue;

			// ���� ����
			best[nextPos.y][nextPos.x] = g + h;
			pq.push(PQNode(g + h, g, nextPos));
			parent[nextPos.y][nextPos.x] = node.pos;
		}
	}

	_path.clear();
	Pos pos = dest;

	while (true)
	{
		_path.push_back(pos);

		// ������
		if (pos == parent[pos.y][pos.x])
			break;

		pos = parent[pos.y][pos.x];
	}

	/*vector<Pos> temp(_path.size());
	for (int i = 0; i < _path.size(); i++)
		temp[i] = _path[_path.size() - 1 - i];

	_path = temp;*/

	std::reverse(_path.begin(), _path.end());
}
