#include <Windows.h>
#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <time.h>
#include <string>
#include <iomanip>
using namespace std;

class person
{
private:
	string lastName, firstName;
public:
	person() : lastName(" "), firstName(" ")	// конструктор по умолчанию
	{}
	person(string lName, string fName) : lastName(lName), firstName(fName) // конструктор с двумя параметрами
	{}
	friend bool operator < (const person& p1, const person& p2)
	{
		if (p1.lastName == p2.lastName)
			return (p1.firstName < p2.firstName) ? true : false;
		return (p1.lastName < p2.lastName) ? true : false;
	}
	friend bool operator == (const person& p1, const person& p2)
	{
		return (p1.lastName == p2.lastName && p1.firstName == p2.firstName) ? true : false;
	}
	friend ostream& operator << (ostream& os, const person& p)
	{
		os << setw(15) << left << p.lastName << " " << setw(15) << left << p.firstName;
		return os;
	}
	friend istream& operator >> (istream& is, person& p)
	{
		is >> p.lastName >> p.firstName;
		return is;
	}
};

map<int, person> input(const char* filename)
{
	ifstream myfile(filename);
	istream_iterator<person> person_iter(myfile);
	istream_iterator<person> eos;

	deque<person> group;
	copy(person_iter, eos, back_inserter(group));
	sort(group.begin(), group.end());

	map<int, person> ordered_group;
	int i = 0;
	for (auto iter = group.begin(); iter != group.end(); ++iter)
		ordered_group.insert(make_pair(i++, *iter));
	return ordered_group;
}

int bandrand(int startvalue, int endvalue)
{
	srand(time(NULL));
	return startvalue + rand() % (abs(endvalue - startvalue) + 1);
}

map<person, person> random(map<int, person> ordered_group)
{
	map<person, person> control_group;
	vector<int> numbers;
	int random;

	while (numbers.size() < ordered_group.size())
		if (find(numbers.begin(), numbers.end(), random = bandrand(0, ordered_group.size() - 1)) == numbers.end() && random != numbers.size())
		{
			if (numbers.size() == (ordered_group.size() - 1) && find(numbers.begin(), numbers.end(), numbers.size()) == numbers.end())
				numbers.clear();
			numbers.push_back(random);
		}

	vector<int>::iterator iter_numbers = numbers.begin();
	for (auto iter = ordered_group.begin(); iter != ordered_group.end(); ++iter)
		control_group.insert(make_pair(iter->second, ordered_group[*(iter_numbers++)]));

	return control_group;
}

void output(map<person, person> control_group, const char* filename)
{
	ofstream os(filename);
	os	 << setw(20) << "Проверяющий" << setw(16) << " " << setw(20) << "Проверяемый" << endl << endl;
	cout << setw(20) << "Проверяющий" << setw(16) << " " << setw(20) << "Проверяемый" << endl << endl;
	for (auto iter = control_group.begin(); iter != control_group.end(); ++iter)
	{
		os	 << iter->first << "<->	" << iter->second << endl;
		cout << iter->first << "<->	" << iter->second << endl;
	}
}

int main()
{
	SetConsoleOutputCP(1251);

	output(random(input("group.txt")), "group_pair_out.txt");

	system("pause");
}