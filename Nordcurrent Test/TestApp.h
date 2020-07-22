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

	// Переопределяем из BaseApp
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);

	// Собственные методы класса TestApp
	void turn();
	void draw();
	void drawFilledArea();
	void drawTetramino();
	void drawNextTetramino();

private:

	Tetramino tetramino;			// текущая фигура
	Tetramino next_tetramino;		// следующая фигура
	Painter filled_area;			// заполненная область
	int counter;					// счетчик
	static const int DELAY = 20;	// задержка
};
