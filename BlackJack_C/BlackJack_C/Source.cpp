#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
대략적인 틀입니다. 수정하고 싶으시거나 추가하고 싶으시면 자유롭게 써주시되, 주석으로 이러이러항 아이디어입니다
라고 써주셨으면 합니다.
*/

struct card{
	int cardShape = 0;//1 == ,스페이드, 2 == 클로버, 3 == 하트, 4 == 다이아
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

	while (1)//무한 루프
	{
		if (Intro() == 1)
			break;

		whosWin = OnTheGame();

		if (whosWin == 0)
			printf("\n딜러가 승리하였습니다!\n==============================\n\n");
		else if (whosWin == 1)
			printf("\n사용자가 승리하였습니다!\n==============================\n\n");
		else if (whosWin == 2)
			printf("\n무승부입니다!\n==============================\n\n");
	}



	return;
}

int Intro()
{
	int choice = 0;

	while (1)
	{
		printf("블랙잭 게임에 오신 것을 환영합니다.\n");
		printf("게임을 진행하시려면 0, 끝내시려면 1을 눌러주십시오. : ");
		scanf("%d", &choice);

		if (choice == 0 || choice == 1)
			break;
		else
			printf("다시 입력해주십시오.\n\n\n");
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

	struct card dillers[10];//딜러가 받는 카드
	int dillCardIndex = 0;

	struct card users[10];//사용자가 받는 카드
	int userCardIndex = 0;

	int isSame = 0; //0은 같은 카드 없음, 1은 같은 카드 있음

	//카드 수 합을 저장할 변수
	int sumOfUsers = 0;
	int sumOfDillers = 0;

	//더 받는가 안 받는가
	int dillerStay = 0;//0은 받음, 1은 안 받음
	int userStay = 0;

	int whosWin = 3;// 0은 딜러 우승, 1은 사용자 우승, 2는 무승부

	while (1){
		//딜러가 먼저 시작
		if (turn % 2 == 0){

			if (dillerStay != 1){
				while (1){
					//RandomNumGenerater에 4를 넣어 4가지의 임의의 수로 카드의 문양을 결정
					dillers[dillCardIndex].cardShape = RandomNumGenerater(4);
					//RandomNumGenerater에 13을 넣어 13가지의 임의의 수로 카드의 수를 결정
					dillers[dillCardIndex].cardNum = RandomNumGenerater(13);

					isSame = IsThereSameCard(dillers, users);

					if (isSame == 0)
						break;
				}

				if ((dillers[dillCardIndex].cardShape == 0) || (dillers[dillCardIndex].cardNum == 0))
					printf("시스템 오류가 발생했습니다.\n");

				//갖고 있는 카드의 수를 모두 더함
				if (dillers[dillCardIndex].cardNum >= 11)
					sumOfDillers += 10;
				else 
					sumOfDillers += dillers[dillCardIndex].cardNum;

				//카드의 수 합이 16이상 21미만 또는 21, 21초과인지 판별
				if ((sumOfDillers >= 17) && (sumOfDillers <= 20)){
					printf("딜러가 스테이를 외쳤습니다!\n\n");
					dillerStay = 1;
				}

				dillCardIndex++;
			}
		}



		else{
			if (userStay != 1){
				while (1){
					//RandomNumGenerater에 4를 넣어 4가지의 임의의 수로 카드의 문양을 결정
					users[userCardIndex].cardShape = RandomNumGenerater(4);
					//RandomNumGenerater에 13을 넣어 13가지의 임의의 수로 카드의 수를 결정
					users[userCardIndex].cardNum = RandomNumGenerater(13);

					isSame = IsThereSameCard(dillers, users);

					if (isSame == 0)
						break;
				}

				if ((users[userCardIndex].cardShape == 0) || (users[userCardIndex].cardNum == 0))
					printf("시스템 오류가 발생했습니다.\n");



				//갖고 있는 카드의 수를 모두 더함
				if (users[userCardIndex].cardNum >= 11)
					sumOfUsers += 10;
				else
					sumOfUsers += users[userCardIndex].cardNum;

				printf("\n현재 카드 수의 총 합: %d \n", sumOfUsers);

				//카드의 수 합이 16이상 21미만 또는 21, 21초과인지 판별
				if ((sumOfUsers >= 16) && (sumOfUsers < 21)){
					printf("\n더 받으시려면 0을, 그만 받으시려면 1을 입력하십시오: ");
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
		딜러의 인공지능을 이 cpp파일 안에서 만들 것인지 다른 cpp파일을 만들고 거기에서 구현하고 여기로 가져다 쓸 것인지 의견 내주십시오.
		*/

		turn++;
	}
	
	printf("\n딜러의 카드 수 합: %d\n\n", sumOfDillers);

	return whosWin;
}

int IsThereSameCard(struct card* pGivenCardDiller, struct card* pGivenCardUser)
{
	int isSame = 0;//0은 같은 카드 없음, 1은 같은 카드 있음

	for (int i = 0; i < 10; i++)
	{
		if ((pGivenCardDiller->cardShape != 0) && (pGivenCardUser->cardShape != 0))//카드 모양 값이 0이 아니면(초기화된 값 그대로가 아니면)
			if ((pGivenCardDiller->cardShape) == (pGivenCardUser->cardShape))//카드 모양, 값 비교 
				if ((pGivenCardDiller->cardNum) == (pGivenCardUser->cardNum))
					isSame = 1;
	}

	return isSame;
}

int FindWinner(int diller, int user){

	int whoWins = 3;// 0이면 딜러 우승, 1이면 사용자 우승, 2는 무승부

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