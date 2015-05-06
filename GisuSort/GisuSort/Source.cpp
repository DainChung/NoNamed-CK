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

	//난수로 데이터 생성


	for (index = 0; index < MAXIMUM; index++)
	{
		temp = (((long)rand() << 15) | rand()) % MAXIMUM; // 난수 생성 범위 강제로 늘리기(20비트까지 표현 가능)
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
		printf("input.txt 파일에 정보를 저장합니다.\n");
	}
	else
	{
		fp = fopen("output.txt", "w");
		printf("output.txt 파일에 정보를 저장합니다.\n");
	}

	for (i = 0; i < MAXIMUM; i++)
	{
		fprintf(fp, "%6d", data[i]);
		j++;

		//줄 정리
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
	
	//데이터 Q의 모든 내용을 -1로 초기화
	for (_1stIndex = 0; _1stIndex < 10; _1stIndex++)
	{ 
		for (_2ndIndex = 0; _2ndIndex < MAXIMUM; _2ndIndex++)
		{
			dataQ[_1stIndex][_2ndIndex] = -1;
		}
	}
	
	//자릿수를 추출하기 위한 변수 값 조작
	if (number != 0)
	{
		for (int helper = 0; helper < number; helper++)
		{
			tempHelper *= 10;
		}
	}
	else
		tempHelper = 1;


	//자릿수 추출 및 정렬
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

	//Q에 정렬된 데이터로 다시 배열
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