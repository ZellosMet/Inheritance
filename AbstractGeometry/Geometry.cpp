#include<Windows.h>
#include<iostream>
#include<ctime>

namespace Geometry
{
	enum Color
	{
	red = 0x000000FF,
	green = 0x00FF000,
	blue = 0x00FF0000,
	yelloy = 0x00FFFF00,

	console_red = 0xCC, //0x - шестнадцаричиный
	console_green = 0xAA,
	console_blue = 0x99,
	console_defauit = 0x07
	};
#define SHAPE_TAKE_PARAMETERSINT int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERSINT start_x, start_y, line_width, color
	class Shape
	{
		static const int MIN_START_X = 10;
		static const int MIN_START_Y = 10;
		static const int MAX_START_X = 500;
		static const int MAX_START_Y = 400;
		static const int MIN_LINE_WIDTH = 5;
		static const int MAX_LINE_WIDTH = 25;		
	protected:
		int start_x;
		int start_y;
		int line_width;
		Color color;
	public:
		Shape(SHAPE_TAKE_PARAMETERSINT) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}
		void set_start_x(int start_x)
		{
			if (start_x < MIN_START_X) start_x = MIN_START_X;
			if (start_x < MAX_START_X) start_x = MAX_START_X;
			this->start_x = start_x;			
		}
		void set_start_y(int start_y)
		{
			if (start_y < MIN_START_Y) start_y = MIN_START_Y;
			if (start_y < MAX_START_Y) start_y = MAX_START_Y;
			this->start_y = start_y;			
		}
		void set_line_width(int line_width)
		{
			if (line_width < MIN_LINE_WIDTH) line_width = MIN_LINE_WIDTH;
			if (line_width < MAX_LINE_WIDTH) line_width = MAX_LINE_WIDTH;
			this->line_width = line_width;
		}
		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void get_draw()const = 0;
		virtual void info()const
		{
			std::cout << "Площать фигуры: " << get_area() << std::endl;
			std::cout << "Периметр фигуры: " << get_perimeter() << std::endl;
		}
	};
	class Rectangle : public Shape
	{
		static const int MIN_SIDE = 30;
		static const int MAX_SIDE = 500;
		double side1;
		double side2;
	public:
		double get_length()const
		{
			return side1;
		}
		double get_width()const
		{
			return side2;
		}
		void set_length(double side1)
		{
			if (side1 < MIN_SIDE) side1 = MIN_SIDE;
			if (side1 > MAX_SIDE) side1 = MAX_SIDE;
			this->side1 = side1;
		}
		void set_width(double side2)
		{
			if (side2 < MIN_SIDE) side2 = MIN_SIDE;
			if (side2 > MAX_SIDE) side2 = MAX_SIDE;
			this->side2 = side2;
		}
		Rectangle(double side1, double side2, SHAPE_TAKE_PARAMETERSINT) : Shape(SHAPE_GIVE_PARAMETERSINT)
		{
			set_length(side1);
			set_width(side2);
		}
		~Rectangle() {}
		double get_area()const override
		{
			return side1 * side2;
		}
		double get_perimeter()const override
		{
			return (side1 + side2) * 2;
		}
		void get_draw()const override
		{
			HWND hwnd = GetConsoleWindow(); //получаем окно консоли
			HDC hdc = GetDC(hwnd); //создаём контекс устройства
			HPEN hPen = CreatePen(PS_SOLID, 5, color); //карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color); //кисть заливает цветом фигуру
			//Выбираем чем и на чём будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			// Рисуем фигуру
			::Rectangle(hdc, start_x, start_y, start_x+side1, start_y + side2);

			//Очищаем память
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Сторона1: " << side1 << std::endl;
			std::cout << "Сторона2: " << side2 << std::endl;
			Shape::info();
		}
	};
	class Square : public Rectangle
	{
	public:
		Square(double side, SHAPE_TAKE_PARAMETERSINT) : Rectangle(side, side, SHAPE_GIVE_PARAMETERSINT) {}
		~Square() {}
	};
/*
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
*/
}
//#define TEST

void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "");

	Geometry::Square square(50, 300, 300, 5, Geometry::Color::red);
	square.info();
	square.get_draw();
	std::cout << std::endl;

	Geometry::Rectangle rectangle(150, 100, 300, 500, 5, Geometry::Color::blue);
	rectangle.info();
	rectangle.get_draw();
	std::cout << std::endl;

#ifdef TEST

	Triangle triangle(5, 5, Color::console_green);
	std::cout << "Длина основания треугольника: " << triangle.get_base() << std::endl;
	std::cout << "Высота треугольника: " << triangle.get_height() << std::endl;
	std::cout << "Площадь треугольника: " << triangle.get_area() << std::endl;
	std::cout << "Периметр треугольника: " << triangle.get_perimeter() << std::endl;
	triangle.get_draw();
	std::cout << std::endl;


	Circle circle(4, Color::console_red);
	std::cout << "Радиус круга: " << circle.get_radius() << std::endl;
	std::cout << "Площадь круга: " << circle.get_area() << std::endl;
	std::cout << "Периметр круга: " << circle.get_perimeter() << std::endl;
	circle.get_draw();
#endif	

	
}