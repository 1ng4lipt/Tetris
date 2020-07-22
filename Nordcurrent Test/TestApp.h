#pragma once

#include "BaseApp.h"
#include "Tetramino.h"
#include "Painter.h"

class TestApp : public BaseApp
{
	typedef BaseApp Parent;

public:

	// C-tor
	TestApp();

	// �������������� �� BaseApp
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);

	// ����������� ������ ������ TestApp
	void turn();
	void draw();
	void drawFilledArea();
	void drawTetramino();
	void drawNextTetramino();

private:

	Tetramino tetramino;			// ������� ������
	Tetramino next_tetramino;		// ��������� ������
	Painter filled_area;			// ����������� �������
	int counter;					// �������
	static const int DELAY = 20;	// ��������
};
