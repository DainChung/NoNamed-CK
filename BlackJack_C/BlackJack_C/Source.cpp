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
int OnTheGame(int turn);
int IsThereSameCard(struct card* , struct card*);

void main()
{
	int mainChoice = 0;

	int whosTurn = 0; // whosTurn%2의 값이 0 == 딜러 차례, 1 == 사용자 차례


	srand((unsigned)time(NULL));

	while (1)//무한 루프
	{
		if (Intro() == 1)
			break;
		while (1){
			if (OnTheGame(whosTurn) == 0){
				printf("딜러가 승리하였습니다!\n==============================\n\n");
				break;
			}

			else if (OnTheGame(whosTurn) == 1){
				printf("사용자가 승리하였습니다!\n==============================\n\n");
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

int OnTheGame(int turn)
{
	//딜러가 받는 카드
	struct card dillers[10];

	static int dillCardIndex = 0;

	//사용자가 받는 카드
	struct card users[10];

	static int userCardIndex = 0;

	int sumOfCardNum = 0;

	int isSame = 0; //0은 같은 카드 없음, 1은 같은 카드 있음

	int whosWin = 2;// 0은 딜러 우승, 1은 사용자 우승

	//딜러가 먼저 시작
	if (turn % 2 == 0){

		while (1){
			//RandomNumGenerater에 4를 넣어 4가지의 임의의 수로 카드의 문양을 결정
			dillers[dillCardIndex].cardShape = RandomNumGenerater(4);
			//RandomNumGenerater에 13을 넣어 13가지의 임의의 수로 카드의 수를 결정
			dillers[dillCardIndex].cardNum = RandomNumGenerater(13);

			isSame = IsThereSameCard(dillers, users);

			if (isSame == 0)
				break;
		}

		if (dillers[dillCardIndex].cardShape == 0 || dillers[dillCardIndex].cardNum == 0)
			printf("시스템 오류가 발생했습니다.\n");

		//갖고 있는 카드의 수를 모두 더함
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
			//RandomNumGenerater에 4를 넣어 4가지의 임의의 수로 카드의 문양을 결정
			users[userCardIndex].cardShape = RandomNumGenerater(4);
			//RandomNumGenerater에 13을 넣어 13가지의 임의의 수로 카드의 수를 결정
			users[userCardIndex].cardNum = RandomNumGenerater(13);

			isSame = IsThereSameCard(dillers, users);

			if (isSame == 0)
				break;
		}

		if (users[userCardIndex].cardShape == 0 || users[userCardIndex].cardNum == 0)
			printf("시스템 오류가 발생했습니다.\n");

		

		//갖고 있는 카드의 수를 모두 더함
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

		//카드 수 합이 21을 넘는 쪽이 패배
		//카드 수 합이 16 이상이면 카드를 더 받을지 말지를 결정.		
		//카드 수 합이 21이 된 쪽이 무조건 승리. 둘 다 21이면 무승부
		//둘 다 20 이하이면 카드 수 합이 더 큰 쪽이 승리.

		//게임이 끝난 뒤, 다시 할 지 안 할지를 결정

		/*
		딜러의 인공지능을 이 cpp파일 안에서 만들 것인지 다른 cpp파일을 만들고 거기에서 구현하고 여기로 가져다 쓸 것인지 의견 내주십시오.
		*/

		

	return 0;
}

int IsThereSameCard(struct card* pGivenCardDiller, struct card* pGivenCardUser)
{
	int isSame = 0;//0은 같은 카드 없음, 1은 같은 카드 있음

	for (int i = 0; i < 10; i++)
	{
		if (pGivenCardDiller->cardShape != 0 && pGivenCardUser->cardShape != 0)//카드 모양 값이 0이 아니면(초기화된 값 그대로가 아니면)
			if (pGivenCardDiller->cardShape == pGivenCardUser->cardShape)//카드 모양, 값 비교 
				if (pGivenCardDiller->cardNum == pGivenCardUser->cardNum)
					isSame = 1;
	}

	return isSame;
}