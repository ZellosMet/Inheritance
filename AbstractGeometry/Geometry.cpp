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
		yelloy = 0x0000FFFF,

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
		static const int MAX_START_X = 600;
		static const int MAX_START_Y = 1000;
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
			if (start_x > MAX_START_X) start_x = MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y < MIN_START_Y) start_y = MIN_START_Y;
			if (start_y > MAX_START_Y) start_y = MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < MIN_LINE_WIDTH) line_width = MIN_LINE_WIDTH;
			if (line_width > MAX_LINE_WIDTH) line_width = MAX_LINE_WIDTH;
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
			HPEN hPen = CreatePen(PS_SOLID, line_width, color); //карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color); //кисть заливает цветом фигуру
			//Выбираем чем и на чём будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			// Рисуем фигуру
			::Rectangle(hdc, start_x, start_y, start_x + side1, start_y + side2);

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
		Circle(double radius, SHAPE_TAKE_PARAMETERSINT) : Shape(SHAPE_GIVE_PARAMETERSINT)
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
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x + radius, start_y + radius);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);

		}
		void info()const override
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Радиус: " << radius << std::endl;
			Shape::info();
		}
	};
	double const Geometry::Circle::PI = 3.14;

	class Triangle : public Shape
	{
		static const int MIN_SIDE1 = 4;
		static const int MAX_SIDE1 = 50;
		static const int MIN_SIDE2 = 4;
		static const int MAX_SIDE2 = 50;
		static const int MIN_SIDE3 = 4;
		static const int MAX_SIDE3 = 50;
		static const int MIN_ANGLE = 2;
		static const int MAX_ANGLE = 79;
	protected:
		double side1;
		double side2;
		double side3;
		double angle;
		static const int point = 3;
		POINT pt[point];
	public:
		double get_side1()const
		{
			return side1;
		}
		double get_side2()const
		{
			return side2;
		}
		double get_side3()const
		{
			return side3;
		}
		double get_angle()const
		{
			return angle;
		}
		void set_side1(double side1)
		{
			if (side1 < MIN_SIDE1) side1 = MIN_SIDE1;
			if (side1 > MAX_SIDE1) side1 = MAX_SIDE1;
			this->side1 = side1;
		}
		void set_side2(double side2)
		{
			if (side2 < MIN_SIDE2) side2 = MIN_SIDE2;
			if (side2 > MAX_SIDE2) side2 = MAX_SIDE2;
			this->side2 = side2;
		}
		void set_side3(double side3)
		{
			if (side3 < MIN_SIDE3) side3 = MIN_SIDE3;
			if (side3 > MAX_SIDE3) side3 = MAX_SIDE3;
			this->side3 = side3;
		}
		void set_angle(double angle)
		{
			if (angle < MIN_ANGLE) angle = MIN_ANGLE;
			if (angle > MAX_ANGLE) angle = MAX_ANGLE;
			this->angle = angle;
		}
		Triangle(double side1, double side2, double angle, SHAPE_TAKE_PARAMETERSINT) : Shape(SHAPE_GIVE_PARAMETERSINT)
		{
			set_side1(side1);
			set_side2(side2);
			set_side3(sqrt(pow(side1, 2) + pow(side2, 2) - 2 * side1 * side2 * (cos(angle * 0.0175))));
			set_angle(angle);
			pt[0].x = start_x;
			pt[0].y = start_y;
			(angle == 90) ? pt[1].x = start_x : (angle < 90) ? pt[1].x = start_x - side1 : pt[1].x = start_x + side1;
			(angle == 90) ? pt[1].y = start_y + side1 : (angle < 90) ? pt[1].y = start_y + side1 : pt[1].y = start_y + side1;
			(angle == 90) ? pt[2].x = pt[1].x + side2 : pt[2].x = pt[1].x + side2;
			(angle == 90) ? pt[2].y = pt[1].y : pt[2].y = pt[1].y;
		}
		~Triangle() {}
		double get_area()const override
		{
			double p = get_perimeter() / 2;
			return sqrt(fabs(p * (p - side1) * (p - side2) * (p - side3)));
		}
		double get_perimeter()const override
		{
			return side1 + side2 + side3;
		}
		void get_draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Polygon(hdc, pt, point);

			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Сторона1: " << side1 << std::endl;
			std::cout << "Сторона2: " << side2 << std::endl;
			std::cout << "Сторона3: " << side3 << std::endl;
			std::cout << "Угол: " << angle << std::endl;
			Shape::info();
		}
	};
	class AcuteTriangle : public Triangle
	{
	public:
		AcuteTriangle(double side1, double side2, double angle, SHAPE_TAKE_PARAMETERSINT) : Triangle(side1, side2, angle, SHAPE_GIVE_PARAMETERSINT) {}
		~AcuteTriangle() {}
	};
	class RightTriangle : public Triangle
	{
	public:
		RightTriangle(double side1, double side2, double angle, SHAPE_TAKE_PARAMETERSINT) : Triangle(side1, side2, angle, SHAPE_GIVE_PARAMETERSINT) {}
		~RightTriangle() {}
	};
	class ObtuseTriangle : public Triangle
	{
	public:
		ObtuseTriangle(double side1, double side2, double angle, SHAPE_TAKE_PARAMETERSINT) : Triangle(side1, side2, angle, SHAPE_GIVE_PARAMETERSINT) {}
		~ObtuseTriangle() {}
	};
}
void main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "");

	Geometry::AcuteTriangle acutetriangle(50, 60, 60, 550, 50, 5, Geometry::Color::green);
	acutetriangle.info();
	acutetriangle.get_draw();
	std::cout << std::endl;

	Geometry::RightTriangle righttriangle(50, 100, 90, 500, 200, 5, Geometry::Color::yelloy);
	righttriangle.info();
	righttriangle.get_draw();
	std::cout << std::endl;

	Geometry::ObtuseTriangle obtusetriangle(50, 60, 120, 500, 350, 5, Geometry::Color::red);
	obtusetriangle.info();
	obtusetriangle.get_draw();
	std::cout << std::endl;

	Geometry::Square square(50, 500, 500, 5, Geometry::Color::red);
	square.info();
	square.get_draw();
	std::cout << std::endl;

	Geometry::Rectangle rectangle(70, 50, 500, 630, 5, Geometry::Color::blue);
	rectangle.info();
	rectangle.get_draw();
	std::cout << std::endl;

	Geometry::Circle circle(50, 500, 750, 5, Geometry::Color::green);
	circle.info();
	circle.get_draw();
	std::cout << std::endl;
}