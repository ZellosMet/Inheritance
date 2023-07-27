#include<iostream>
#include<fstream>// подключаем файловцую библиотеку

//#define WRITE_TO_FILE
//#define READ_FROM_FILE
//#define SWAP_OF_ADDRESS
//#define ADDRESS_FIXED

void main()
{
	setlocale(LC_ALL, "");

#ifdef WRITE_TO_FILE

	std::cout << "Hello Files" << std::endl;
	//Создание потока
	std::ofstream fout;
	//Открытие потока 
	fout.open("File1.txt", std::ios_base::app);
	//Пишем поток
	fout << "Hello Files" << std::endl;
	//Закрываем поток
	fout.close();

	system("start notepad File1.txt");
#endif 

#ifdef READ_FROM_FILE
	//Создание потока
	std::ifstream fin;
	//Открытие потока
	fin.open("File1.txt");
	//Проверка на открытие потока
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			const int SIZE = 256;
			char sz_buffer[SIZE] = {};
			//fin.getline(sz_buffer, SIZE);
			fin >> sz_buffer;
			std::cout << sz_buffer << std::endl;
		}
		fin.close();
	}
	else std::cerr << "Error: File not found" << std::endl;
#endif 

#ifdef SWAP_OF_ADDRESS
	std::ifstream fin;
	fin.open("201_RAW.txt");
	if (fin.is_open())
	{
		std::string IP;
		std::string MAC;
		std::ofstream fout;
		fout.open("201_ready.txt");
		while (!fin.eof())
		{
			fin >> IP;
			fin >> MAC;
			fout << MAC << "\t" << IP << std::endl;
		}
		fout.close();
		std::cout << "File Ready!" << std::endl;
	}
	else std::cerr << "Error: File not found" << std::endl;
	fin.close();
	system("start notepad 201_ready.txt");
#endif

#ifdef ADDRESS_FIXED
	std::string hostname = "201";
	std::string file_name;
	std::ifstream fin;
	fin.open(hostname + "_RAW.txt");
	if (fin.is_open())
	{
		std::string IP;
		std::string MAC;
		std::ofstream fout;
		int number = 1;
		fout.open("201dhcpd");
		while (!fin.eof())
		{
			fin >> IP;
			fin >> MAC;
			fout << "host-" << hostname << "-" << number << std::endl;
			fout << "{" << std::endl;
			fout << "\thardware ethernet\t" << MAC << std::endl;
			fout << "\tfixed-address\t\t" << IP << std::endl;
			fout << "}\n\n";
			number++;
		}
		fout.close();
		std::cout << "File Ready!" << std::endl;
	}
	else std::cerr << "Error: File not found" << std::endl;
	fin.close();
	system("start notepad 201dhcpd");
#endif 
}