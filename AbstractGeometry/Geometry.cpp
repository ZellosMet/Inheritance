#include<Windows.h>
#include<iostream>
#include<ctime>

enum Color
{
	console_red = 0xCC, //0x - шестнадцаричиный
	console_green = 0xAA,
	console_blue = 0x99,
	console_defauit = 0x07
};

enum RandShape
{
	square = 1,
	triangle,
	rectangl,
	circle
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
				std::cout << "* ";
			std::cout << std::endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_defauit);
	}
};
class Triangle : public Shape
{
	static const int MIN_BASE = 3;
	static const int MAX_BASE = 50;
	static const int MIN_HEIGHT = 3;
	static const int MAX_HEIGHT = 50;
	double base;
	double height;
public:
	double get_base()const
	{
		return base;
	}
	double get_height()const
	{
		return height;
	}
	void set_base(double base)
	{
		if (base < MIN_BASE) base = MIN_BASE;
		if (base > MAX_BASE) base = MAX_BASE;
		this->base = base;
	}
	void set_height(double height)
	{
		if (height < MIN_BASE) height = MIN_BASE;
		if (height > MAX_BASE) height = MAX_BASE;
		this->height = height;
	}
	Triangle(double base, double height, Color color) : Shape(color)
	{
		set_base(base);
		set_height(height);
	}
	~Triangle() {}
	double get_area()const override
	{
		return height / 2 * base;
	}
	double get_perimeter()const override
	{
		return 2 * height + base;
	}
	void get_draw()const override
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < height; i++)
		{
			for (int j = i; j < height - 1; j++)
				std::cout << "  ";
			SetConsoleTextAttribute(hConsole, color);
			std::cout << "* ";
			for (int j = 0; j < i * 2; j++)
				std::cout << "* ";
			std::cout << std::endl;
			SetConsoleTextAttribute(hConsole, Color::console_defauit);
		}
	}
};

class Rectangl : public Shape
{
	static const int MIN_LENGTH = 3;
	static const int MAX_LENGTH = 50;
	static const int MIN_WIDTH = 3;
	static const int MAX_WIDTH = 50;
	double length;
	double width;
public:
	double get_length()const
	{
		return length;
	}
	double get_width()const
	{
		return width;
	}
	void set_length(double length)
	{
		if (length < MIN_LENGTH) length = MIN_LENGTH;
		if (length > MAX_LENGTH) length = MAX_LENGTH;
		this->length = length;
	}
	void set_width(double width)
	{
		if (width < MIN_WIDTH) width = MIN_WIDTH;
		if (width > MAX_WIDTH) width = MAX_WIDTH;
		this->width = width;
	}
	Rectangl(double width, double length, Color color) : Shape(color)
	{
		set_length(length);
		set_width(width);
	}
	~Rectangl() {}
	double get_area()const override
	{
		return length * width;
	}
	double get_perimeter()const override
	{
		return length * 2 + width * 2;
	}
	void get_draw()const override
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, color);
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < length; j++)
				std::cout << "* ";
			std::cout << std::endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_defauit);
	}
};

class Circle : public Shape
{
	static const int MIN_RADIUS = 4;
	static const int MAX_RADIUS = 50;
	static const double PI;

	double radius;
public:
	double get_radius()const
	{
		return radius;
	}
	void set_radius(double radius)
	{
		if (radius < MIN_RADIUS) radius = MIN_RADIUS;
		if (radius > MAX_RADIUS) radius = MAX_RADIUS;
		this->radius = radius;
	}
	Circle(double radius, Color color) : Shape(color)
	{
		set_radius(radius);
	}
	~Circle() {}
	double get_area()const override
	{
		return PI * radius * radius;
	}
	double get_perimeter()const override
	{
		return PI * radius * 2;
	}
	void get_draw()const override
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < radius; i++)
		{
			for (int j = i; j < radius - 1; j++) std::cout << "  ";
			SetConsoleTextAttribute(hConsole, color);
			std::cout << "* ";
			for (int j = 0; j < i * 2; j++) std::cout << "  "; std::cout << "* ";
			SetConsoleTextAttribute(hConsole, Color::console_defauit);
			std::cout << std::endl;
		}
		for (int i = 0; i < radius; i++)
		{
			for (int j = 0; j <= i - 1; j++) std::cout << "  ";
			SetConsoleTextAttribute(hConsole, color);
			std::cout << "* ";
			for (int j = 0; j < (radius - 1 - i) * 2; j++) std::cout << "  ";
			std::cout << "* ";
			SetConsoleTextAttribute(hConsole, Color::console_defauit);
			std::cout << std::endl;
		}
	}
};

double const Circle::PI = 3.14;

//#define TEST

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "");

#ifdef TEST
	Square square(5, Color::console_red);
	std::cout << "Длина стороны квадрата: " << square.get_side() << std::endl;
	std::cout << "Площадь квадрата: " << square.get_area() << std::endl;
	std::cout << "Периметр квадрата: " << square.get_perimeter() << std::endl;
	square.get_draw();
	std::cout << std::endl;

	Triangle triangle(5, 5, Color::console_green);
	std::cout << "Длина основания треугольника: " << triangle.get_base() << std::endl;
	std::cout << "Высота треугольника: " << triangle.get_height() << std::endl;
	std::cout << "Площадь треугольника: " << triangle.get_area() << std::endl;
	std::cout << "Периметр треугольника: " << triangle.get_perimeter() << std::endl;
	triangle.get_draw();
	std::cout << std::endl;

	Rectangl rectangl(5, 8, Color::console_blue);
	std::cout << "Длина прямоугольника: " << rectangl.get_length() << std::endl;
	std::cout << "Ширина прямоугольника: " << rectangl.get_width() << std::endl;
	std::cout << "Площадь прямоугольника: " << rectangl.get_area() << std::endl;
	std::cout << "Периметр прямоугольника: " << rectangl.get_perimeter() << std::endl;
	rectangl.get_draw();
	std::cout << std::endl;

	Circle circle(4, Color::console_red);
	std::cout << "Радиус круга: " << circle.get_radius() << std::endl;
	std::cout << "Площадь круга: " << circle.get_area() << std::endl;
	std::cout << "Периметр круга: " << circle.get_perimeter() << std::endl;
	circle.get_draw();
#endif

	int shape = rand() % 4 + 1;
	Color rand_color[] = { Color::console_red, Color::console_green, Color::console_blue };
	int color_shape = rand() % 3 + 1;
	switch (shape)
	{
	case RandShape::square:
	{
		Square square((rand() % 10), rand_color[color_shape]);
		std::cout << "Длина стороны квадрата: " << square.get_side() << std::endl;
		std::cout << "Площадь квадрата: " << square.get_area() << std::endl;
		std::cout << "Периметр квадрата: " << square.get_perimeter() << std::endl;
		square.get_draw();
		break;
	}
	case RandShape::triangle:
	{
		Triangle triangle((rand() % 10), (rand() % 10), rand_color[color_shape]);
		std::cout << "Длина основания треугольника: " << triangle.get_base() << std::endl;
		std::cout << "Высота треугольника: " << triangle.get_height() << std::endl;
		std::cout << "Площадь треугольника: " << triangle.get_area() << std::endl;
		std::cout << "Периметр треугольника: " << triangle.get_perimeter() << std::endl;
		triangle.get_draw();
		break;
	}
	case RandShape::rectangl:
	{
		Rectangl rectangl((rand() % 10), (rand() % 10), rand_color[color_shape]);
		std::cout << "Длина прямоугольника: " << rectangl.get_length() << std::endl;
		std::cout << "Ширина прямоугольника: " << rectangl.get_width() << std::endl;
		std::cout << "Площадь прямоугольника: " << rectangl.get_area() << std::endl;
		std::cout << "Периметр прямоугольника: " << rectangl.get_perimeter() << std::endl;
		rectangl.get_draw();
		break;
	}
	case RandShape::circle:
	{
		Circle circle((rand() % 10), rand_color[color_shape]);
		std::cout << "Радиус круга: " << circle.get_radius() << std::endl;
		std::cout << "Площадь круга: " << circle.get_area() << std::endl;
		std::cout << "Периметр круга: " << circle.get_perimeter() << std::endl;
		circle.get_draw();
		break;
	}
	}
}