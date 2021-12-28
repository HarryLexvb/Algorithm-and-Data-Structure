#include <iostream>

using namespace std;

/*
Realice la función void mezclar(int *a, int *b,int *c) que mezcla los valores un array donde la mitad está poblado de impares ordenados y la otra mitad de pares ordenados. El puntero a apunta al inicio, b a la mitad y c al último elemento.
*/
void intercambio(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
void printArr(int *a, int *c)
{
	for (int *i = a; i - 1 != c; i++)
	{
		cout << *i << ", ";
	}
	cout << endl;
}
void mezclar(int *a, int *b, int *c)
{
	bool flagOdd = false;
	bool flagEven = false;
	if (b != c - 1)
	{
		// if (*c > *(b - 1))
		// {
		if (*(c - 1) < *(b - 1))
		{
			intercambio(c - 1, b - 1);
		}
		// }
		flagEven = true;
	}
	if (a + 1 != b)
	{
		if (*a > *(b - 1))
		{
			intercambio(a, b - 1);
		}

		else if (*b < *(a + 1))
		{
			intercambio(b, a + 1);
		}
		flagOdd = true;
	}
	if (*b > *c)
	{
		intercambio(b, c);
	}
	cout << endl;
	cout << "Odd : " << std::boolalpha << flagOdd << endl;
	cout << "Even : " << std::boolalpha << flagEven << endl;
	cout << "a: " << *a << endl;
	cout << "b: " << *b << endl;
	cout << "c: " << *c << endl;
	printArr(a, c);
	// if (*(b + 1) > *(b - 2))
	// {
	// 	intercambio(b + 1, b - 2);
	// }
	// if (*() > *())
	// {
	// }

	if (flagOdd && flagEven)
	{
		mezclar(a + 1, b, c - 1);
	}
	else if (flagOdd)
	{
		mezclar(a + 1, b, c);
	}
	else if (flagEven)
	{
		mezclar(a, b, c - 1);
	}
}

int main()
{
	int A[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	cout << "Array antes" << endl;
	for (int i = 0; i < 10; i++)
		cout << A[i] << " ";
	cout << endl;
	mezclar(&A[0], &A[5], &A[9]);
	cout << "\n\nArray despues" << endl;
	for (int i = 0; i < 10; i++)
		cout << A[i] << " ";
	cout << endl;
	return 0;
}