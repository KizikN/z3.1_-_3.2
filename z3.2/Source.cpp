//Компоненты файла f – целые числа, положительных чисел столько же, сколько
//отрицательных.Получить файл g из чисел исходного файла, в котором не было бы
//двух соседних чисел с одинаковым знаком

#include<iostream>
#include<fstream>

using namespace std;

int Get_in(fstream& file_1);
void New_Get_in_new_file(fstream& file_1, ofstream& file_2);

int main()
{
	int n;
	fstream file_1("hi.txt", ios::binary | ios::in | ios::out);
	file_1.clear();

	if (!file_1)
	{
		cout << "error1" << endl;
		return 1;
	}

	n = Get_in(file_1);

	ofstream file_2("bye.txt", ios::binary);
	file_2.clear();

	cout << endl;
	New_Get_in_new_file(file_1, file_2);

	file_1.close();
	file_2.close();
	return 0;
}

int Get_in(fstream& file_1)
{
	int n;
	cout << "n = ";
	cin >> n;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		int v;
		cin >> v;
		file_1.write(reinterpret_cast <char*>(&v), sizeof(int));
	}
	file_1.seekg(0);

	return n;
}

void New_Get_in_new_file(fstream& file_1, ofstream& file_2)
{
	int a{ 0 };
	int b{ 0 };
	file_1.read(reinterpret_cast <char*>(&a), sizeof(int));
	while (file_1.read(reinterpret_cast <char*>(&b), sizeof(int)))
	{
		if (((b < 0 && a < 0) || (b > 0 && a > 0)))
		{
			int c{ 0 };
			if (file_1.read(reinterpret_cast <char*>(&c), sizeof(int)))
			{
				if (((b < 0 && c < 0) || (b > 0 && c > 0)))
					while (file_1.read(reinterpret_cast <char*>(&a), sizeof(int)) && ((c < 0 && a < 0) || (c > 0 && a > 0)))
					{}
				else
				{
					file_2.write(reinterpret_cast <char*>(&a), sizeof(int));
					file_2.write(reinterpret_cast <char*>(&b), sizeof(int));
					cout << a << " ";
					cout << b << " ";
					a = c;
				}
			}
			else
			{
				file_2.write(reinterpret_cast <char*>(&a), sizeof(int));
				file_2.write(reinterpret_cast <char*>(&b), sizeof(int));
				cout << a << " ";
				cout << b << " ";
			}
		}
		else
			a = b;
	}
}