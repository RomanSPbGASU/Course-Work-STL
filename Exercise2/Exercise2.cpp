#include <Windows.h>
#include <iostream>
#include <fstream>
#include <list>
#include <deque>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

class names
{

	int number;
	string name_b;
public:
	names() {};
	names(int number, string name_b) : number(number), name_b(name_b)
	{};
	friend ostream& operator << (ostream& os, const names& n)
	{
		os << n.number << ";" << n.name_b;
		return os;
	}
	friend istream& operator >> (istream& is, names& n)
	{
		try
		{
			string numstr;
			getline(is, numstr, ';');
			n.number = stoi(numstr);
			getline(is, n.name_b);
		}
		catch (invalid_argument)
		{}
		return is;
	}
};

void read_names(const char* filename, list<names>& lname)
{
	ifstream name_stream(filename);
	istream_iterator<names> name_iter(name_stream);
	istream_iterator<names> eos;
	copy(name_iter, eos, back_inserter(lname));
}

void write_names(const char * filename, list<names>& lname, int start_pos)
{
	if (start_pos > lname.size())
		return;
	for (int i = 0; i < start_pos - 1; ++i)
		lname.pop_front();
	ofstream name_stream(filename);
	ostream_iterator<names> name_iter(name_stream, "\n");
	copy(lname.begin(), lname.end(), name_iter);
}

int main()
{
	SetConsoleOutputCP(1251);

	list<names> lnames;
	read_names("NAMES.txt", lnames);
	cout << "Загружено " << lnames.size() << " записей из файла NAMES.txt" << endl;

	int ans;
	while (1)
	{
		cout << endl << "Введите номер элемента, начиная с которого будет происходить запись в файл: "; cin >> ans;
		if (ans > lnames.size())
			cout << "Введённый номер больше количества элементов" << endl;
		else
			break;
	}

	write_names("NAMES_new.txt", lnames, ans);

	cout << endl << "Записано " << lnames.size() << " записей в файл NAMES_new.txt" << endl << endl;

	system("pause");
}

