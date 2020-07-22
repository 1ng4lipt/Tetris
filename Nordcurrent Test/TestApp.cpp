#include "TestApp.h"

TestApp::TestApp() : Parent(30, 30)
{
	// �������������� tetramino, next_tetramino, filled_area ����� 
	// ������������ �� �������

	tetramino = Tetramino(rand() % 5, 8, 1, 0);
	next_tetramino = Tetramino(rand() % 5, 8, 1, 0);
	filled_area = Painter();
	counter = 1000;				// ������������� ��� �������� �������� � �������� ���� �������������� �������
}

/* ========== �������������� ������ �� BaseApp ========== */

// ���������� ������� �� ������
void TestApp::KeyPressed(int btnCode)
{
	Tetramino t = tetramino;

	// �������� ����� ��� ������� ������ "�"
	if (btnCode == 75)
		t.move(-1, 0);

	// �������� ������ ��� ������� ������ "D"
	else if (btnCode == 77)
		t.move(1, 0);

	// �������� ���� ��� ������� ������ "S"
	else if (btnCode == 80)
		t.setSpeed(DELAY);

	// �������� ������� ��� ������� ������ "Space"
	else if (btnCode == 32)
		t.rotate();

	if (filled_area.checkCollision(t) == false)
	{
		tetramino = t;
		drawFilledArea();
		drawTetramino();
	}
}

void TestApp::UpdateF(float deltaTime)
{
	draw();											// ����������
	if (counter > DELAY / tetramino.getSpeed())		// ��������� ���
	{
		counter = 0;
		turn();										// ������� ���
	}
	counter++;
}


/* ========== ������������� ������ �� TestApp ========== */

// ��������� ����������� �������
void TestApp::drawFilledArea()
{
	// ������������� ������� ������������ ������� � ������ ��� ��������� �������

	for (int j = 0; j < Painter::WIDTH + 2; j++)
	{
		SetChar(j * 1, 0, '#');
		SetChar(j * 1, (Painter::HEIGHT + 1), '#');
	}

	for (int i = 0; i < Painter::HEIGHT + 2; i++)
	{
		SetChar(0, i * 1, '#');
		SetChar((Painter::WIDTH + 1), i * 1, '#');
	}

	// ��������� ����������� �������
	for (int i = 1; i <= Painter::HEIGHT; i++)
		for (int j = 1; j <= Painter::WIDTH; j++)
		{
			if (filled_area.getValue(j - 1, i - 1) == true)
				SetChar(j * 1, i * 1, '*');			// '*' ��� �������
			else
				SetChar(j * 1, i * 1, '.');			// '.' ��� ����
		}
}

void TestApp::drawTetramino()
{
	// �������� ����������
	int x = tetramino.getX();
	int y = tetramino.getY();

	// ������
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (tetramino.getValue(j, i) == true)
				SetChar((x + j) * 1, (y + i) * 1, '*');
}

// ��������� ��������� ���� �������

void TestApp::drawNextTetramino()
{
	// ������� ������� ��������� ��������� ������ �� �����������
	for (int j = Painter::WIDTH + 2; j < Painter::WIDTH + 9; j++)
	{
		SetChar(j * 1, 0, '#');
		SetChar(j * 1, 5, '#');
	}

	// ������� ������� ��������� ��������� ������ �� ���������
	for (int i = 0; i < 5; i++)
		SetChar(Painter::WIDTH + 8, i * 1, '#');

	// ������ ���� ������� ��������� ��������� ������
	for (int i = 1; i < 5; i++)
		for (int j = Painter::WIDTH + 2; j < Painter::WIDTH + 8; j++)
			SetChar(j * 1, i * 1, '.');

	// ��������� ��������� ������
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (next_tetramino.getValue(j, i) == true)
				SetChar((j + Painter::WIDTH + 3) * 1, (i + 2) * 1, '*');
}


void TestApp::draw()
{
	drawFilledArea();
	drawTetramino();
	drawNextTetramino();
}

void TestApp::turn()
{
	// ���������� ������� ������ ����
	Tetramino t = tetramino;
	t.move(0, 1);

	// ��� ������������ � ������� �������� (����������� �������)
	if (filled_area.checkCollision(t) == false)
		tetramino = t;

	// ���� ������ ��� ����� "����" ����
	else
	{
		filled_area.merge(tetramino);						// ��������� ������ � ���������
		filled_area.killLines();							// ������� ����������� �����, ���� ����� ����

		next_tetramino = Tetramino(rand() % 5, 8, 1, 0);	// ������� ����� �������
		tetramino = next_tetramino;

		if (filled_area.checkCollision(tetramino))			// ���� ����� ������ �� ����� "����" ���� ��-�� ������������� �������� ����
			filled_area.refresh();							// �������� ����� ����
	}
}