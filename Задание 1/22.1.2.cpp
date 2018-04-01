#include <Windows.h>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

struct names
{
	int number;
	string name_b;
	friend istream& operator >> (istream& is, names& n)
	{
		try
		{
			string numstr;
			getline(is, numstr, ';');
			n.number = stoi(numstr);
			getline(is, n.name_b);
		}
		catch(invalid_argument)
		{}
		return is;
	}
};
struct plans
{
	char plan;
	int num_sc;
	string name;
	friend istream& operator >> (istream& is, plans& p)
	{
		try
		{
			string substring;
			getline(is, substring, ';');
			p.plan = substring[0];
			getline(is, substring, ';');
			p.num_sc = stoi(substring);
			getline(is, p.name);
		}
		catch (invalid_argument)
		{}
		return is;
	}
};
struct money
{
	int regn;
	char plan;
	int num_sc;
	char a_p;
	float vr, vv, vitg, ora, ova, oitga, orp, ovr, oitgp, ir, iv, iitg;
	string dt;
	float priz;
	friend istream& operator >> (istream& is, money& m)
	{
		try
		{
			string substring;
			getline(is, substring, ';');
			m.regn = stoi(substring);
			getline(is, substring, ';');
			m.plan = substring[0];
			getline(is, substring, ';');
			m.num_sc = stoi(substring);
			getline(is, substring, ';');
			m.a_p = substring[0];
			getline(is, substring, ';');
			m.vr = stof(substring);
			getline(is, substring, ';');
			m.vv = stof(substring);
			getline(is, substring, ';');
			m.vitg = stof(substring);
			getline(is, substring, ';');
			m.ora = stof(substring);
			getline(is, substring, ';');
			m.ova = stof(substring);
			getline(is, substring, ';');
			m.oitga = stof(substring);
			getline(is, substring, ';');
			m.orp = stof(substring);
			getline(is, substring, ';');
			m.ovr = stof(substring);
			getline(is, substring, ';');
			m.oitgp = stof(substring);
			getline(is, substring, ';');
			m.ir = stof(substring);
			getline(is, substring, ';');
			m.iv = stof(substring);
			getline(is, substring, ';');
			m.iitg = stof(substring);
			getline(is, m.dt, ';');
			m.dt.resize(10);
			getline(is, substring);
			m.priz = stof(substring);
		}
		catch (invalid_argument)
		{}
		return is;
	}

};
struct res
{
	int regn, num_sc;
	string dt;
	float iitg;
	friend ostream& operator << (ostream& os, const res& r)
	{
		os << r.regn << "  " << r.num_sc << "  " << r.dt << "  " << setw(7) << fixed << setprecision(0) << r.iitg;
		return os;
	}
};

void read_names(const char* filename, vector<names>& vname)
{
	ifstream name_stream(filename);
	istream_iterator<names> name_iter(name_stream);
	istream_iterator<names> eos;
	copy(name_iter, eos, back_inserter(vname));
}
void read_plans(const char* filename, vector<plans>&vplan)
{
	ifstream plans_stream(filename);
	istream_iterator<plans> plans_iter(plans_stream);
	istream_iterator<plans> eos;
	copy(plans_iter, eos, back_inserter(vplan));
}
void read_money(const char* filename, vector<money>& vmoney)
{
	ifstream money_stream(filename);
	istream_iterator<money> money_iter(money_stream);
	istream_iterator<money> eos;
	copy(money_iter, eos, back_inserter(vmoney));
}
// ��������� ������������ ����� �� ��� ������
string get_name(int number, vector<names>&vname)
{
	auto result = find_if(vname.begin(), vname.end(), [&](const names &n) { return (number == n.number); });
	if (result != vname.end())
		return result->name_b;
	else
		return "";
}
 //��������� ������������ ����� �� ��� ������
string get_plan(int num_sc, const vector<plans>&vplan)
{
	auto result = find_if(vplan.begin(), vplan.end(), [&](const plans &p) { return (num_sc == p.num_sc); });
	if (result != vplan.end())
		return result->name;
	else
		return "";
}
// ����� �������, ��������������� �������� ��������
void search_money(int regn, int num_sc, vector<money> vmoney, vector<res>& vres)
{
	for_each(vmoney.begin(), vmoney.end(), [&](const money &m) { if (m.regn == regn && m.num_sc == num_sc) vres.push_back({ m.regn, m.num_sc, m.dt, m.iitg }); });
}
// ����� ����������� �� �����
void show_res(const vector<res>&vres)
{
	for_each(vres.begin(), vres.end(), [&](const res r) { cout << r.dt << setw(6) << " " << setw(7) << fixed << setprecision(0) << r.iitg << endl; });
}
// ������ ����������� � ���� RESULT.txt
void write_res(char* filename, const vector<res> &vres)
{
	fstream myfile(filename, ios::out);
	myfile << "REGN NUM_SC	     DT		   IITG" << endl;
	for_each(vres.begin(), vres.end(), [&](const res r) { myfile << " " << r << endl; });
}

int main()
{
	SetConsoleOutputCP(1251);

	vector<names> vname;	// ������ ��� �������� ������� ������� NAMES
	vector<plans> vplan;	// ������ ��� �������� ������� ������� PLAN
	vector<money> vmoney;	// ������ ��� �������� ������� ������� 101F
	vector<res> vres;		// ������ ��� �������� �����������

	char file_1[] = "NAMES.txt", file_2[] = "PLAN.txt", file_3[] = "101F.txt", file_4[] = "RESULT.txt";

	read_names(file_1, vname);	// ������� ���������� ������� � ����� NAMES.txt � ���������� ������� vname
	cout << "��������� " << vname.size() << " ������� �� ����� " << file_1 << endl;

	read_plans(file_2, vplan);	// ������� ���������� ������� � ����� PLAN.txt � ���������� ������� vname
	cout << "��������� " << vplan.size() << " ������� �� ����� " << file_2 << endl;

	read_money(file_3, vmoney);	// ������� ���������� ������� � ����� 101F.txt � ���������� ������� vname
	cout << "��������� " << vmoney.size() << " ������� �� ����� " << file_3 << endl;

	int regn, num_sc;
	string name, plan;
	while (1)
	{
		cout << endl << "������� ���. ����� �����: "; cin >> regn;
		if ((name = get_name(regn, vname)) != "")
			break;
		cout << "���� �� ������" << endl;
	}

	while (1)
	{
		cout << endl << "������� ����� �����: "; cin >> num_sc;
		if ((plan = get_plan(num_sc, vplan)) != "")
			break;
		cout << "���� �� ������" << endl;
	}

	cout << endl << "�������� ������� �� ����� �" << num_sc << " \"" << plan << " \"" << endl;

	cout << endl << "��� ����� �" << regn << " " << name << endl;

	cout << endl << setw(7) << right << "����" << setw(22) << "�����, ���. ���." << endl;
	search_money(regn, num_sc, vmoney, vres);
	show_res(vres);
	write_res(file_4, vres);
	cout << endl;
	cout << "���������� (" << vres.size() << " �������) �������� � ���� " << file_4 << endl << endl;
	system("pause");
}
