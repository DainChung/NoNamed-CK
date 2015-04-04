#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
�뷫���� Ʋ�Դϴ�. �����ϰ� �����ðų� �߰��ϰ� �����ø� �����Ӱ� ���ֽõ�, �ּ����� �̷��̷��� ���̵���Դϴ�
��� ���ּ����� �մϴ�.
*/

int Intro();
int RandomNumGenerater(int value);
int OnTheGame(int turn);
void IsThereSameCard();

void main()
{
	int mainChoice = 0;

	int whosTurn = 0; // whosTurn%2�� ���� 0 == ���� ����, 1 == ����� ����


	srand((unsigned)time(NULL));

	while (1)//���� ����
	{
		if (Intro() == 1)
			break;

		if (OnTheGame(whosTurn) == 0){
			printf("������ �¸��Ͽ����ϴ�!\n");
			continue;
		}
		else if (OnTheGame(whosTurn) == 1){
			printf("����ڰ� �¸��Ͽ����ϴ�!\n");
			continue;
		}
		whosTurn++;
	}



	return;
}

int Intro()
{
	int choice;

	while (1)
	{
		printf("���� ���ӿ� ���� ���� ȯ���մϴ�.\n");
		printf("������ �����Ͻ÷��� 0, �����÷��� 1�� �����ֽʽÿ�. : ");
		scanf("%d", &choice);

		if (choice == 0 || choice == 1)
			break;
		else
			printf("�ٽ� �Է����ֽʽÿ�.\n");
	}

	return choice;
}

int RandomNumGenerater(int value)
{
	int random = 0;

	random = rand() % value + 1;

	if (random >= 11)
		random = 10;

	return random;
}

int OnTheGame(int turn)
{
	//������ �޴� ī��
	int dillCardShape[10] = { 0 };//1 == ,�����̵�, 2 == Ŭ�ι�, 3 == ��Ʈ, 4 == ���̾�
	int dillCardNum[10] = { 0 };

	static int dillCardIndex = 0;

	//����ڰ� �޴� ī��
	int cardShape[10] = { 0 };
	int cardNum[10] = { 0 };

	static int userCardIndex = 0;

	int sumOfCardNum = 0;

	int whosWins = 0;// 0�� ���� ���, 1�� ����� ���
	
	//������ ���� ����
	if (turn % 2 == 0){

		//RandomNumGenerater�� 4�� �־� 4������ ������ ���� ī���� ������ ����
		dillCardShape[dillCardIndex] = RandomNumGenerater(4);
		//RandomNumGenerater�� 13�� �־� 13������ ������ ���� ī���� ���� ����
		dillCardNum[dillCardIndex] = RandomNumGenerater(4);

		if (dillCardShape == 0 || dillCardNum == 0)
			printf("�ý��� ������ �߻��߽��ϴ�.\n");

		//���� �ִ� ī���� ���� ��� ����
		if (dillCardIndex >= 1){
			for (int i = 0; i < dillCardIndex; i++){
				sumOfCardNum += dillCardNum[i];
			}
		}

		dillCardIndex++;
	}
	else{
		//RandomNumGenerater�� 4�� �־� 4������ ������ ���� ī���� ������ ����
		cardShape[userCardIndex] = RandomNumGenerater(4);
		//RandomNumGenerater�� 13�� �־� 13������ ������ ���� ī���� ���� ����
		cardNum[userCardIndex] = RandomNumGenerater(4);


		if (cardShape == 0 || cardNum == 0)
			printf("�ý��� ������ �߻��߽��ϴ�.\n");

		//���� �ִ� ī���� ���� ��� ����
		if (userCardIndex >= 1){
			for (int i = 0; i < userCardIndex; i++){
				sumOfCardNum += cardNum[i];
			}
		}

		userCardIndex++;
	}

		

		//ī�� �� ���� 21�� �Ѵ� ���� �й�
		//ī�� �� ���� 16 �̻��̸� ī�带 �� ������ ������ ����.		
		//ī�� �� ���� 21�� �� ���� ������ �¸�. �� �� 21�̸� ���º�
		//�� �� 20 �����̸� ī�� �� ���� �� ū ���� �¸�.

		//������ ���� ��, �ٽ� �� �� �� ������ ����

		/*
		������ �ΰ������� �� cpp���� �ȿ��� ���� ������ �ٸ� cpp������ ����� �ű⿡�� �����ϰ� ����� ������ �� ������ �ǰ� ���ֽʽÿ�.
		*/

		return whosWins;
}