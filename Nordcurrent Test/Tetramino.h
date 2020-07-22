#pragma once

class Tetramino
{
public:

	// C-tor
	Tetramino() {};
	Tetramino(int shape, int x, int y, int angle);

	// D-tor
	~Tetramino() {};

	bool	getValue(int x, int y)	const;
	int		getSpeed()				const;
	int		getX()					const;
	int		getY()					const;

	void	move(int dx, int dy);
	void	setSpeed(int speed);
	void	rotate();

private:

	int shape;
	int angle;
	int speed;
	int x;
	int y;
};
