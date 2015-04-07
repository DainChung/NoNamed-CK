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

int OnTheGame();

int IsThereSameCard(struct card* , struct card*);

int FindWinner(int, int);

void main()
{
	int mainChoice = 0;

	int whosWin = 3;

	srand((unsigned)time(NULL));

	while (1)//���� ����
	{
		if (Intro() == 1)
			break;

		whosWin = OnTheGame();

		if (whosWin == 0)
			printf("\n������ �¸��Ͽ����ϴ�!\n==============================\n\n");
		else if (whosWin == 1)
			printf("\n����ڰ� �¸��Ͽ����ϴ�!\n==============================\n\n");
		else if (whosWin == 2)
			printf("\n���º��Դϴ�!\n==============================\n\n");
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

int OnTheGame()
{
	int turn = 0;

	struct card dillers[10];//������ �޴� ī��
	int dillCardIndex = 0;

	struct card users[10];//����ڰ� �޴� ī��
	int userCardIndex = 0;

	int isSame = 0; //0�� ���� ī�� ����, 1�� ���� ī�� ����

	//ī�� �� ���� ������ ����
	int sumOfUsers = 0;
	int sumOfDillers = 0;

	//�� �޴°� �� �޴°�
	int dillerStay = 0;//0�� ����, 1�� �� ����
	int userStay = 0;

	int whosWin = 3;// 0�� ���� ���, 1�� ����� ���, 2�� ���º�

	while (1){
		//������ ���� ����
		if (turn % 2 == 0){

			if (dillerStay != 1){
				while (1){
					//RandomNumGenerater�� 4�� �־� 4������ ������ ���� ī���� ������ ����
					dillers[dillCardIndex].cardShape = RandomNumGenerater(4);
					//RandomNumGenerater�� 13�� �־� 13������ ������ ���� ī���� ���� ����
					dillers[dillCardIndex].cardNum = RandomNumGenerater(13);

					isSame = IsThereSameCard(dillers, users);

					if (isSame == 0)
						break;
				}

				if ((dillers[dillCardIndex].cardShape == 0) || (dillers[dillCardIndex].cardNum == 0))
					printf("�ý��� ������ �߻��߽��ϴ�.\n");

				//���� �ִ� ī���� ���� ��� ����
				if (dillers[dillCardIndex].cardNum >= 11)
					sumOfDillers += 10;
				else 
					sumOfDillers += dillers[dillCardIndex].cardNum;

				//ī���� �� ���� 16�̻� 21�̸� �Ǵ� 21, 21�ʰ����� �Ǻ�
				if ((sumOfDillers >= 17) && (sumOfDillers <= 20)){
					printf("������ �����̸� ���ƽ��ϴ�!\n\n");
					dillerStay = 1;
				}

				dillCardIndex++;
			}
		}



		else{
			if (userStay != 1){
				while (1){
					//RandomNumGenerater�� 4�� �־� 4������ ������ ���� ī���� ������ ����
					users[userCardIndex].cardShape = RandomNumGenerater(4);
					//RandomNumGenerater�� 13�� �־� 13������ ������ ���� ī���� ���� ����
					users[userCardIndex].cardNum = RandomNumGenerater(13);

					isSame = IsThereSameCard(dillers, users);

					if (isSame == 0)
						break;
				}

				if ((users[userCardIndex].cardShape == 0) || (users[userCardIndex].cardNum == 0))
					printf("�ý��� ������ �߻��߽��ϴ�.\n");



				//���� �ִ� ī���� ���� ��� ����
				if (users[userCardIndex].cardNum >= 11)
					sumOfUsers += 10;
				else
					sumOfUsers += users[userCardIndex].cardNum;

				printf("\n���� ī�� ���� �� ��: %d \n", sumOfUsers);

				//ī���� �� ���� 16�̻� 21�̸� �Ǵ� 21, 21�ʰ����� �Ǻ�
				if ((sumOfUsers >= 16) && (sumOfUsers < 21)){
					printf("\n�� �����÷��� 0��, �׸� �����÷��� 1�� �Է��Ͻʽÿ�: ");
					scanf("%d", &userStay);
					printf("\n");
				}


				userCardIndex++;
			}
		}
		if ((userStay == 1) && (dillerStay == 1))
			whosWin = FindWinner(sumOfDillers, sumOfUsers);

		if (sumOfDillers > 21)
			whosWin = 1;
		else if (sumOfUsers > 21)
			whosWin = 0;
		
		if ((sumOfDillers > 21) && (sumOfUsers > 21))
			whosWin = 2;

		if (whosWin != 3)
			break;

		/*
		������ �ΰ������� �� cpp���� �ȿ��� ���� ������ �ٸ� cpp������ ����� �ű⿡�� �����ϰ� ����� ������ �� ������ �ǰ� ���ֽʽÿ�.
		*/

		turn++;
	}
	
	printf("\n������ ī�� �� ��: %d\n\n", sumOfDillers);

	return whosWin;
}

int IsThereSameCard(struct card* pGivenCardDiller, struct card* pGivenCardUser)
{
	int isSame = 0;//0�� ���� ī�� ����, 1�� ���� ī�� ����

	for (int i = 0; i < 10; i++)
	{
		if ((pGivenCardDiller->cardShape != 0) && (pGivenCardUser->cardShape != 0))//ī�� ��� ���� 0�� �ƴϸ�(�ʱ�ȭ�� �� �״�ΰ� �ƴϸ�)
			if ((pGivenCardDiller->cardShape) == (pGivenCardUser->cardShape))//ī�� ���, �� �� 
				if ((pGivenCardDiller->cardNum) == (pGivenCardUser->cardNum))
					isSame = 1;
	}

	return isSame;
}

int FindWinner(int diller, int user){

	int whoWins = 3;// 0�̸� ���� ���, 1�̸� ����� ���, 2�� ���º�

	if (diller == user)
		whoWins = 2;
	else if (user == 21)
		whoWins = 1;
	else if (diller == 21)
		whoWins = 0;
	else{
		if ((20 - user) < (20 - diller))
			whoWins = 1;
		else if ((20 - user) > (20 - diller))
			whoWins = 0;
	}

	return whoWins;
}