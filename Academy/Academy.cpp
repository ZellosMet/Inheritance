#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>

char* Shrink(char* str);
std::string* Forming_an_array_of_fields(char str[]);
int Count_Space(char str[]);

class Human
{
	std::string last_name;
	std::string first_name;
	int age;
protected:
	static const int LAST_NAME_WIDTH = 12;
	static const int FIRST_NAME_WIDTH = 12;
	static const int AGE_WIDTH = 5;
	static int count; //Статическое объявление переменной
public:
	//Гетторы/Сетторы
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(const std::string& age)
	{
		this->age = std::stoi(age);
	}
	void set_age(int age)
	{
		this->age = age;
	}
	//Конструкторы/Деструкторы
	Human(const std::string& last_name, const std::string& first_name, const std::string& age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		std::cout << "HConstructor:\t" << this << std::endl;
	}
	Human(const std::string& last_name, const std::string& first_name, int age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		std::cout << "HConstructor:\t" << this << std::endl;
	}
	virtual ~Human()
	{
		count--;
		std::cout << "HDestructor:\t" << this << std::endl;
	}
	//Методы
	virtual std::ostream& print(std::ostream& os)const
	{
		return os << last_name << " " << first_name << " " << age;
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		ofs << typeid(*this).name() << "\t";
		ofs.width(LAST_NAME_WIDTH);
		ofs << std::left;
		ofs << last_name;
		ofs.width(FIRST_NAME_WIDTH);
		ofs << std::left;
		ofs << first_name;
		ofs.width(AGE_WIDTH);
		ofs << age;
		return ofs;
	}
};

int Human::count = 0; //Реализация статической переменной

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	obj.print(ofs);
	return ofs;
}

class Student :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int GROUP_WIDTH = 7;
	static const int RATING_WIDTH = 8;
	static const int ATTANDANCE_WIDTH = 8;
protected:
	std::string speciality;
	std::string group;
	int rating;
	int attandance;
public:
	//Гетторы/Сетторы
	const std::string& get_specialiry()const
	{
		return speciality;
	}
	const std::string& get_group()const
	{
		return group;
	}
	int get_rating()const
	{
		return rating;
	}
	int get_attandance()const
	{
		return attandance;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const std::string& group)
	{
		this->group = group;
	}
	void set_rating(const std::string& rating)
	{
		this->rating = std::stoi(rating);
	}
	void set_rating(int rating)
	{
		this->rating = rating;
	}
	void set_attandance(const std::string& attandance)
	{
		this->attandance = std::stoi(attandance);
	}
	void set_attandance(int attandance)
	{
		this->attandance = attandance;
	}
	//Конструкторы/Деструктор
	Student
	(const std::string& last_name, const std::string& first_name, const std::string& age,
		const std::string& speciality, const std::string& group = "", const std::string& rating = 0, const std::string& attandance = 0) // Введение универсального конструктора
		: Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attandance(attandance);
		std::cout << "SConstructor:\t" << this << std::endl;
	}
	Student
	(const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality, const std::string& group = "", int rating = 0, int attandance = 0) // Введение универсального конструктора
		: Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attandance(attandance);
		std::cout << "SConstructor:\t" << this << std::endl;
	}
	~Student()
	{
		std::cout << "SDestructor:\t" << this << std::endl;
	}
	//Методы
	std::ostream& print(std::ostream& os)const
	{
		Human::print(os) << " ";
		return os << "Speciality: " << speciality << "; " << "Group: " << group << "; " << "Rating: " << rating << "; " << "Attandance: " << attandance << ";";
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(GROUP_WIDTH);
		ofs << group;
		ofs.width(RATING_WIDTH);
		ofs << rating;
		ofs.width(ATTANDANCE_WIDTH);
		ofs << attandance;
		return ofs;
	}
};

class Teacher : public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int EXPERIENCE_WIDTH = 5;
	std::string speciality;
	int experience;
public:
	//Гетторы/Сетторы
	const std::string& get_speciality()const
	{
		return speciality;
	}
	int get_experience()const
	{
		return experience;
	}
	void set_speciality(const std::string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experience(int experience)
	{
		this->experience = experience;
	}
	void set_experience(const std::string& experience)
	{
		this->experience = std::stoi(experience);
	}
	//Кострукторы/Деструктор
	Teacher
	(const std::string& last_name, const std::string& first_name, const std::string& age,
		const std::string& speciality, const std::string& experience)
		: Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_experience(experience);
		std::cout << "TConstructor:\t" << this << std::endl;
	}
	Teacher
	(const std::string& last_name, const std::string& first_name, int age,
		const std::string& speciality, int experience)
		: Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_experience(experience);
		std::cout << "TConstructor:\t" << this << std::endl;
	}
	~Teacher()
	{
		std::cout << "TDestructor:\t" << this << std::endl;
	}
	//Методы
	std::ostream& print(std::ostream& os)const
	{
		Human::print(os) << " ";
		return os << "Speciality: " << speciality << "; " << "Experience: " << experience << ";";
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		Human::print(ofs);
		ofs.width(SPECIALITY_WIDTH);
		ofs << speciality;
		ofs.width(EXPERIENCE_WIDTH);
		ofs << experience;
		return ofs;
	}
};

class Graduate : public Student
{
	static const int THESIS_TOPIC_WIDTH = 30;
	static const int GRADE_WIDTH = 5;
	std::string thesis_topic;
	int grade;
public:
	//Гетторы/Сетторы
	const std::string& get_thesis_topic()const
	{
		return thesis_topic;
	}
	int get_grade()const
	{
		return grade;
	}
	void set_thesis_topic(const std::string& thesis_topic)
	{
		this->thesis_topic = thesis_topic;
	}
	void set_grade(int grade)
	{
		this->grade = grade;
	}
	//Конструкторы/Деструктор
	Graduate
	(const Student& student, const std::string& thesis_topic, int grade)
		: Student(student.get_last_name(), student.get_first_name(), student.get_age(), student.get_specialiry())
	{
		set_thesis_topic(thesis_topic);
		set_grade(grade);
	}
	~Graduate()
	{
		std::cout << "GDestructor:\t" << this << std::endl;
	}
	//Методы
	std::ostream& print(std::ostream& os)const
	{
		Human::print(os) << " ";
		return os << "Speciality: " << speciality << "; " << "Thesis Topic: " << thesis_topic << "; " << "Grade: " << grade << ";";
	}
	std::ofstream& print(std::ofstream& ofs)const
	{
		Human::print(ofs);
		ofs.width(THESIS_TOPIC_WIDTH);
		ofs << thesis_topic;
		ofs.width(GRADE_WIDTH);
		ofs << grade;
		return ofs;
	}
};

void print(Human** group, const int n)
{
	for (int i = 0; i < n; i++) std::cout << *group[i] << std::endl;
}

void save(Human** group, const int size, const char filename[])
{
	std::ofstream fout(filename);
	for (int i = 0; i < size; i++) fout << *group[i] << std::endl;
	fout.close();
	std::string command = "start notepad ";
	command += filename;
	system(command.c_str());
}

Human** load(const std::string& filename, int& n)
{
	Human** group = nullptr;
	std::ifstream fin_number_objects(filename);
	if (fin_number_objects.is_open())
	{
		//Определяем размер массива
		for (n = 0; !fin_number_objects.eof(); n++)
		{
			std::string buffer;
			std::getline(fin_number_objects, buffer);
		}
		fin_number_objects.close();
	}
	else std::cerr << "Error: file not found" << std::endl;

	group = new Human * [--n] {};
	int j = 0;
	const int SIZE = 256;
	char str[SIZE] = {};

	std::ifstream fin_members_class(filename);
	if (fin_members_class.is_open())
	{
		while (!fin_members_class.eof())
		{
			std::string buffer;
			fin_members_class >> buffer;
			if (buffer == "Human")
			{
				fin_members_class.getline(str, SIZE);
				std::string* members_class = new std::string[Count_Space(str)];
				members_class = Forming_an_array_of_fields(str);
				group[j++] = new Human(members_class[0], members_class[1], members_class[2]);
				delete[] members_class;
			}
			if (buffer == "Student")
			{
				fin_members_class.getline(str, SIZE);
				std::string* members_class = new std::string[Count_Space(str)];
				members_class = Forming_an_array_of_fields(str);
				group[j++] = new Student(members_class[0], members_class[1], members_class[2], members_class[3], members_class[4], members_class[5], members_class[6]);
				delete[] members_class;
			}
			if (buffer == "Teacher")
			{
				fin_members_class.getline(str, SIZE);
				std::string* members_class = new std::string[Count_Space(str)];
				members_class = Forming_an_array_of_fields(str);
				group[j++] = new Teacher(members_class[0], members_class[1], members_class[2], members_class[3], members_class[4]);
				delete[] members_class;
			}
		}
		fin_members_class.close();
	}
	else std::cerr << "Error: file not found" << std::endl;
	return group;
}
char* Shrink(char* str)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == ' ' && str[i + 1] == ' ')
		{
			for (int j = i; str[j] != 0; j++) str[j] = str[j + 1];
			i--;
		}
	}
	while (str[0] == ' ') for (int i = 0; str[i]; i++) str[i] = str[i + 1];
	for (int i = 0; str[i]; i++) str[i] = str[i + 1];
	return str;
}
std::string* Forming_an_array_of_fields(char str[])
{
	std::string* buffer;
	buffer = new std::string[Count_Space(str)]{};
	Shrink(str);
	int i = 0;
	for (int j = 0; j < Count_Space(str); j++)
	{
		for (; str[i]; i++)
		{
			if (str[i] != ' ')
				buffer[j] += str[i];
			else
			{
				i++;
				break;
			}
		}
	}
	return buffer;
}
int Count_Space(char str[])
{
	int s = 0;
	for (int i = 0; str[i]; i++) if (str[i] == ' ') s++;
	return s;
}

//#define Creative

void main()
{
	setlocale(LC_ALL, "");
#ifdef Creative
	Human human("Montana", "Antonio", 30);
	human.print();

	Student stud("Pinkman", "Jessie", 25, "Chemistry", "WW_220", 95, 98);
	stud.print();

	Teacher teach("Ivanov", "Ivan", 57, "Programmer", 20);
	teach.print();

	Graduate gradute(stud, "Blue Lollipops", 99);
	gradute.print();
#endif 	
	Human* group[] =
	{
		new Human("Montana", "Antonio", 35),
		new Student("Pinkman", "Jessie", 75, "Chemistry", "WW_220", 68, 76),
		new Teacher("Ivanov", "Ivan", 68, "Programmer", 95)
	};
	print(group, sizeof(group) / sizeof(group)[0]);
	save(group, sizeof(group) / sizeof(group)[0], "Group.txt");
	int size;
	Human** group_load = load("Group.txt", size);
	print(group_load, sizeof(group) / sizeof(group)[0]);
}