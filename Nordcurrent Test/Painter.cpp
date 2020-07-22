#include "Painter.h"

Painter::Painter(void)
{
	refresh();
}

// ������ �����
void Painter::refresh()
{
	for (int i = 0; i < Painter::HEIGHT; i++)
		for (int j = 0; j < Painter::WIDTH; j++)
			map[i][j] = false;

	// �������� ������ ������, ����� ����� ���� ���������� ������������ ������ � ���������� ������� ����
	for (int j = 0; j < Painter::WIDTH; j++)
		map[Painter::HEIGHT][j] = true;
}

bool Painter::getValue(int x, int y) const
{
	return map[y][x];
}

// ��������� �� �������� � �����
bool Painter::checkCollision(Tetramino &t) const
{
	// ���� ������ ����� ��������� � �������� ����, ������� ���������� (���������� true)
	// ��������� �� ��� ���, ���� ������� �� ���������� � ������������: 
	// ��������� ���� ��� ������� ��������� (���������� false)	

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (t.getValue(j, i) == true)
			{
				int x = t.getX() + j - 1;
				int y = t.getY() + i;
				if (x < 0 || x >= Painter::WIDTH || y < 0 || y >= Painter::HEIGHT)
					return true;
				if (t.getValue(j, i) == map[y][x])
					return true;
			}
		}
	return false;
}

void Painter::merge(Tetramino &t)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (t.getValue(j, i) == true)
			{
				int x = t.getX() + j - 1;
				int y = t.getY() + i;
				if (x >= 0 || x < Painter::WIDTH || y >= 0 || y < Painter::HEIGHT)
					map[y][x] = map[y][x] | t.getValue(j, i);
			}
		}
}

void Painter::killLines()
{
	for (int i = 0; i < Painter::HEIGHT; i++)
	{
		bool solid = true;
		for (int j = 0; j < Painter::WIDTH; j++)
			solid &= map[i][j];
		if (solid == true)
			killLine(i);
	}
}

void Painter::killLine(int k)
{
	// �������� ������
	for (int i = k - 1; i >= 0; i--)
		for (int j = 0; j < Painter::WIDTH; j++)
			map[i + 1][j] = map[i][j];

	// ������� ������ ������ � ���������� ����
	for (int j = 0; j < Painter::WIDTH; j++)
		map[0][j] = false;
}