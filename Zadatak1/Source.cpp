#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

struct Kordinata {
	int x, y;
};

const int redak = 20;
const int stupac = 40;

void sredivanjeIgraca(Kordinata &igrac,Kordinata &kraj ,char grid[redak][stupac], char slucaj) {
	if (slucaj == 'x')
	{
		for (size_t i = 0; i < redak; i++)
		{
			for (size_t j = 0; j < stupac; j++)
			{
				if (igrac.x == j && igrac.y == i)
				{
					cout << 'x';
				}
				else
				{
					cout << grid[i][j];
				}

			}
			cout << endl;
		}
		if (igrac.x < kraj.x)
		{
			igrac.x++;
		}
		else if (igrac.x > kraj.x)
		{
			igrac.x--;
		}
	}
	else
	{
		for (size_t i = 0; i < redak; i++)
		{
			for (size_t j = 0; j < stupac; j++)
			{
				if (igrac.x == j && igrac.y == i)
				{
					cout << 'x';
				}
				else
				{
					cout << grid[i][j];
				}

			}
			cout << endl;
		}
		if (igrac.y < kraj.y)
		{
			igrac.y++;
		}
		else if (igrac.y > kraj.y)
		{
			igrac.y--;
		}
	}
	
}

int main() {
	
	
	int A[2], B[2];
	cout << "Unesi A redak: ";
	cin >> A[0];
	cout << "Unesi A stupac: ";
	cin >> A[1];

	cout << "Unesi B redak: ";
	cin >> B[0];
	cout << "Unesi B stupac: ";
	cin >> B[1];

	/*
		1.Provjeriti x kordinate unesenih tocki
			Ako je x1 manji od x2 onda salji desno, a ako je x1
			veci od x2 onda salji ljevo
		1.2.Ici na x kordinatu sve dok nije x1 = x2
		
		2.Provjeriti y kordinate unesenih tocki
			Ako je y1 manji od x2 onda salji dole, a ako je x1
			veci od x2 onda salji gore
		2.2.Ici na y kordinatu sve dok nije y1 = y2
		*/


	char grid[redak][stupac];

	//Pocetno stanje
	for (int i = 0; i < redak; i++)
	{
		
		for (int j = 0; j < stupac; j++)
		{
			if (A[0] - 1 == i && A[1] - 1 == j)
			{
				grid[i][j] = 'A';
			}
			else if (B[0] - 1 == i && B[1] - 1 == j)
			{
				grid[i][j] = 'B';
			}
			else
			{
				grid[i][j] = '-';
			}
		}
					
	}

	Kordinata igrac;
	igrac.x = A[1] - 1;
	igrac.y = A[0] - 1;

	Kordinata kraj;
	kraj.x = B[1] - 1;
	kraj.y = B[0] - 1;

	//Inicijalno crtanje
	for (size_t i = 0; i < redak; i++)
	{
		for (size_t j = 0; j < stupac; j++)
		{
			cout << grid[i][j];
		}
		cout << endl;
	}

	//Sredivanje X kordinate
	while (igrac.x != kraj.x)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		system("cls");
		cout << endl << endl;
		sredivanjeIgraca(igrac, kraj, grid, 'x');
		
	}

	//Sredivanje Y kordinate
	while (igrac.y != kraj.y)
	{
		this_thread::sleep_for(chrono::milliseconds(100));
		system("cls");
		cout << endl << endl;
		sredivanjeIgraca(igrac, kraj, grid, 'y');


	}

	return 0;
}