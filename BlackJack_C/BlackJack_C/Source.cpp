#include<stdio.h>

/*
대략적인 틀입니다. 수정하고 싶으시거나 추가하고 싶으시면 자유롭게 써주시되, 주석으로 이러이러항 아이디어입니다
라고 써주셨으면 합니다.
*/

int Intro();
int RandomNumGenerater(int value);


void main()
{
	while (1)//무한 루프
	{
		//만약 Intro()가 반환하는 값이 1이면 무한루프에서 나가기
		//0인 경우 게임 진행

		//딜러가 먼저 시작

		//RandomNumGenerater에 4를 넣어 4가지의 임의의 수로 카드의 문양을 결정
		//RandomNumGenerater에 13을 넣어 13가지의 임의의 수로 카드의 수를 결정

		//카드 수 합이 21을 넘는 쪽이 패배
		//카드 수 합이 16 이상이면 카드를 더 받을지 말지를 결정.		
		//카드 수 합이 21이 된 쪽이 무조건 승리. 둘 다 21이면 무승부
		//둘 다 20 이하이면 카드 수 합이 더 큰 쪽이 승리.

		//게임이 끝난 뒤, 다시 할 지 안 할지를 결정

		/*
		딜러의 인공지능을 이 cpp파일 안에서 만들 것인지 다른 cpp파일을 만들고 거기에서 구현하고 여기로 가져다 쓸 것인지 의견 내주십시오.
		*/
	}



	return;
}

int Intro()
{
	int choice;

	printf("게임을 진행하시려면 0, 끝내시려면 1을 눌러주십시오. : ");
	scanf("%d", &choice);

	return choice;
}

int RandomNumGenerater(int value)
{
	int random = 0;

	return random;
}