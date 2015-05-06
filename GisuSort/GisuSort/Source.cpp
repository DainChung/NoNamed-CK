#define _CRT_SECURE_NO_WARNINGS
#define MAXIMUM	100000

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

long data[MAXIMUM] = { 0, };

//void MakeRandomData(int *data);
void WriteDataToText(FILE *fp, int number);
int SortData(int number);

void main()
{
	FILE *fp = NULL;

	srand((unsigned)time(NULL));

	int index = 0;
	long temp;
	int dump;

	//������ ������ ����


	for (index = 0; index < MAXIMUM; index++)
	{
		temp = (((long)rand() << 15) | rand()) % MAXIMUM; // ���� ���� ���� ������ �ø���(20��Ʈ���� ǥ�� ����)
		//printf("%d \n",temp);
		data[index] = temp;
	}

	WriteDataToText(fp, 0);
	dump = SortData(0);
	WriteDataToText(fp, 1);
}

void WriteDataToText(FILE *fp, int number)
{
	int i;
	int j = 0;

	if (number == 0)
	{
		fp = fopen("input.txt", "w");
		printf("input.txt ���Ͽ� ������ �����մϴ�.\n");
	}
	else
	{
		fp = fopen("output.txt", "w");
		printf("output.txt ���Ͽ� ������ �����մϴ�.\n");
	}

	for (i = 0; i < MAXIMUM; i++)
	{
		fprintf(fp, "%6d", data[i]);
		j++;

		//�� ����
		if (j == 10)
		{
			fprintf(fp, "\n");
			j = 0;
		}
	}
}

int SortData(int number)
{
	long dataQ[10][MAXIMUM] = { 0, };

	int _1stIndex, _2ndIndex, helperIndex;

	long temp;
	int tempHelper = 1;
	
	//������ Q�� ��� ������ -1�� �ʱ�ȭ
	for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
	{ 
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			dataQ[_1stIndex][_2ndIndex] = -1;
		}
	}
	
	//�ڸ����� �����ϱ� ���� ���� �� ����
	if (number != 0)
	{
		for (int helper = 0; helper < number; helper++)
		{
			tempHelper *= 10;
		}
	}
	else
		tempHelper = 1;


	//�ڸ��� ���� �� ����
	for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
	{
		temp = (long)((data[_2ndIndex] % (tempHelper * 10)) / tempHelper);

		for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
		{
			if (dataQ[temp][_2ndIndex] == -1)
			{
				dataQ[temp][_2ndIndex] = data[_2ndIndex];
				break;
			}
		}
	}

	helperIndex = 0;

	//Q�� ���ĵ� �����ͷ� �ٽ� �迭
	for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
	{
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			if (dataQ[_1stIndex][_2ndIndex] != -1)
			{
				data[helperIndex] = dataQ[_1stIndex][_2ndIndex];
				helperIndex++;
			}
		}
	}

	if (number <= 5)
		return SortData(++number);
	else
		return 0;
}