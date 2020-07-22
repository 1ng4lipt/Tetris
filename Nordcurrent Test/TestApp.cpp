#include "TestApp.h"

TestApp::TestApp() : Parent(30, 30)
{
	// Инициализируем tetramino, next_tetramino, filled_area через 
	// конструкторы их классов

	tetramino = Tetramino(rand() % 5, 8, 1, 0);
	next_tetramino = Tetramino(rand() % 5, 8, 1, 0);
	filled_area = Painter();
	counter = 1000;				// дополнительно при создании объектов и игрового поля инициализируем счетчик
}

/* ========== ПЕРЕОПРЕДЕЛЯЕМ МЕТОДЫ ИЗ BaseApp ========== */

// Обработчик нажатий на кнопки
void TestApp::KeyPressed(int btnCode)
{
	Tetramino t = tetramino;

	// Движение влево при нажатии кнопки "А"
	if (btnCode == 75)
		t.move(-1, 0);

	// Движение вправо при нажатии кнопки "D"
	else if (btnCode == 77)
		t.move(1, 0);

	// Движение вниз при нажатии кнопки "S"
	else if (btnCode == 80)
		t.setSpeed(DELAY);

	// Вращение фигурки при нажатии кнопки "Space"
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
	draw();											// отрисовали
	if (counter > DELAY / tetramino.getSpeed())		// задержали ход
	{
		counter = 0;
		turn();										// сделали ход
	}
	counter++;
}


/* ========== РЕАЛИЗОВЫВАЕМ МЕТОДЫ ИЗ TestApp ========== */

// Отрисовка заполненной области
void TestApp::drawFilledArea()
{
	// Устанавливаем границы отрисовочной области и символ для отрисовки границы

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

	// Отрисовка заполненной области
	for (int i = 1; i <= Painter::HEIGHT; i++)
		for (int j = 1; j <= Painter::WIDTH; j++)
		{
			if (filled_area.getValue(j - 1, i - 1) == true)
				SetChar(j * 1, i * 1, '*');			// '*' для объекта
			else
				SetChar(j * 1, i * 1, '.');			// '.' для поля
		}
}

void TestApp::drawTetramino()
{
	// Получаем координаты
	int x = tetramino.getX();
	int y = tetramino.getY();

	// Рисуем
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (tetramino.getValue(j, i) == true)
				SetChar((x + j) * 1, (y + i) * 1, '*');
}

// Отрисовка подсказки след фигурки

void TestApp::drawNextTetramino()
{
	// Границы области подсказки следующей фигуры по горизонтали
	for (int j = Painter::WIDTH + 2; j < Painter::WIDTH + 9; j++)
	{
		SetChar(j * 1, 0, '#');
		SetChar(j * 1, 5, '#');
	}

	// Границы области подсказки следующей фигуры по вертикали
	for (int i = 0; i < 5; i++)
		SetChar(Painter::WIDTH + 8, i * 1, '#');

	// Пустые поля области подсказки следующей фигуры
	for (int i = 1; i < 5; i++)
		for (int j = Painter::WIDTH + 2; j < Painter::WIDTH + 8; j++)
			SetChar(j * 1, i * 1, '.');

	// Отрисовка следующей фигуры
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
	// Перемещаем текущую фигуру вниз
	Tetramino t = tetramino;
	t.move(0, 1);

	// При столкновении с другими фигурами (заполненной область)
	if (filled_area.checkCollision(t) == false)
		tetramino = t;

	// Если фигура еще может "идти" вниз
	else
	{
		filled_area.merge(tetramino);						// добавляем фигуру к остальным
		filled_area.killLines();							// удаляем заполненные линии, если такие есть

		next_tetramino = Tetramino(rand() % 5, 8, 1, 0);	// создаем новую фигурку
		tetramino = next_tetramino;

		if (filled_area.checkCollision(tetramino))			// если новая фигура не может "идти" ниже из-за заполненности игрового поля
			filled_area.refresh();							// начинаем новую игру
	}
}