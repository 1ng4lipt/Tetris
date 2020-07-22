#pragma once

#include "Tetramino.h"

class Painter
{
public:

	// C-tor
	Painter();

	// D-tor
	~Painter() {};

	enum { HEIGHT = 20, WIDTH = 15 };

	bool getValue(int x, int y)			const;
	bool checkCollision(Tetramino &t)	const;

	void merge(Tetramino &t);
	void killLines();
	void killLine(int k);
	void refresh();

private:
	// HEIGHT + 2 ��� ��������� ������� ��� ���������� �������

	// �� ����� map - ��� ����� �������� ����, ������ ���� �� 2 �������
	bool map[HEIGHT + 2][WIDTH];
};
