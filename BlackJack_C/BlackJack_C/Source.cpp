#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
대략적인 틀입니다. 수정하고 싶으시거나 추가하고 싶으시면 자유롭게 써주시되, 주석으로 이러이러항 아이디어입니다
라고 써주셨으면 합니다.
*/

int Intro();
int RandomNumGenerater(int value);
int OnTheGame(int turn);
void IsThereSameCard();

void main()
{
	int mainChoice = 0;

	int whosTurn = 0; // whosTurn%2의 값이 0 == 딜러 차례, 1 == 사용자 차례


	srand((unsigned)time(NULL));

	while (1)//무한 루프
	{
		if (Intro() == 1)
			break;

		if (OnTheGame(whosTurn) == 0){
			printf("딜러가 승리하였습니다!\n");
			continue;
		}
		else if (OnTheGame(whosTurn) == 1){
			printf("사용자가 승리하였습니다!\n");
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
		printf("블랙잭 게임에 오신 것을 환영합니다.\n");
		printf("게임을 진행하시려면 0, 끝내시려면 1을 눌러주십시오. : ");
		scanf("%d", &choice);

		if (choice == 0 || choice == 1)
			break;
		else
			printf("다시 입력해주십시오.\n");
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
	//딜러가 받는 카드
	int dillCardShape[10] = { 0 };//1 == ,스페이드, 2 == 클로버, 3 == 하트, 4 == 다이아
	int dillCardNum[10] = { 0 };

	static int dillCardIndex = 0;

	//사용자가 받는 카드
	int cardShape[10] = { 0 };
	int cardNum[10] = { 0 };

	static int userCardIndex = 0;

	int sumOfCardNum = 0;

	int whosWins = 0;// 0은 딜러 우승, 1은 사용자 우승
	
	//딜러가 먼저 시작
	if (turn % 2 == 0){

		//RandomNumGenerater에 4를 넣어 4가지의 임의의 수로 카드의 문양을 결정
		dillCardShape[dillCardIndex] = RandomNumGenerater(4);
		//RandomNumGenerater에 13을 넣어 13가지의 임의의 수로 카드의 수를 결정
		dillCardNum[dillCardIndex] = RandomNumGenerater(4);

		if (dillCardShape == 0 || dillCardNum == 0)
			printf("시스템 오류가 발생했습니다.\n");

		//갖고 있는 카드의 수를 모두 더함
		if (dillCardIndex >= 1){
			for (int i = 0; i < dillCardIndex; i++){
				sumOfCardNum += dillCardNum[i];
			}
		}

		dillCardIndex++;
	}
	else{
		//RandomNumGenerater에 4를 넣어 4가지의 임의의 수로 카드의 문양을 결정
		cardShape[userCardIndex] = RandomNumGenerater(4);
		//RandomNumGenerater에 13을 넣어 13가지의 임의의 수로 카드의 수를 결정
		cardNum[userCardIndex] = RandomNumGenerater(4);


		if (cardShape == 0 || cardNum == 0)
			printf("시스템 오류가 발생했습니다.\n");

		//갖고 있는 카드의 수를 모두 더함
		if (userCardIndex >= 1){
			for (int i = 0; i < userCardIndex; i++){
				sumOfCardNum += cardNum[i];
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

		return whosWins;
}