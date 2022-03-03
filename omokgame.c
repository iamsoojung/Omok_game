#include <stdio.h>		// ǥ�� ����� �Լ� ����� ���� ������� �߰�
#include <Windows.h>	// �ܼ�â�� �̿��ϱ� ���� ������� �߰�
#include <conio.h>		// �ܼ� ����� �Լ� ����� ���� ������� �߰�

#define MINT_TEXT textcolor(11, 0);		// ���ڻ� = ��Ʈ & ���ڹ��� = ����
#define WHITE_TEXT textcolor(15, 0);	// ���ڻ� = �Ͼ� & ���ڹ��� = ����
#define YELLOW_TEXT textcolor(14, 0);	// ���ڻ� = ��� & ���ڹ��� = ����
#define BLACK_STONE 1	// 1 = �浹
#define WHITE_STONE 2	// 2 = �鵹
#define BLACK_PRINT printf("��");	// �浹 ���
#define WHITE_PRINT printf("��");	// �鵹 ���

int i, j;
int board[19][19] = { 0 };	// 19X19 ������ �迭

void title();	// ����ȭ�� ����Լ�
void rule();	// ���ӹ��ȭ�� ����Լ�
void load();	// ���� ���� �� ī��Ʈ�ٿ��ϴ� �Լ�
void after_game();	// ���� ���� �� ������ ������ ������ȭ�� ����Լ�
void exit_game();	// ��������ȭ�� ����Լ�

void gotoxy(int x, int y);	// Ŀ�� ��ġ ���� �Լ�
void textcolor(int foreground, int background);	// ���ڻ�, ���ڹ��� ���� �Լ�

void a();	// ������ 1��
void b();	// ������ 2�� ~ 18��
void c();	// ������ 19��
void omok_board();	// ������ �׸��� �Լ�

void stone_move(int stone);	// ���� �����̴� �Լ�
void press_key(int input, int* x, int* y);	// Ű���� �Է¹޴� �Լ�

int win_check_black();	// �浹�� �¸� �����Լ�
int win_check_white();	// �鵹�� �¸� �����Լ�

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

// �����Լ� ���� ---------------------------------------------------------------------------
int main()
{
	// Ŀ�� ����ó��
	CONSOLE_CURSOR_INFO cursorInfo = { 0 };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	while (1)
	{
	start:	// ���̺� start (����ȭ��)
		title();
		char ch = _getch();	// ���� ch�� �Է¹��� Ű���尪 ����
		if (ch == 49)	// 1 -> ���� ����
		{
		game:	// ���̺� game (���ӽ���)
			load();

			// ������ �ʱ�ȭ
			for (i = 0; i < 19; i++)
			{
				for (j = 0; j < 19; j++)
				{
					board[i][j] = NULL;
				}
			}
			system("cls");	// ȭ�� ����� �Լ�

			while (1)
			{
				omok_board();
				stone_move(BLACK_STONE);	// �浹 ����
				if (win_check_black() == 0)	// �浹�� �¸��� ���
				{
					after_game();
					while (1)
					{
						ch = _getch();	// ���� ch�� �Է¹��� Ű���尪 ����

						if (ch == 49)	// 1
						{
							goto game;	// ���̺� game(����ȭ��)���� �̵�
						}
						else if (ch == 27)	// ESC
						{
							exit_game();
							return 0;	// ���α׷��� ���������� ����
						}
						else if (ch == 48)		// 0
						{
							system("cls");	// ȭ�� ����� �Լ�
							goto start;		// ���̺� start(����ȭ��)�� �̵�
						}
					}
				}

				omok_board();
				stone_move(WHITE_STONE);	// �鵹 ����
				if (win_check_white() == 0)	// �鵹�� �¸��� ��� (�浹�� ���� ����)
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
		else if (ch == 50)	// 2 -> ���� ����
		{
			rule();
			while (1)
			{
				ch = _getch();	// ���� ch�� �Է¹��� Ű���尪 ����
				if (ch == 48)	// 0
				{
					system("cls");	// ȭ�� ����� �Լ�
					goto start;		// ���̺� start(����ȭ��)�� �̵�
				}
			}
		}
		else if (ch == 27)	//esc
		{
			exit_game();
			return 0;	// ���α׷��� ���������� ����
		}
	}
}

void title()
{
	// Sleep(100); 
	// : 0.1�ʾ� �ð����� �ΰ� ���
	gotoxy(5, 2); printf("������������������������������������������������������������������������������������������������������������������������������������������������");
	Sleep(100);
	MINT_TEXT;
	gotoxy(5, 4); printf("      ����         �����                                   ��    ");
	Sleep(100);
	gotoxy(5, 5); printf("     ��    ��        ��    ��     �����   �� ��     ����   ��    ");
	Sleep(100);
	gotoxy(5, 6); printf("      ����         �����          ��    �� ��    ��    ��  ��    ");
	Sleep(100);
	gotoxy(5, 7); printf("        ��              ��            ��   ��� ��     ����   ��    ");
	Sleep(100);
	gotoxy(5, 8); printf("        ��              ��           ��      �� ��                    ");
	Sleep(100);
	gotoxy(5, 9); printf("        ��        ��������    ��       �� ��      ������    ");
	Sleep(100);
	gotoxy(5, 10); printf("   �������                    ��        �� ��      ��      ��    ");
	Sleep(100);
	gotoxy(5, 11); printf("                    ������               �� ��      ������    ");
	Sleep(100);
	gotoxy(5, 12); printf("                            ��                                        ");
	Sleep(100);
	gotoxy(5, 13); printf("                            ��                                        ");
	Sleep(100);
	WHITE_TEXT;
	gotoxy(5, 15); printf("����������������������������������������������������������������������������������������������������������������������������������������������"); Sleep(100);
	gotoxy(30, 18); printf("���� ���� >>  1");
	gotoxy(30, 20); printf("���� ���� >>  2");
	gotoxy(30, 22); printf("���� ���� >> ESC");
}

void rule()
{
	system("cls");
	gotoxy(5, 3); printf("������������������������������������������������������������������������������������������������������������������������������������");
	MINT_TEXT;
	gotoxy(5, 5); printf("                 �١ڡ١ڡ١� ���ӹ�� �ڡ١ڡ١ڡ�");
	gotoxy(5, 7); printf("                 ����Ű�� �̿��Ͽ� �ٵϵ��� �����̰�");
	gotoxy(5, 8); printf("                ���� 5���� �ٵϵ��� ���޾� ������ �¸�!");
	gotoxy(5, 9); printf("                        ��(��)�� ��(�)�Դϴ�");
	gotoxy(5, 11); printf("                    ����� ����Ű : �ٵϵ� �̵�");
	gotoxy(5, 12); printf("                 space bar : �ٵϵ� ���� (���� Ŭ��)");
	gotoxy(5, 14); printf("                   ����ȭ������ ���ư����� >>> 0");
	WHITE_TEXT;
	gotoxy(5, 16); printf("������������������������������������������������������������������������������������������������������������������������������������");
}

void load()
{
	system("cls");
	gotoxy(30, 8);
	printf("��������������������������������������������������");
	gotoxy(30, 14);
	printf("��������������������������������������������������");
	Sleep(100);
	gotoxy(30, 10);
	printf("\t ������ �����մϴ�!!");
	gotoxy(42, 12);
	printf("3");	Sleep(1000);	// 3�� ī��Ʈ�ٿ� ����
	gotoxy(42, 12);
	printf("2");	Sleep(1000);
	gotoxy(42, 12);
	printf("1");	Sleep(1000);
}

void after_game()
{
	puts("\n  ��������  �� ���� �� �Ͻðڽ��ϱ�?  ��������\n");
	puts("            ���� ��!! >>> 1          ");
	puts("          ���ϰ� �����ҷ��� >>> ESC    ");
	puts("\n       ����ȭ������ ���ư����� >>> 0     \n");
	printf("   ����������������������������������");
	puts("������������������������������������\n");
}

void exit_game()
{
	system("cls");
	printf("\n\n      ������������������������������������������������");
	puts("������������������������������������������������");
	MINT_TEXT;
	puts("\n\n              ������������ �� �� ������������\n\n");
	WHITE_TEXT;
	printf("      ������������������������������������������������");
	puts("������������������������������������������������\n\n\n");
}


void a()
{
	// 1��
	if (board[0][0] == 0)	printf("�� ");		// ������ �迭�� ���Ұ� 0 �̸� -> ������ ��� ���
	else if (board[0][0] == BLACK_STONE)	BLACK_PRINT		// ������ �迭�� ���Ұ� �浹 �̸� -> �浹 ���
	else if (board[0][0] == WHITE_STONE)	WHITE_PRINT		// ������ �迭�� ���Ұ� �鵹 �̸� -> �鵹 ���

	// 2�� ~ 18��
		for (i = 1; i < 18; i++)
		{
			if (board[0][i] == 0)	printf("�� ");
			else if (board[0][i] == BLACK_STONE)	BLACK_PRINT
			else if (board[0][i] == WHITE_STONE)	WHITE_PRINT
		}

	// 19��
	if (board[0][18] == 0)	printf("�� ");
	else if (board[0][18] == BLACK_STONE)	BLACK_PRINT
	else if (board[0][18] == WHITE_STONE)	WHITE_PRINT

		printf("\n");
}

void b()
{
	for (i = 1; i < 18; i++)
	{
		// 1��
		if (board[i][0] == 0)	printf("�� ");
		else if (board[i][0] == BLACK_STONE)	BLACK_PRINT
		else if (board[i][0] == WHITE_STONE)	WHITE_PRINT

			// 2�� ~ 18��
			for (j = 1; j < 18; j++)
			{
				if (board[i][j] == 0)	printf("�� ");
				else if (board[i][j] == BLACK_STONE)	BLACK_PRINT
				else if (board[i][j] == WHITE_STONE)	WHITE_PRINT
			}

		// 19��
		if (board[i][18] == 0)	printf("�� ");
		else if (board[i][18] == BLACK_STONE)		BLACK_PRINT
		else if (board[i][18] == WHITE_STONE)		WHITE_PRINT

			printf("\n");
	}
}

void c()
{
	// 1��
	if (board[18][0] == 0)	printf("�� ");
	else if (board[18][0] == BLACK_STONE)	BLACK_PRINT
	else if (board[18][0] == WHITE_STONE)	WHITE_PRINT

		// 2�� ~ 18��
		for (i = 1; i < 18; i++)
		{
			if (board[18][i] == 0)	printf("�� ");
			else if (board[18][i] == BLACK_STONE)	BLACK_PRINT
			else if (board[18][i] == WHITE_STONE)	WHITE_PRINT
		}

	// 19��
	if (board[18][18] == 0)	printf("�� ");
	else if (board[18][18] == BLACK_STONE)	BLACK_PRINT
	else if (board[18][18] == WHITE_STONE)	WHITE_PRINT

		printf("\n");
}

void omok_board()
{
	a();	// 1��
	b();	// 2�� ~ 18��
	c();	// 19��
}

int win_check_black()
{
	for (i = 0; i < 18; i++)
	{
		for (j = 0; j < 18; j++)
		{
			// ���� 5���� (��)
			if (board[i][j] == BLACK_STONE && board[i][j + 1] == BLACK_STONE && board[i][j + 2] == BLACK_STONE && board[i][j + 3] == BLACK_STONE && board[i][j + 4] == BLACK_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      BLACK �� !!!");
				WHITE_TEXT;
				return 0;
			}

			// ���� 5���� (��)
			if (board[i][j] == BLACK_STONE && board[i + 1][j] == BLACK_STONE && board[i + 2][j] == BLACK_STONE && board[i + 3][j] == BLACK_STONE && board[i + 4][j] == BLACK_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      BLACK �� !!!");
				WHITE_TEXT;
				return 0;
			}

			// �Ʒ� �밢�� 5���� (��)
			if (board[i][j] == BLACK_STONE && board[i + 1][j + 1] == BLACK_STONE && board[i + 2][j + 2] == BLACK_STONE && board[i + 3][j + 3] == BLACK_STONE && board[i + 4][j + 4] == BLACK_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      BLACK �� !!!");
				WHITE_TEXT;
				return 0;
			}

			// �� �밢�� 5���� (��)
			if (i >= 4)
			{
				if (board[i][j] == BLACK_STONE && board[i - 1][j + 1] == BLACK_STONE && board[i - 2][j + 2] == BLACK_STONE && board[i - 3][j + 3] == BLACK_STONE && board[i - 4][j + 4] == BLACK_STONE)
				{
					omok_board();
					YELLOW_TEXT;
					puts("\n\t      BLACK �� !!!");
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
			// ���� 5���� (��)
			if (board[i][j] == WHITE_STONE && board[i][j + 1] == WHITE_STONE && board[i][j + 2] == WHITE_STONE && board[i][j + 3] == WHITE_STONE && board[i][j + 4] == WHITE_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      WHITE �� !!!");
				WHITE_TEXT;
				return 0;
			}

			// ���� 5���� (��)
			if (board[i][j] == WHITE_STONE && board[i + 1][j] == WHITE_STONE && board[i + 2][j] == WHITE_STONE && board[i + 3][j] == WHITE_STONE && board[i + 4][j] == WHITE_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      WHITE �� !!!");
				WHITE_TEXT;
				return 0;
			}

			// �Ʒ� �밢�� 5���� (��)
			if (board[i][j] == WHITE_STONE && board[i + 1][j + 1] == WHITE_STONE && board[i + 2][j + 2] == WHITE_STONE && board[i + 3][j + 3] == WHITE_STONE && board[i + 4][j + 4] == WHITE_STONE)
			{
				omok_board();
				YELLOW_TEXT;
				puts("\n\t      WHITE �� !!!");
				WHITE_TEXT;
				return 0;
			}

			// �� �밢�� 5���� (��)
			if (i >= 4)
			{
				if (board[i][j] == WHITE_STONE && board[i - 1][j + 1] == WHITE_STONE && board[i - 2][j + 2] == WHITE_STONE && board[i - 3][j + 3] == WHITE_STONE && board[i - 4][j + 4] == WHITE_STONE)
				{
					omok_board();
					YELLOW_TEXT;
					puts("\n\t      WHITE �� !!!");
					WHITE_TEXT;
					return 0;
				}
			}
		}
	}
}

void stone_move(int stone)
{
	static int x = 19;		// �ٵϾ� ��ġ��ǥ�� ���� �������� x, y
	static int y = 10;
	int input;
	gotoxy(x, y);
	while (1)
	{
	retry:		// ���̺� retry(���� �����)
		input = _getch();
		if (_kbhit())	//Ű���� �Է��� ������
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
		else if (_getch() == 32)	// �Է��� spacebar�� ���
		{
			if (board[y - 1][x / 2] == BLACK_STONE || board[y - 1][x / 2] == WHITE_STONE)	// ������ ��ǥ�� �̹� ���� �����ϴ� ��ǥ�� ���
			{
				system("cls");
				omok_board();
				puts("\n\t�� �̹� ���õ� ĭ�Դϴ�. ��");
				puts("\n\t  �� �ٽ� �������ּ��� ��");
				goto retry;		// ���̺� retry(���� �����)�� �̵�
			}

			// �� �� ��� �� ���
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

void press_key(int input, int* x, int* y)	// input = Ű���� �Է�, x��ǥ�� y��ǥ�� �����ͷ� ����
{
	if (input == 72)	// Ű���� �Է� = ��
	{
		(*y)--;			// y��ǥ ���� �̵�
		if (*y < 1)	*y = 1;		// �� �̻� �̵��� ĭ�� ���� ��� -> ���ڸ�
		return y;		// y��ǥ ��ȯ
	}
	else if (input == 80)	// Ű���� �Է� = ��
	{
		(*y)++;			// y��ǥ �Ʒ��� �̵�
		if (*y > 19)	*y = 19;
		return y;
	}
	else if (input == 75)	// Ű���� �Է� = ��
	{
		*x -= 2;		// x��ǥ ���� �̵�
		if (*x < 1)	*x = 1;
		return x;		// x��ǥ ��ȯ
	}
	else if (input == 77)	// Ű���� �Է� = ��
	{
		*x += 2;		// x��ǥ ������ �̵�
		if (*x > 37)	*x = 37;
		return x;		// x��ǥ ��ȯ
	}
}