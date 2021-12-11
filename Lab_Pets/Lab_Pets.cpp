// Lab_Pets.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
#include <set>
using namespace std;
struct Info
{
	string master_name;
	string vid;
	string klichka;
	int age;
};
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream F1;
	vector <Info> mass;
	Info str;
	string str1, str2; //вспомогательные строки
	F1.open("input.txt");
	while (!F1.eof())//чтение структуры
	{
		getline(F1, str1);
		int i = 0;
		while (str1[i] != ',')
		{
			str2.push_back(str1[i]);
			i++;
		}
		str.master_name = str2;
		str2.clear();
		i++;
		while (str1[i] != ',')
		{
			str2.push_back(str1[i]);
			i++;
		}
		str.vid = str2;
		str2.clear();
		i++;
		if (str1[i] != ',' && str1[i + 1] != ',')
		{
			while (str1[i] != ',')
			{
				str2.push_back(str1[i]);
				i++;
			}
			str.klichka = str2;
			str2.clear();
			i++;
		}
		else
		{
			str.klichka = " ";
			i++;
		}

		while (i < str1.length())
		{
			str2.push_back(str1[i]);
			i++;
		}
		int a = stoi(str2);
		str.age = a;
		str2.clear();
		i = 0;
		mass.push_back(str);
	}

	int x;
	cout << "Выберите нужную опцию:" << endl;
	cout << "1. Вывести кол-во различных видов животных у каждого владельца" << endl;
	cout << "2. Вывести все клички и владельцев определенного вида животного" << endl;
	cout << "3. Вывести кол-во видов животных с определённой кличкой" << endl;
	cout << "4. Вывести возраст самого старого и молодого животных для каждого вида" << endl;
	cin >> x;
	cin.ignore(1, '\n');
	set <string> klichki;//пункт 2
	set <string> vladelcy;//пункт 2
	set <string> vids;//пункт 3
	string str3, str4;//вспомогательные строки
	int k = 0;
	switch (x)
	{
	case 1:
		for (int i = 0; i < mass.size() - 1; i++)//Сортировка имён по алфавиту и по видам животных
		{
			for (int j = i; j < mass.size(); j++)
			{
				if (strcmp(mass[i].master_name.c_str(), mass[j].master_name.c_str()) > 0)
				{
					str = mass[i];
					mass[i] = mass[j];
					mass[j] = str;
				}
				if (strcmp(mass[i].vid.c_str(), mass[j].vid.c_str()) > 0 && strcmp(mass[i].master_name.c_str(), mass[j].master_name.c_str()) == 0)
				{
					str = mass[i];
					mass[i] = mass[j];
					mass[j] = str;
				}
			}

		}
		for (int i = 0; i < mass.size(); i++)
		{
			str3 = mass[i].master_name;
			str4 = " ";
			while (strcmp(mass[i].master_name.c_str(), str3.c_str()) == 0)
			{
				if (strcmp(mass[i].vid.c_str(), str4.c_str()) != 0)
				{
					str4 = mass[i].vid;
					k++;
				}
				if (i + 1 == mass.size())
					break;
				if (str3 == mass[i + 1].master_name)
					i++;
				else break;
			}
			cout << str3 << " владеет " << k << " различными видами животных" << endl;
			k = 0;
		}
		break;
	case 2:
		while (true)
		{
			cout << "Выберите вид животного:";
			getline(cin, str3);
			for (int i = 0; i < mass.size(); i++)
			{
				if (strcmp(mass[i].vid.c_str(), str3.c_str()) == 0)
				{
					vladelcy.insert(mass[i].master_name);
					klichki.insert(mass[i].klichka);
				}
			}
			try
			{
				if (klichki.size() == 0 && vladelcy.size() == 0)
					throw 1;
				cout << "Клички:";
				for (string item : klichki)
				{
					cout << item << " ";
				}
				cout << endl << "Владельцы:";
				for (string item : vladelcy)
				{
					cout << item << " ";
				}
				break;
			}
			catch (int)
			{
				cout << "Неправильно выбран вид животного" << endl;
			}
		}
		break;
	case 3:
		cout << "Выберите кличку(отсутствие клички обозначается пробелом):" << endl;
		getline(cin, str3);
		for (int i = 0; i < mass.size(); i++)
		{
			if (strcmp(mass[i].klichka.c_str(), str3.c_str()) == 0)
			{
				vids.insert(mass[i].vid);
			}
		}
		if (vids.size() > 0)
			cout << vids.size() << endl;
		else
			cout << "Животных с такой кличкой не обнаружено" << endl;
		break;
	case 4:
		for (int i = 0; i < mass.size(); i++)//соритровка по видам животных
		{
			for (int j = i; j < mass.size(); j++)
			{
				if (strcmp(mass[i].vid.c_str(), mass[j].vid.c_str()) > 0)
				{
					str = mass[i];
					mass[i] = mass[j];
					mass[j] = str;
				}
				if (strcmp(mass[i].vid.c_str(), mass[j].vid.c_str()) == 0 && mass[i].age > mass[j].age)
				{
					str = mass[i];
					mass[i] = mass[j];
					mass[j] = str;
				}
			}
		}
		for (int i = 0; i < mass.size(); i++)
		{
			int b = mass[i].age;
			int m = mass[i].age;
			str3 = mass[i].vid;
			while (str3 == mass[i].vid)
			{
				if (mass[i].age >= b)
					b = mass[i].age;
				if (mass[i].age <= m)
					m = mass[i].age;
				if (i + 1 == mass.size())
					break;
				if (str3 == mass[i + 1].vid)
					i++;
				else
					break;
			}
			cout << mass[i].vid << ", возраст самого старого(ой) - " << b << ", возраст самого молодого(ой) - " << m << endl;
		}
		break;
	default: cout << "Неправильная операция" << endl;
	}
	F1.close();
	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
