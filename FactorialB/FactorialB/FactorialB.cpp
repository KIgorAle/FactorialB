// FactorialB.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <stdio.h>

struct Result {
	int *res;
	int size;
};

struct FResult {
	int *numb1;
	int *numb2;
	int size1;
	int size2;
	int number;
};

Result multiply(int number1[], int number2[], int size_number1, int size_number2)
{
	int length = size_number1 + size_number2 + 1;
	int *subresult = new int[length] {0, }, *result = new int[length] {0, };
	int integer = 0;

	for (int j = 0; j < size_number2; j++)
	{
		for (int i = 0; i < size_number1; i++)
		{
			subresult[i + j] = (number1[i] * number2[j] + integer) % 10;
			//�������
			integer = (number1[i] * number2[j] + integer) / 10;
			//�����, �������
		}

		if (integer > 0) //��������� ����
		{
			subresult[size_number1 + j] = integer; //�������� ������ � ����������         <--- �����
			integer = 0;
		}

		for (int i = 0; i <= size_number1 + j; i++) //�������� ��������
		{
			int temp = (result[i] + subresult[i] + integer) % 10;
			integer = (result[i] + subresult[i] + integer) / 10;
			result[i] = temp;

			subresult[i] = 0;
		}

	}

	int leadnull = -1;
	bool check = false;

	for (int i = 0; i < length; i++) //�������� �� ���������� ����
	{
		if (check == false)
		{
			if (result[i] == 0)
			{
				leadnull = i;
				check = true;
			}
		}
		else
		{
			if (result[i] != 0)
			{
				check = false;
			}
		}

	}

	length = leadnull; //��������� ������, ��� �����������

	int *finalresult = new int[length];       // 
	memcpy(finalresult, result, length * sizeof(int)); //��������� ��������� �� ��������� ������ (�� ���� ��������)

	Result final;
	final.res = new int[length];
	memcpy(final.res, finalresult, length * sizeof(int));
	final.size = length;


	return final;
}

FResult factorial(FResult old_result)
{
	FResult final;
	FResult final2;
	FResult final3;

	if (old_result.number == 0)
	{
		int number1[] = { 1 };

		int number2[] = { 1 };

		final.numb1 = new int[1];
		memcpy(final.numb1, number1, 1 * sizeof(int));

		final.numb2 = new int[1];
		memcpy(final.numb2, number2, 1 * sizeof(int));

		final.size1 = 1;
		final.size2 = 1;
		final.number = -1;

		return final;
	}
	else
	{
		int number2[] = { old_result.number % 10,old_result.number / 10 }; //�������� ���������� ����� � ������ ���� ��� ��������

		final2.number = old_result.number - 1; //���� ����������� ��������� n-1

		final3 = factorial(final2); // ������� ������ (n-1)!



		Result subfinal;
		subfinal = multiply(final3.numb1, number2, final3.size1, 2);    // ��������� n ������� �� ����� n+1

		final.numb1 = new int[subfinal.size];
		memcpy(final.numb1, subfinal.res, subfinal.size * sizeof(int));

		final.numb2 = new int[2];
		memcpy(final.numb2, number2, 2 * sizeof(int));

		final.size1 = subfinal.size;
		final.size2 = 2; //<----
		final.number = old_result.number - 1;

		return final;
	}
}

int main()
{
	FResult final;
	FResult final2;

	printf("Vvedite celoe chislo ot 0 do 30\n");
	scanf("%d", &final.number);

	final2 = factorial(final);

	printf("Faktorial %d: \n", final.number);
	for (int i = final2.size1 - 1; i >= 0; i--) //����� ����������
	{
		printf("%d", final2.numb1[i]);
	}

	int s;
	scanf("%d", &s); //���� ������� �� �����������


	return 0;
}
