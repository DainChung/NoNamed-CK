#define _CRT_SECURE_NO_WARNINGS
#define MAXIMUM	100

/*
�߰��� �� �� ���� ������ ���� ��ġ�� Ƣ�� ��찡 ����. �ε��� ���� �߸� �����߰ų� ���� ����.
�Ǵ� �迭 ������ �Ѿ�� ���� ����.
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//void MakeRandomData(int *data);
void WriteDataToText(FILE *fp, int *data);
void SortData(int *data, int number);

void main()
{
	int data[MAXIMUM] = { 0, };
	FILE *fp = NULL;

	srand((unsigned)time(NULL));

	int index = 0;
	int temp;

	for (index = 0; index < MAXIMUM; index++)
	{
		temp = rand() % MAXIMUM;
		//printf("%d \n",temp);
		data[index] = temp;
	}

	//MakeRandomData(data);
	WriteDataToText(fp, data);
	SortData(data, 1);
	WriteDataToText(fp, data);

	
	int j = 0;

	for (int i = 0; i < 1000; i++)
	{

		printf("%4d ", data[i]);
			if (j >= 10)
			{
				printf("\n");
				j = 0;
			}
		j++;
	}

}
/*
void MakeRandomData(int *data)
{
	
}
*/
void WriteDataToText(FILE *fp, int *data)
{
	int i;
	int j = 0;

	fp = fopen("output.txt", "w");

	printf("sort.text ���Ͽ� ������ �����մϴ�.\n");

	for (i = 0; i < MAXIMUM; i++)
	{
		fprintf(fp, "%5d ", *(data));
		data++;
		j++;

		//�� ����
		if (j >= 10)
		{
			printf("\n");
			j = 0;
		}
	}
}

void SortData(int *data, int number)
{
	int dataQ[10][MAXIMUM] = { 0, };

	int _1stIndex, _2ndIndex;

	int temp;

	//������ Q�� ��� ������ -1�� �ʱ�ȭ
	for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
	{ 
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			dataQ[_1stIndex][_2ndIndex] = -1;
		}
	}

	switch (number)
	{
	case 1://1�� �ڸ��� ����
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			temp = *(data) % 10;
			data++;

			for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
			{
				if (dataQ[temp][_2ndIndex] == -1)
				{
					dataQ[temp][_2ndIndex] = *(data);
					break;
				}
			}
		}

		//Q�� ���ĵ� �����ͷ� �ٽ� �迭
		for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
		{
			for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
			{
				if (dataQ[_1stIndex][_2ndIndex] != -1)
				{
					data = &(dataQ[_1stIndex][_2ndIndex]);
					data++;
				}
			}
		}

		SortData(data, 2);
		break;
	case 2://10�� �ڸ��� ����
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			temp = (*(data) % 100) / 10;
			data++;

			for (_1stIndex = 0; _1stIndex< 10; _1stIndex++)
			{
				if (dataQ[temp][_2ndIndex] == -1)
				{
					dataQ[temp][_2ndIndex] = *(data);
					break;
				}
			}
		}
		//Q�� ���ĵ� �����ͷ� �ٽ� �迭
		for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
		{
			for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
			{
				if (dataQ[_1stIndex][_2ndIndex] != -1)
				{
					data = &(dataQ[_1stIndex][_2ndIndex]);
					data++;
				}
			}
		}

		SortData(data, 3);
		break;
	case 3://100�� �ڸ��� ����
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			temp = (*(data) % 1000) / 100;
			data++;

			for (_1stIndex = 0; _1stIndex< 10; _1stIndex++)
			{
				if (dataQ[temp][_2ndIndex] == -1)
				{
					dataQ[temp][_2ndIndex] = *(data);
					break;
				}
			}
		}
		//Q�� ���ĵ� �����ͷ� �ٽ� �迭
		for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
		{
			for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
			{
				if (dataQ[_1stIndex][_2ndIndex] != -1)
				{
					data = &(dataQ[_1stIndex][_2ndIndex]);
					data++;
				}
			}
		}
		SortData(data, 4);
		break;
	/*case 4://1000�� �ڸ��� ����
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			temp = (*(data) % 10000)/1000;
			data++;

			for (_1stIndex = 0; _1stIndex< 10; _1stIndex++)
			{
				if (dataQ[temp][_2ndIndex] == -1)
				{
					dataQ[temp][_2ndIndex] = *(data);
					break;
				}
			}
		}
		//Q�� ���ĵ� �����ͷ� �ٽ� �迭
		for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
		{
			for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
			{
				if (dataQ[_1stIndex][_2ndIndex] != -1)
				{
					data = &(dataQ[_1stIndex][_2ndIndex]);
					data++;
				}
			}
		}
		SortData(data, 5);
		break;
	case 5://10000�� �ڸ��� ����
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			temp = (*(data) % MAXIMUM) / 10000;
			data++;

			for (_1stIndex = 0; _1stIndex< 10; _1stIndex++)
			{
				if (dataQ[temp][_2ndIndex] == -1)
				{
					dataQ[temp][_2ndIndex] = *(data);
					break;
				}
			}
		}
		//Q�� ���ĵ� �����ͷ� �ٽ� �迭
		for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
		{
			for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
			{
				if (dataQ[_1stIndex][_2ndIndex] != -1)
				{
					data = &(dataQ[_1stIndex][_2ndIndex]);
					data++;
				}
			}
		}
		SortData(data, 6);
		break;
	case 6://100000�� �ڸ��� ����
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			temp = *(data) / MAXIMUM;
			data++;

			for (_1stIndex = 0; _1stIndex< 10; _1stIndex++)
			{
				if (dataQ[temp][_2ndIndex] == -1)
				{
					dataQ[temp][_2ndIndex] = *(data);
					break;
				}
			}
		}
		//Q�� ���ĵ� �����ͷ� �ٽ� �迭
		for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
		{
			for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
			{
				if (dataQ[_1stIndex][_2ndIndex] != -1)
				{
					data = &(dataQ[_1stIndex][_2ndIndex]);
					data++;
				}
			}
		}
		SortData(data, 0);
		break;*/

	default:
		break;
	}
}