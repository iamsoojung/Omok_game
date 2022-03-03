#include <stdio.h>		// 표준 입출력 함수 사용을 위한 헤더파일 추가
#include <Windows.h>	// 콘솔창을 이용하기 위한 헤더파일 추가
#include <conio.h>		// 콘솔 입출력 함수 사용을 위한 헤더파일 추가

#define MINT_TEXT textcolor(11, 0);		// 글자색 = 민트 & 글자배경색 = 검정
#define WHITE_TEXT textcolor(15, 0);	// 글자색 = 하양 & 글자배경색 = 검정
#define YELLOW_TEXT textcolor(14, 0);	// 글자색 = 노랑 & 글자배경색 = 검정
#define BLACK_STONE 1	// 1 = 흑돌
#define WHITE_STONE 2	// 2 = 백돌
#define BLACK_PRINT printf("○");	// 흑돌 출력
#define WHITE_PRINT printf("●");	// 백돌 출력

int i, j;
int board[19][19] = { 0 };	// 19X19 오목판 배열

void title();	// 시작화면 출력함수
void rule();	// 게임방법화면 출력함수
void load();	// 게임 시작 전 카운트다운하는 함수
void after_game();	// 게임 끝난 후 다음에 동작할 선택지화면 출력함수
void exit_game();	// 게임종료화면 출력함수

void gotoxy(int x, int y);	// 커서 위치 조정 함수
void textcolor(int foreground, int background);	// 글자색, 글자배경색 변경 함수

void a();	// 오목판 1행
void b();	// 오목판 2행 ~ 18행
void c();	// 오목판 19행
void omok_board();	// 오목판 그리는 함수

void stone_move(int stone);	// 돌을 움직이는 함수
void press_key(int input, int* x, int* y);	// 키보드 입력받는 함수

int win_check_black();	// 흑돌의 승리 판정함수
int win_check_white();	// 백돌의 승리 판정함수

void gotoxy(int x, int y)
{
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void textcolor(int foreground, int background)
{
	int color = foreground + background * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 메인함수 시작 ---------------------------------------------------------------------------
int main()
{
	// 커서 숨김처리
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	while (1)
	{
	start:	// 레이블 start (시작화면)
		title();
		char ch = _getch();	// 변수 ch에 입력받은 키보드값 저장
		if (ch == 49)	// 1 -> 게임 시작
		{
		game:	// 레이블 game (게임실행)
			load();

			// 오목판 초기화
			for (i = 0; i < 19; i++)
			{
				for (j = 0; j < 19; j++)
				{
					board[i][j] = NULL;
				}
			}
			system("cls");	// 화면 지우기 함수

			while (1)
			{
				omok_board();
				stone_move(BLACK_STONE);	// 흑돌 시작
				if (win_check_black() == 0)	// 흑돌이 승리인 경우
				{
					after_game();
					while (1)
					{
						ch = _getch();	// 변수 ch에 입력받은 키보드값 저장

						if (ch == 49)	// 1
						{
							goto game;	// 레이블 game(게임화면)으로 이동
						}
						else if (ch == 27)	// ESC
						{
							exit_game();
							return 0;	// 프로그램이 정상적으로 종료
						}
						else if (ch == 48)		// 0
						{
							system("cls");	// 화면 지우는 함수
							goto start;		// 레이블 start(시작화면)로 이동
						}
					}
				}

				omok_board();
				stone_move(WHITE_STONE);	// 백돌 시작
				if (win_check_white() == 0)	// 백돌이 승리인 경우 (흑돌의 경우와 동일)
				{
					after_game();
					while (1)
					{
						ch = _getch();

						if (ch == 49)
						{
							goto game;
						}
						else if (ch == 27)
						{
							exit_game();
							return 0;
						}
						else if (ch == 48)
						{
							system("cls");
							goto start;
						}
					}
				}
			}
		}
		else if (ch == 50)	// 2 -> 게임 설명
		{
			rule();
			while (1)
			{
				ch = _getch();	// 변수 ch에 입력받은 키보드값 저장
				if (ch == 48)	// 0
				{
					system("cls");	// 화면 지우는 함수
					goto start;		// 레이블 start(시작화면)로 이동
				}
			}
		}
		else if (ch == 27)	//esc
		{
			exit_game();
			return 0;	// 프로그램이 정상적으로 종료
		}
	}
}

void title()
{
	// Sleep(100); 
	// : 0.1초씩 시간차를 두고 출력
	gotoxy(5, 2); printf("┌━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┐");
	Sleep(100);
	MINT_TEXT;
	gotoxy(5, 4); printf("      ■■■         ■■■■                                   ■    ");
	Sleep(100);
	gotoxy(5, 5); printf("     ■    ■        ■    ■     ■■■■   ■ ■     ■■■   ■    ");
	Sleep(100);
	gotoxy(5, 6); printf("      ■■■         ■■■■          ■    ■ ■    ■    ■  ■    ");
	Sleep(100);
	gotoxy(5, 7); printf("        ■              ■            ■   ■■ ■     ■■■   ■    ");
	Sleep(100);
	gotoxy(5, 8); printf("        ■              ■           ■      ■ ■                    ");
	Sleep(100);
	gotoxy(5, 9); printf("        ■        ■■■■■■■    ■       ■ ■      ■■■■■    ");
	Sleep(100);
	gotoxy(5, 10); printf("   ■■■■■■                    ■        ■ ■      ■      ■    ");
	Sleep(100);
	gotoxy(5, 11); printf("                    ■■■■■               ■ ■      ■■■■■    ");
	Sleep(100);
	gotoxy(5, 12); printf("                            ■                                        ");
	Sleep(100);
	gotoxy(5, 13); printf("                            ■                                        ");
	Sleep(100);
	WHITE_TEXT;
	gotoxy(5, 15); printf("└━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┘"); Sleep(100);
	gotoxy(30, 18); printf("게임 시작 >>  1");
	gotoxy(30, 20); printf("게임 설명 >>  2");
	gotoxy(30, 22); printf("게임 종료 >> ESC");
}

void rule()
{
	system("cls");
	gotoxy(5, 3); printf("┌━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┐");
	MINT_TEXT;
	gotoxy(5, 5); printf("                 ☆★☆★☆★ 게임방법 ★☆★☆★☆");
	gotoxy(5, 7); printf("                 방향키를 이용하여 바둑돌을 움직이고");
	gotoxy(5, 8); printf("                먼저 5개의 바둑돌을 연달아 이으면 승리!");
	gotoxy(5, 9); printf("                        흑(黑)이 선(先)입니다");
	gotoxy(5, 11); printf("                    ←↑↓→ 방향키 : 바둑돌 이동");
	gotoxy(5, 12); printf("                 space bar : 바둑돌 놓기 (더블 클릭)");
	gotoxy(5, 14); printf("                   시작화면으로 돌아가려면 >>> 0");
	WHITE_TEXT;
	gotoxy(5, 16); printf("└━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┘");
}

void load()
{
	system("cls");
	gotoxy(30, 8);
	printf("┌━━━━━━━━━━━━━━━━━━━━━━━┐");
	gotoxy(30, 14);
	printf("└━━━━━━━━━━━━━━━━━━━━━━━┘");
	Sleep(100);
	gotoxy(30, 10);
	printf("\t 게임을 시작합니다!!");
	gotoxy(42, 12);
	printf("3");	Sleep(1000);	// 3초 카운트다운 시작
	gotoxy(42, 12);
	printf("2");	Sleep(1000);
	gotoxy(42, 12);
	printf("1");	Sleep(1000);
}

void after_game()
{
	puts("\n  ┏━━━  ※ 한판 더 하시겠습니까?  ━━━┓\n");
	puts("            한판 더!! >>> 1          ");
	puts("          안하고 종료할래요 >>> ESC    ");
	puts("\n       시작화면으로 돌아가려면 >>> 0     \n");
	printf("   ┗━━━━━━━━━━━━━━━━");
	puts("━━━━━━━━━━━━━━━━━┛\n");
}

void exit_game()
{
	system("cls");
	printf("\n\n      ━━━━━━━━━━━━━━━━━━━━━━━━");
	puts("━━━━━━━━━━━━━━━━━━━━━━━━");
	MINT_TEXT;
	puts("\n\n              ♥♡♥♡♥♡ 종 료 ♡♥♡♥♡♥\n\n");
	WHITE_TEXT;
	printf("      ━━━━━━━━━━━━━━━━━━━━━━━━");
	puts("━━━━━━━━━━━━━━━━━━━━━━━━\n\n\n");
}


void a()
{
	// 1열
	if (board[0][0] == 0)	printf("┌ ");		// 오목판 배열의 원소가 0 이면 -> 오목판 모양 출력
	else if (board[0][0] == BLACK_STONE)	BLACK_PRINT		// 오목판 배열의 원소가 흑돌 이면 -> 흑돌 출력
	else if (board[0][0] == WHITE_STONE)	WHITE_PRINT		// 오목판 배열의 원소가 백돌 이면 -> 백돌 출력

	// 2열 ~ 18열
		for (i = 1; i < 18; i++)
		{
			if (board[0][i] == 0)	printf("┬ ");
			else if (board[0][i] == BLACK_STONE)	BLACK_PRINT
			else if (board[0][i] == WHITE_STONE)	WHITE_PRINT
		}

	// 19열
	if (board[0][18] == 0)	printf("┐ ");
	else if (board[0][18] == BLACK_STONE)	BLACK_PRINT
	else if (board[0][18] == WHITE_STONE)	WHITE_PRINT

		printf("\n");
}

void b()
{
	for (i = 1; i < 18; i++)
	{
		// 1열
		if (board[i][0] == 0)	printf("├ ");
		else if (board[i][0] == BLACK_STONE)	BLACK_PRINT
		else if (board[i][0] == WHITE_STONE)	WHITE_PRINT

			// 2열 ~ 18열
			for (j = 1; j < 18; j++)
			{
				if (board[i][j] == 0)	printf("┼ ");
				else if (board[i][j] == BLACK_STONE)	BLACK_PRINT
				else if (board[i][j] == WHITE_STONE)	WHITE_PRINT
			}

		// 19열
		if (board[i][18] == 0)	printf("┤ ");
		else if (board[i][18] == BLACK_STONE)		BLACK_PRINT
		else if (board[i][18] == WHITE_STONE)		WHITE_PRINT

			printf("\n");
	}
}

void c()
{
	// 1열
	if (board[18][0] == 0)	printf("└ ");
	else if (board[18][0] == BLACK_STONE)	BLACK_PRINT
	else if (board[18][0] == WHITE_STONE)	WHITE_PRINT

		// 2열 ~ 18열
		for (i = 1; i < 18; i++)
		{
			if (board[18][i] == 0)	printf("┴ ");
			else if (board[18][i] == BLACK_STONE)	BLACK_PRINT
			else if (board[18][i] == WHITE_STONE)	WHITE_PRINT
		}

	// 19열
	if (board[18][18] == 0)	printf("┘ ");
	else if (board[18][18] == BLACK_STONE)	BLACK_PRINT
	else if (board[18][18] == WHITE_STONE)	WHITE_PRINT

		printf("\n");
}

void omok_board()
{
	a();	// 1행
	b();	// 2행 ~ 18행
	c();	// 19행
}

int win_check_black()
{
	for (i = 0; i < 18; i++)
	{
		for (j = 0; j < 18; j++)
		{
			// 가로 5연속 (→)
			if (board[i][j] == BLACK_STONE && board[i][j + 1] == BLACK_STONE && board[i][j + 2] == BLACK_STONE && board[i][j + 3] == BLACK_STONE && board[i][j + 4] == BLACK_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      BLACK 승 !!!");
				WHITE_TEXT;
				return 0;
			}

			// 세로 5연속 (↓)
			if (board[i][j] == BLACK_STONE && board[i + 1][j] == BLACK_STONE && board[i + 2][j] == BLACK_STONE && board[i + 3][j] == BLACK_STONE && board[i + 4][j] == BLACK_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      BLACK 승 !!!");
				WHITE_TEXT;
				return 0;
			}

			// 아래 대각선 5연속 (↘)
			if (board[i][j] == BLACK_STONE && board[i + 1][j + 1] == BLACK_STONE && board[i + 2][j + 2] == BLACK_STONE && board[i + 3][j + 3] == BLACK_STONE && board[i + 4][j + 4] == BLACK_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      BLACK 승 !!!");
				WHITE_TEXT;
				return 0;
			}

			// 위 대각선 5연속 (↗)
			if (i >= 4)
			{
				if (board[i][j] == BLACK_STONE && board[i - 1][j + 1] == BLACK_STONE && board[i - 2][j + 2] == BLACK_STONE && board[i - 3][j + 3] == BLACK_STONE && board[i - 4][j + 4] == BLACK_STONE)
				{
					omok_board();
					YELLOW_TEXT;
					puts("\n\t      BLACK 승 !!!");
					WHITE_TEXT;
					return 0;
				}
			}
		}
	}
}

int win_check_white()
{
	for (i = 0; i < 18; i++)
	{
		for (j = 0; j < 18; j++)
		{
			// 가로 5연속 (→)
			if (board[i][j] == WHITE_STONE && board[i][j + 1] == WHITE_STONE && board[i][j + 2] == WHITE_STONE && board[i][j + 3] == WHITE_STONE && board[i][j + 4] == WHITE_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      WHITE 승 !!!");
				WHITE_TEXT;
				return 0;
			}

			// 세로 5연속 (↓)
			if (board[i][j] == WHITE_STONE && board[i + 1][j] == WHITE_STONE && board[i + 2][j] == WHITE_STONE && board[i + 3][j] == WHITE_STONE && board[i + 4][j] == WHITE_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      WHITE 승 !!!");
				WHITE_TEXT;
				return 0;
			}

			// 아래 대각선 5연속 (↘)
			if (board[i][j] == WHITE_STONE && board[i + 1][j + 1] == WHITE_STONE && board[i + 2][j + 2] == WHITE_STONE && board[i + 3][j + 3] == WHITE_STONE && board[i + 4][j + 4] == WHITE_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      WHITE 승 !!!");
				WHITE_TEXT;
				return 0;
			}

			// 위 대각선 5연속 (↗)
			if (i >= 4)
			{
				if (board[i][j] == WHITE_STONE && board[i - 1][j + 1] == WHITE_STONE && board[i - 2][j + 2] == WHITE_STONE && board[i - 3][j + 3] == WHITE_STONE && board[i - 4][j + 4] == WHITE_STONE)
				{
					omok_board();
					YELLOW_TEXT;
					puts("\n\t      WHITE 승 !!!");
					WHITE_TEXT;
					return 0;
				}
			}
		}
	}
}

void stone_move(int stone)
{
	static int x = 19;		// 바둑알 위치좌표를 위한 정적변수 x, y
	static int y = 10;
	int input;
	gotoxy(x, y);
	while (1)
	{
	retry:		// 레이블 retry(게임 재시작)
		input = _getch();
		if (_kbhit())	//키보드 입력이 있으면
		{
			gotoxy(x, y);
			system("cls");
			omok_board();
			input = _getch();
			press_key(input, &x, &y);
			gotoxy(x, y);
			if (stone == BLACK_STONE)	BLACK_PRINT
			else WHITE_PRINT
		}
		else if (_getch() == 32)	// 입력이 spacebar인 경우
		{
			if (board[y - 1][x / 2] == BLACK_STONE || board[y - 1][x / 2] == WHITE_STONE)	// 선택한 좌표가 이미 돌이 존재하는 좌표인 경우
			{
				system("cls");
				omok_board();
				puts("\n\t※ 이미 선택된 칸입니다. ※");
				puts("\n\t  ※ 다시 선택해주세요 ※");
				goto retry;		// 레이블 retry(게임 재시작)로 이동
			}

			// 그 외 경우 돌 출력
			else
			{
				if (stone == BLACK_STONE)	board[y - 1][x / 2] = BLACK_STONE;
				else board[y - 1][x / 2] = WHITE_STONE;
				system("cls");
				break;
			}
		}
	}
}

void press_key(int input, int* x, int* y)	// input = 키보드 입력, x좌표와 y좌표는 포인터로 받음
{
	if (input == 72)	// 키보드 입력 = 상
	{
		(*y)--;			// y좌표 위쪽 이동
		if (*y < 1)	*y = 1;		// 더 이상 이동할 칸이 없는 경우 -> 제자리
		return y;		// y좌표 반환
	}
	else if (input == 80)	// 키보드 입력 = 하
	{
		(*y)++;			// y좌표 아래쪽 이동
		if (*y > 19)	*y = 19;
		return y;
	}
	else if (input == 75)	// 키보드 입력 = 좌
	{
		*x -= 2;		// x좌표 왼쪽 이동
		if (*x < 1)	*x = 1;
		return x;		// x좌표 반환
	}
	else if (input == 77)	// 키보드 입력 = 우
	{
		*x += 2;		// x좌표 오른쪽 이동
		if (*x > 37)	*x = 37;
		return x;		// x좌표 반환
	}
}