#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
�뷫���� Ʋ�Դϴ�. �����ϰ� �����ðų� �߰��ϰ� �����ø� �����Ӱ� ���ֽõ�, �ּ����� �̷��̷��� ���̵���Դϴ�
��� ���ּ����� �մϴ�.
*/

struct card{
	int cardShape = 0;//1 == ,�����̵�, 2 == Ŭ�ι�, 3 == ��Ʈ, 4 == ���̾�
	int cardNum = 0;
};

int Intro();
int RandomNumGenerater(int value);
int OnTheGame(int turn);
int IsThereSameCard(struct card* , struct card*);

void main()
{
	int mainChoice = 0;

	int whosTurn = 0; // whosTurn%2�� ���� 0 == ���� ����, 1 == ����� ����


	srand((unsigned)time(NULL));

	while (1)//���� ����
	{
		if (Intro() == 1)
			break;
		while (1){
			if (OnTheGame(whosTurn) == 0){
				printf("������ �¸��Ͽ����ϴ�!\n==============================\n\n");
				break;
			}

			else if (OnTheGame(whosTurn) == 1){
				printf("����ڰ� �¸��Ͽ����ϴ�!\n==============================\n\n");
				break;
			}
		}

		whosTurn++;
	}



	return;
}

int Intro()
{
	int choice = 0;

	while (1)
	{
		printf("���� ���ӿ� ���� ���� ȯ���մϴ�.\n");
		printf("������ �����Ͻ÷��� 0, �����÷��� 1�� �����ֽʽÿ�. : ");
		scanf("%d", &choice);

		if (choice == 0 || choice == 1)
			break;
		else
			printf("�ٽ� �Է����ֽʽÿ�.\n\n\n");
	}

	return choice;
}

int RandomNumGenerater(int value)
{
	int random = 0;

	random = rand() % value + 1;

	return random;
}

int OnTheGame(int turn)
{
	//������ �޴� ī��
	struct card dillers[10];

	static int dillCardIndex = 0;

	//����ڰ� �޴� ī��
	struct card users[10];

	static int userCardIndex = 0;

	int sumOfCardNum = 0;

	int isSame = 0; //0�� ���� ī�� ����, 1�� ���� ī�� ����

	int whosWin = 2;// 0�� ���� ���, 1�� ����� ���

	//������ ���� ����
	if (turn % 2 == 0){

		while (1){
			//RandomNumGenerater�� 4�� �־� 4������ ������ ���� ī���� ������ ����
			dillers[dillCardIndex].cardShape = RandomNumGenerater(4);
			//RandomNumGenerater�� 13�� �־� 13������ ������ ���� ī���� ���� ����
			dillers[dillCardIndex].cardNum = RandomNumGenerater(13);

			isSame = IsThereSameCard(dillers, users);

			if (isSame == 0)
				break;
		}

		if (dillers[dillCardIndex].cardShape == 0 || dillers[dillCardIndex].cardNum == 0)
			printf("�ý��� ������ �߻��߽��ϴ�.\n");

		//���� �ִ� ī���� ���� ��� ����
		if (dillCardIndex >= 1){
			for (int i = 0; i < dillCardIndex; i++){
				if (dillers[i].cardNum >= 11)
					sumOfCardNum += 10;
				else
					sumOfCardNum += dillers[i].cardNum;
			}
		}

		dillCardIndex++;
	}
	else{
		while (1){
			//RandomNumGenerater�� 4�� �־� 4������ ������ ���� ī���� ������ ����
			users[userCardIndex].cardShape = RandomNumGenerater(4);
			//RandomNumGenerater�� 13�� �־� 13������ ������ ���� ī���� ���� ����
			users[userCardIndex].cardNum = RandomNumGenerater(13);

			isSame = IsThereSameCard(dillers, users);

			if (isSame == 0)
				break;
		}

		if (users[userCardIndex].cardShape == 0 || users[userCardIndex].cardNum == 0)
			printf("�ý��� ������ �߻��߽��ϴ�.\n");

		

		//���� �ִ� ī���� ���� ��� ����
		if (userCardIndex >= 1){
			for (int i = 0; i < userCardIndex; i++){
				if (users[i].cardNum >= 11)
					sumOfCardNum += 10;
				else
					sumOfCardNum += users[i].cardNum;
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

		

	return 0;
}

int IsThereSameCard(struct card* pGivenCardDiller, struct card* pGivenCardUser)
{
	int isSame = 0;//0�� ���� ī�� ����, 1�� ���� ī�� ����

	for (int i = 0; i < 10; i++)
	{
		if (pGivenCardDiller->cardShape != 0 && pGivenCardUser->cardShape != 0)//ī�� ��� ���� 0�� �ƴϸ�(�ʱ�ȭ�� �� �״�ΰ� �ƴϸ�)
			if (pGivenCardDiller->cardShape == pGivenCardUser->cardShape)//ī�� ���, �� �� 
				if (pGivenCardDiller->cardNum == pGivenCardUser->cardNum)
					isSame = 1;
	}

	return isSame;
}