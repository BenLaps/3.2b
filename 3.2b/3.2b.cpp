
#include <iostream>
#include <string>
#include <iomanip>
#include <locale>
#include <Windows.h> 

using namespace std;

enum Cours { I = 1, II, III, IV, V, VI };
string CoursStr[] = {
	"I", "II", "III", "IV", "V", "VI"
};

enum Spec { KN, INF, MATHandECONOM };
string SpecStr[] = {
	"����.� �����",
	"������.",
	"�����. �� �����.",
};

struct Student
{
	string prizv;
	Cours cours;
	Spec spec;
	int physic;
	int math;
	union {
		int prog;
		int numM;
		int ped;
	};
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);

void Sort(Student* s, const int N);

int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int BinSearch(Student* s, const int N, const string lastname, const Cours cours, const int informatic);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ N: "; cin >> N;

	Student* s = new Student[N];

	int menuItem;
	string lastname = "";
	int cours;
	int informatic = 0;
	int found;

	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " [1] - �������� ����� � ���������" << endl;
		cout << " [2] - ���� ����� �� �����" << endl;
		cout << " [5] - ����������" << endl;
		cout << " [6] - �������� ������������� �� ���� �����" << endl;
		cout << " [7] - ������� ����� �������� �� �������� , ������ �� ������� � �����������" << endl;
		cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;


		switch (menuItem)
		{
		case 1:
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 5:
			Sort(s, N);
			break;
		case 6:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 7:
			cout << "������ ����� ������:" << endl;
			cout << " �������: "; cin >> lastname;
			cout << " ���� "; cin >> cours;
			cout << " ������ "; cin >> informatic;
			cin.get();
			cin.sync();

			cout << endl;
			if ((found = BinSearch(s, N, lastname, (Cours)cours, informatic)) != -1)
				cout << "�������� ���������� � ������� " << found + 1 << endl;
			else
				cout << "�������� ���������� �� ��������" << endl;
			break;

			BinSearch(s, N, lastname, (Cours)cours, informatic);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);
	return 0;
}

void Create(Student* s, const int N)
{
	int cours, spec;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����

		cout << " �������: "; cin >> s[i].prizv;
		cout << " ����: "; cin >> cours;
		s[i].cours = (Cours)cours;
		cout << "������������: 0 - ��������� �����,  1 - �����������, \n 2 - ���������� �� ��������, "
			<< endl << "������ ������������: ";
		cin >> spec;
		s[i].spec = (Spec)spec;
		cout << " ������ � ������: "; cin >> s[i].physic;
		cout << " ������ � ����������: "; cin >> s[i].math;
		switch (s[i].spec) {
		case KN:
			cout << "������ � �������������:"; cin >> s[i].prog;
			break;
		case INF:
			cout << "������ � ��������� ������:"; cin >> s[i].numM;
			break;
		case MATHandECONOM:
			cout << "������ � ���������:"; cin >> s[i].ped;
			break;
		}
		cout << endl;
	}
}
void Print(Student* s, const int N)
{

	cout << "========================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | �����a | �������. | ���. ���. | ��������� |"
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << s[i].prizv << " "
			<< "| " << setw(4) << right << s[i].cours << " "
			<< "| " << setw(11) << left << s[i].spec << " "
			<< "| " << setw(6) << right << s[i].physic << " "
			<< "| " << setw(6) << left << s[i].math << " ";
		switch (s[i].spec) {
		case KN:
			cout << "| " << setw(8) << right
				<< s[i].prog << " | " << setw(12) << right
				<< " | " << setw(12) << right << " |" << endl;
			break;
		case INF:
			cout << "| " << setw(11) << right
				<< " | " << setw(9) << right << s[i].numM
				<< " | " << setw(12) << right << " |" << endl;
			break;
		case MATHandECONOM:
			cout << "| " << setw(11) << right
				<< " | " << setw(12) << right
				<< " | " << setw(10) << right << s[i].ped << " |" << endl;
			break;
		}
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* s, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // ����� "���������"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((s[i1].cours > s[i1 + 1].cours)
				||
				(s[i1].cours == s[i1 + 1].cours &&
					s[i1].prog > s[i1 + 1].prog)
				||
				(s[i1].cours == s[i1 + 1].cours &&
					s[i1].prog == s[i1 + 1].prog &&
					s[i1].prizv < s[i1 + 1].prizv))
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}
}

int* IndexSort(Student* s, const int N)
{
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((s[I[j]].cours > s[value].cours) ||
				(s[I[j]].cours == s[value].cours &&
					s[I[j]].prog > s[value].prog) ||
				(s[I[j]].cours == s[value].cours &&
					s[I[j]].prog == s[value].prog &&
					s[I[j]].prizv < s[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

void PrintIndexSorted(Student* s, int* I, const int N)
{ // ��������� ������� Print(), ��� ������ ��������� p[i]... 
 // ������������� ������ �� ��������� ���������� ������ �: p[I[i]]...
	cout << "========================================================================="
		<< endl;
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | ����������� | "
		<< endl;
	cout << "-------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << s[I[i]].prizv
			<< "| " << setw(4) << right << s[I[i]].cours << " "
			<< "| " << setw(11) << left << s[I[i]].spec << " "
			<< "| " << setw(6) << right << s[I[i]].physic << " "
			<< "| " << setw(6) << left << s[I[i]].math << " "
			<< "| " << setw(7) << right << s[I[i]].prog << endl;
	}
	cout << "========================================================================="
		<< endl;
	cout << endl;
}

int BinSearch(Student* s, const int N, const string lastname, const Cours cours, const int informatic)
{
	// ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (s[m].prizv == lastname && s[m].cours == cours && s[m].prog == informatic)
			return m;
		if ((s[m].prizv < lastname)
			||
			(s[m].cours == cours &&
				s[m].prizv < lastname)
			||
			(s[m].prog == informatic &&
				s[m].cours == cours &&
				s[m].prizv < lastname))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}

