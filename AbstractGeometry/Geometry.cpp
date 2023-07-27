#include<iostream> 
#include<Windows.h>

enum Color
{
	console_red = 0xCC, //0x - шестнадцаричиный
	console_green = 0xAA,
	console_blue = 0x99,
	console_defauit = 0x07
};

class Shape
{
protected:
	Color color;
public:
	Shape(Color color) : color(color) {}
	virtual ~Shape() {}
	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void get_draw()const = 0;

};

class Square : public Shape
{
	static const int MIN_SIDE = 2;
	static const int MAX_SIDE = 50;
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side < MIN_SIDE) side = MIN_SIDE;
		if (side > MAX_SIDE) side = MAX_SIDE;
		this->side = side;
	}
	Square(double side, Color color) : Shape(color)
	{
		set_side(side);
	}
	~Square() {}
	double get_area()const override
	{
		return side * side;
	}
	double get_perimeter()const override
	{
		return side * 4;
	}
	void get_draw()const override
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				std::cout << "* ";
			}
			std::cout << std::endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_defauit);
	}
};


void main()
{
	setlocale(LC_ALL, "");

	Square square(5, Color::console_red);
	std::cout << "Длина стороны квадрата: " << square.get_side() << std::endl;
	std::cout << "Площадь квадрата: " << square.get_area() << std::endl;
	std::cout << "Периметр квадрата: " << square.get_perimeter() << std::endl;
	square.get_draw();

}