#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
using namespace std;
const int N = 150;

struct Student {
	char fullname[100];
	char sex;
	int group;
	int id;
	int grades[8];
};



void studSort(Student* stud, int a) {
	int perem, elem;
	Student per;
	for (int i = 1; i < a; ++i) {
		perem = stud[i].group;
		per = stud[i];
		elem = i;
		for (int j = i - 1; j >= 0 && stud[j].group > perem; --j) {
			stud[j + 1] = stud[j];
			elem = j;
		}
		stud[elem] = per;
	}			
}


void structPrint(int a, Student* stud) {
	int i = a;
	int count = 0;
	while (count != i) {
		cout << stud[count].fullname << '\n';
		cout << stud[count].sex << '\n';
		cout << stud[count].group << '\n';
		cout << stud[count].id << '\n';
		for (int j = 0; j < 8; j++) {
			cout << stud[count].grades[j] << ' ';
		}
		cout << '\n';
		count++;
	}
}


int newEntry(Student * stud, int a) {
	struct Student student;
	cout << "Введите ФИО студента:\n";
	cin.ignore();
	cin.getline(student.fullname, 100);
	cout << '\n' << "Введите пол: 'М' или 'Ж'\n";
	student.sex = _getche();
	while (student.sex != 'М' && student.sex != 'м' && student.sex != 'Ж' && student.sex != 'ж') {
		cout << '\n' << "Пол введен неправильно, повторите ввод:\n";
		student.sex = _getche();
	}
	cout << '\n' << "Максимальное количество студентов в группе 20. Введите номер группы:\n";
	cin >> student.group;
	int colvGr = 0;
	bool flagGr = false;
	while (!flagGr) {
		for (int i = 0; i < a; i++) {
			if (student.group == stud[i].group) {
				colvGr++;
			}
		}
		if (colvGr == 20) {
			colvGr = 0;
			cout << "В группе максимальное количество студентов, отправьте его в другую группу:\n";
			cin >> student.group;
		}
		else {
			flagGr = true;
		}
	}
	cout << '\n' << "Введите номер студента:\n";
	cin >> student.id;   
	cout << '\n' << "Введите оценки:\n";
	bool flag = true;
	for (int i = 0; i < 8; i++) {
		cin >> student.grades[i];
		while (student.grades[i] < 2 || student.grades[i] > 5) {
			cout << '\n' << "Введено неправильное число, повторите ввод с неправильной оценки:\n";
			cin >> student.grades[i];
		}
		if (student.grades[i] == 2) {
			cout << "У студента есть 2" << '\n';
			flag = false;
			break;
		}
	}
	
	if (flag) {
		strcpy_s(stud[a].fullname, student.fullname);
		stud[a].sex = student.sex;
		stud[a].group = student.group;
		stud[a].id = student.id;
		for (int i = 0; i < 8; i++) {
			stud[a].grades[i] = student.grades[i];
		}

		studSort(stud, a + 1);
		a = a + 1;

		ofstream File("studfile.txt");
		if (!File.is_open())
		{
			cout << "Открыть файл не удалось\n";
			exit(1);
		}
		for (int i = 0; i < a; i++) {
			if (i != 0) {
				File << '\n';
			}
			File << stud[i].fullname << '\n';
			File << stud[i].sex << '\n';
			File << stud[i].group << '\n';
			File << stud[i].id << '\n';
			for (int j = 0; j < 8; j++)
				File << stud[i].grades[j] << " ";
		}

		cout << '\n' << "Данные занесены в файл" << '\n';
		File.close();
	}
	return a;
}


int changeEntry(Student* stud) {
	ifstream File("studfile.txt");
	if (!File.is_open())
	{
		cout << "Открыть файл не удалось\n";
		exit(1);
	}
	int i = 0;
	while (!File.eof()) {
		File.getline(stud[i].fullname, 100);
		char k[2];
		File.getline(k, 2);
		stud[i].sex = k[0];
		char a[10];
		File.getline(a, 10);
		int lens;
		lens = strlen(a);
		int perem = 0;
		int temp = 1;
		for (int j = lens - 1; j >= 0; j--) {
			perem += (a[j] - '0') * temp;
			temp *= 10;
		}
		stud[i].group = perem;
		char b[10];
		File.getline(b, 10);
		int lens2;
		lens2 = strlen(b);
		int perem2 = 0;
		int temp2 = 1;
		for (int j = lens2 - 1; j >= 0; j--) {
			perem2 += (b[j] - '0') * temp2;
			temp2 *= 10;
		}
		stud[i].id = perem2;

		char c[17];
		File.getline(c, 17);
		int d, t = 0;
		for (int j = 0; j <= 14; j += 2) {
			d = c[j] - '0';
			stud[i].grades[t] = d;
			t += 1;
		}
		i++;
	}
	return i;
	File.close();
}



int reversStud(Student* stud, int a) {
	cout << "Введите номер группы студента, запись о котором хотите изменить:\n";
	int groupNumber;
	cin >> groupNumber;
	cout << '\n';
	cout << "Введите порядковый номер студента, запись о котором хотите изменить\n";
	int indNumber;
	cin >> indNumber;
	cout << '\n';
	int countStud = a;
	int count = 0;
	bool flag = true, flagStr = false;
	int stGroup, stId;
	Student student;
	while (count != countStud) {
		if (stud[count].group == groupNumber) {
			if (stud[count].id == indNumber) {
				flagStr = true;
				stGroup = stud[count].group;
				stId = stud[count].id;
				cout << "Введите ФИО студента:\n";
				cin.ignore();
				cin.getline(student.fullname, 100);
				cout << '\n' << "Введите пол: 'М' или 'Ж'\n";
				student.sex = _getche();
				while (student.sex != 'М' && student.sex != 'м' && student.sex != 'Ж' && student.sex != 'ж') {
					cout << '\n' << "Пол введен неправильно, повторите ввод:\n";
					student.sex = _getche();
				}
				cout << '\n' << "Максимальное количество студентов в группе 20. Введите номер группы:\n";
				cin >> student.group;
				int colvGr = 0;
				bool flagGr = false;
				while (!flagGr) {
					for (int i = 0; i < a; i++) {
						if (student.group == stud[i].group) {
							colvGr++;
						}
					}
					if (colvGr == 20) {
						colvGr = 0;
						cout << "В группе максимальное количество студентов, отправьте его в другую группу:\n";
						cin >> student.group;
					}
					else {
						flagGr = true;
					}
				}
				cout << '\n' << "Введите номер студента:\n";
				cin >> student.id;
				cout << '\n' << "Введите оценки:\n";
				for (int i = 0; i < 8; i++) {
					cin >> student.grades[i];
					while (student.grades[i] < 2 || student.grades[i] > 5) {
						cout << '\n' << "Введено неправильное число, повторите ввод с неправильной оценки:\n";
						cin >> student.grades[i];
					}
				}
				for (int i = 0; i < 8; i++) {
					if (student.grades[i] == 2) {
						cout << "У студента есть 2, он удален из файла" << '\n';
						flag = false;
						break;
					}
				
				}
				if (flag) {
					strcpy_s(stud[count].fullname, student.fullname);
					stud[count].sex = student.sex;
					stud[count].group = student.group;
					stud[count].id = student.id;

					for (int i = 0; i < 8; i++) {
						stud[count].grades[i] = student.grades[i];
					}
					break;
				}
				
				else {
					for (int i = count; i < a - 1; i++) {
						strcpy_s(stud[i].fullname, stud[i + 1].fullname);
						stud[i].sex = stud[i + 1].sex;
						stud[i].group = stud[i + 1].group;
						stud[i].id = stud[i + 1].id;
						for (int j = 0; j < 8; j++) {
							stud[i].grades[j] = stud[i + 1].grades[j];
						}
					}
					strcpy_s(stud[a - 1].fullname, "");
					stud[a - 1].sex = ' ';
					stud[a - 1].group = 0;
					stud[a - 1].id = 0;
					for (int j = 0; j < 8; j++) {
						stud[a - 1].grades[j] = 0;
					}
					a = a - 1;
					break;
				}
			}
		}
		count++;
	}
	if (!flagStr) {
		cout << "Такого студента нет\n";
	}
	else {
		for (int i = 0; i < a; i++) {
			if (stud[i].group == stGroup && stud[i].id > stId) {
				stud[i].id -= 1;
			}
		}
		studSort(stud, a);
		ofstream File("studfile.txt");
		if (!File.is_open())
		{
			cout << "Открыть файл не удалось\n";
			exit(1);
		}

		for (int i = 0; i < a; i++) {
			if (i != 0) {
				File << '\n';
			}
			File << stud[i].fullname << '\n';
			File << stud[i].sex << '\n';
			File << stud[i].group << '\n';
			File << stud[i].id << '\n';
			for (int j = 0; j < 8; j++)
				File << stud[i].grades[j] << " ";
		}

		cout << '\n' << "Данные занесены в файл" << '\n';
		File.close();


		//	structPrint(a, stud);
		return a;
	}
}

void groupPrint(Student* stud, int a) {
	cout << "Введите номер нужной группы:\n";
	int groupNumber;
	cin >> groupNumber;
	cout << '\n';
	int countStud = a;
	int count = 0;
	bool flag = false;
	while (count != countStud) {
		if (stud[count].group == groupNumber) {
			flag = true;
			cout << stud[count].fullname << '\n';
			cout << stud[count].sex << '\n';
			cout << stud[count].group << '\n';
			cout << stud[count].id << '\n';
			for (int j = 0; j < 8; j++) {
				cout << stud[count].grades[j] << ' ';
			}
			cout << '\n';
		}
		count++;
	}
	if (!flag) {
		cout << "Такой группы студентов нет\n";
	}
}


void topStudent(Student* stud, int a) {
	struct Newstud {
		char fullname[100];
		char sex;
		int group;
		int id;
		int grades[8];
		int averageMark;
	};
	struct Newstud top[N];
	int averageMarks = 0;
	for (int i = 0; i < a; i++) {
		strcpy_s(top[i].fullname, stud[i].fullname);
		top[i].sex = stud[i].sex;
		top[i].group = stud[i].group;
		top[i].id = stud[i].id;
		for (int j = 0; j < 8; j++) {
			top[i].grades[j] = stud[i].grades[j];
			averageMarks += stud[i].grades[j];
		}
		top[i].averageMark = averageMarks;
		averageMarks = 0;
	}
	int perem, elem;
	Newstud per;
	for (int i = 1; i < a; ++i) {
		perem = top[i].averageMark;
		per = top[i];
		elem = i;
		for (int j = i - 1; j >= 0 && top[j].averageMark > perem; --j) {
			top[j + 1] = top[j];
			elem = j;
		}
		top[elem] = per;
	}
	float sr;
	for (int i = 0; i < a; i++) {
		cout << top[i].fullname << '\n';
		cout << top[i].sex << '\n';
		cout << top[i].group << '\n';
		cout << top[i].id << '\n';
		for (int j = 0; j < 8; j++) {
			cout << top[i].grades[j] << ' ';			
		}
		cout << '\n';
		sr = float(top[i].averageMark) / 8;
		cout << sr << '\n';
	}
}


void mailFemail(Student* stud, int a) {
	int countM = 0, countG = 0;
	for (int i = 0; i < a; i++) {
		if (stud[i].sex == 'М' or stud[i].sex == 'м') {
			countM += 1;
		}
		else {
			countG += 1;
		}
	}
	cout << "Количество мужчин: " << countM << '\n';
	cout << "Количество женщин: " << countG << '\n';
}

void numbers(Student* stud, int a) {
	cout << "Введите 1, если хотите вывести информацию о учениках, которые не получают стипендию\n";
	cout << "Введите 2, если хотите вывести информацию о учениках, которые учатся на хорошо и отлично\n";
	cout << "Введите 3, если хотите вывести информацию о учениках, которые учатся на отлично\n";
	int numb;
	cin >> numb;
	cout << '\n';
	switch (numb)
	{	case 1:
			for (int i = 0; i < a; i++) {
				bool flag = false;
				for (int j = 0; j < 8; j++) {
					if (stud[i].grades[j] == 3) {
						flag = true;
						break;
					}
				}
				if (flag) {
					cout << stud[i].fullname << '\n';
					cout << stud[i].sex << '\n';
					cout << stud[i].group << '\n';
					cout << stud[i].id << '\n';
					for (int j = 0; j < 8; j++) {
						cout << stud[i].grades[j] << ' ';
					}
					cout << '\n';
				}
			}
			break;
		case 2:
			for (int i = 0; i < a; i++) {
				bool flag = true;
				int countFour = 0, countFive = 0;
				for (int j = 0; j < 8; j++) {
					if (stud[i].grades[j] == 3) {
						flag = false;
						break;
					}
					if (stud[i].grades[j] == 4) {
						countFour++;
					}
					if (stud[i].grades[j] == 5) {
						countFive++;
					}
				}
				if (flag && countFour && countFive) {
					cout << stud[i].fullname << '\n';
					cout << stud[i].sex << '\n';
					cout << stud[i].group << '\n';
					cout << stud[i].id << '\n';
					for (int j = 0; j < 8; j++) {
						cout << stud[i].grades[j] << ' ';
					}
					cout << '\n';
				}
			}
			break;
		case 3:
			for (int i = 0; i < a; i++) {
				bool flag = true;
				for (int j = 0; j < 8; j++) {
					if (stud[i].grades[j] == 3) {
						flag = false;
						break;
					}
					if (stud[i].grades[j] == 4) {
						flag = false;
						break;
					}
				}
				if (flag) {
					cout << stud[i].fullname << '\n';
					cout << stud[i].sex << '\n';
					cout << stud[i].group << '\n';
					cout << stud[i].id << '\n';
					for (int j = 0; j < 8; j++) {
						cout << stud[i].grades[j] << ' ';
					}
					cout << '\n';
				}
			}
			break;
		default:
			cout << "Введено неправильное число\n";
			break;
	}
}

void studId(Student* stud, int a) {
	cout << "Введите номер студента:\n";
	int numb;
	cin >> numb;
	cout << '\n';
	bool flag = false;
	for (int i = 0; i < a; i++) {
		if (stud[i].id == numb) {
			flag = true;
			cout << stud[i].fullname << '\n';
			cout << stud[i].sex << '\n';
			cout << stud[i].group << '\n';
			cout << stud[i].id << '\n';
			for (int j = 0; j < 8; j++) {
				cout << stud[i].grades[j] << ' ';
			}
			cout << '\n';
		}
	}
	if (!flag) {
		cout << "Введен неправильный номер\n";
	}
}

void idz() {
	struct Olimp {
		char fullname[100];
		char timName[100];
		char kapName[100];
		char GTO[10];
		int beathday;
	};
	struct Olimp olimpi[N];
	ifstream File("olimp.txt");
	if (!File.is_open())
	{
		cout << "Открыть файл не удалось\n";
		exit(1);
	}
	int i = 0;
	while (!File.eof()) {
		File.getline(olimpi[i].fullname, 100);
		File.getline(olimpi[i].timName, 100);
		File.getline(olimpi[i].kapName, 100);
		File.getline(olimpi[i].GTO, 100);
		char a[5];
		File.getline(a, 5);
		int lens;
		lens = strlen(a);
		int perem = 0;
		int temp = 1;
		for (int j = lens - 1; j >= 0; j--) {
			perem += (a[j] - '0') * temp;
			temp *= 10;
		}
		olimpi[i].beathday = perem;
		i++;
	}
	int elem;
	char perem[100];
	Olimp per;
	for (int j = 1; j < i; ++j) {
		strcpy_s(perem, olimpi[j].timName);
		per = olimpi[j];
		elem = j;
		for (int q = j - 1; q >= 0 && olimpi[q].timName > perem; --q) {
			olimpi[q + 1] = olimpi[q];
			elem = q;
		}
		olimpi[elem] = per;
	}
	cout << "Участники, которым меньше 18 лет:\n";
	bool flag = false;
	for (int j = 0; j < i; j++) {
		if (2024 - olimpi[j].beathday < 18) {
			flag = true;
			cout << olimpi[j].fullname << '\n';
			cout << olimpi[j].timName << '\n';
			cout << olimpi[j].kapName << '\n';
			cout << olimpi[j].GTO << '\n';
			cout << olimpi[j].beathday << '\n';
			cout << '\n';
		}
	}
	if (!flag) {
		cout << "Таких участников нет\n";
	}
	cout << '\n';

	cout << "Участники, у которых есть золотой значок ГТО:\n";
	flag = false;
	for (int j = 0; j < i; j++) {
		if (!strcmp(olimpi[j].GTO, "Да")) {
			flag = true;
			cout << olimpi[j].fullname << '\n';
			cout << olimpi[j].timName << '\n';
			cout << olimpi[j].kapName << '\n';
			cout << olimpi[j].GTO << '\n';
			cout << olimpi[j].beathday << '\n';
			cout << '\n';
		}
	}
	if (!flag) {
		cout << "Таких участников нет\n";
	}
	cout << '\n';

	cout << "Участники, которые являются капитанами:\n";
	flag = false;
	for (int j = 0; j < i; j++) {
		if (!(strcmp(olimpi[j].fullname, olimpi[j].kapName))) {
			flag = true;
			cout << olimpi[j].fullname << '\n';
			cout << olimpi[j].timName << '\n';
			cout << olimpi[j].kapName << '\n';
			cout << olimpi[j].GTO << '\n';
			cout << olimpi[j].beathday << '\n';
			cout << '\n';
		}
	}
	if (!flag) {
		cout << "Таких участников нет\n";
	}
	cout << '\n';
	
	File.close();
}


void menu(Student *stud, int a) {
	cout << "Введите 1, если хотите создать новую запись о студенте\n";
	cout << "Введите 2, если хотите внести изменения в уже имеющуюся запись\n";
	cout << "Введите 3, если хотите вывести все данные о студентах\n";
	cout << "Введите 4, если хотите вывести информацию о студентах группы N\n";
	cout << "Введите 5, если хотите вывести информацию о студентах по среднему баллу за сессию \n";
	cout << "Введите 6, если хотите вывести количество студентов мужского и женского пола\n";
	cout << "Введите 7, если хотите вывести данные о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»\n";
	cout << "Введите 8, если хотите вывести данные о студентах, имеющих номер в списке k\n";
	cout << "Введите 9, если хотите вывести идз\n";
	cout << "Введите 0, если хотите выйти из программы\n";
	int num;
	cin >> num;
	switch (num) {
	case 1:
		system("cls");
		a = newEntry(stud, a);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 2:
		system("cls");
		a = reversStud(stud, a);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 3:
		system("cls");
		structPrint(a, stud);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 4:
		system("cls");
		groupPrint(stud, a);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 5:
		system("cls");
		topStudent(stud, a);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 6:
		system("cls");
		mailFemail(stud, a);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 7:
		system("cls");
		numbers(stud, a);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 8:
		system("cls");
		studId(stud, a);
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 9:
		system("cls");
		idz();
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	case 0:
		break;
	default:
		cout << "Введено неправильное число\n";
		system("Pause");
		system("cls");
		menu(stud, a);
		break;
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	struct Student stud[N];
	int a = changeEntry(stud);
	menu(stud, a);
	cout << "\n\n";
	return 0;
}



