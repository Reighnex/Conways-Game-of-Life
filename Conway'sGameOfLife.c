/*
20810 박태훈
C언어를 활용한 콘웨이의 생명게임 구현
*/

#include <stdio.h>
#include <windows.h>

void ResetBoard(int board[][32], int h, int w); // 보드초기화
void PrintBoard(int board[][32], int h, int w); // 보드 출력
int CountNeighbors(int board[][32], int row, int col); // 살아있는 주변 세포수 세기
void Generation(int board[][32], int h, int w); // 세대 진행
void AddCells(int board[][32], int h, int w); // 선택지1 - 직접 세포 추가
void LoadCells(int board[][32], int h, int w); // 선택지2 - 미리 배치된 세포

int main(void)
{
	int const WIDTH = 30; // 상수 선언 - 게임이 진행되는 보드의 가로 = 30
	int const HEIGHT = 30; // 상수 선언 - 게임이 진행되는 보드의 세로 = 30

	int board[32][32]; // 배열 선언 - 보드의 가장자리부분은 사용하지 않을것이기 때문에(0으로 둘 것), 세로+2, 가로+2
	int choice;

	ResetBoard(board, HEIGHT, WIDTH); // 보드 전체를 0으로 초기화
	
	PrintBoard(board, HEIGHT, WIDTH); // 빈(모든 세포가 죽어있는) 보드 출력

	/* 선택지 - 세포를 직접 추가하거나 미리 배치된 세포를 불러오기 */
	while(1)
	{
		printf("세포를 직접 추가하기 : 1\n미리 배치된 세포 불러오기 : 2\n");
		scanf("%d", &choice);
		system("cls");
		PrintBoard(board, HEIGHT, WIDTH);

		if(choice==1)// 세포를 직접 추가하기
		{
			AddCells(board, HEIGHT, WIDTH);
			break;
		}
		else if(choice==2) // 미리 배치된 세포를 불러오기
		{
			LoadCells(board, HEIGHT, WIDTH);
			break;
		}
		else
			printf("다시 입력해 주세요.\n");
    }
	system("cls");
	PrintBoard(board, HEIGHT, WIDTH); // 세포가 추가된 보드로 재출력


	/* 세대 관찰 */
	while(1)
	{
		printf("다음세대 관찰하기 : 1\n종료하기 : 2\n");
		scanf("%d", &choice);

		if(choice==1) // 다음세대 관찰
		{
			Generation(board, HEIGHT, WIDTH); // 다음 세대로 배열을 전개
			system("cls");
			PrintBoard(board, HEIGHT, WIDTH); // 전개된 배열로 보드 재출력
		}
		else if(choice==2) // 종료
			break;
		else
		{
			system("cls");
			PrintBoard(board, HEIGHT, WIDTH);
			printf("다시 입력해 주세요.\n");
		}
	}
	return 0;
}

void ResetBoard(int board[][32], int h, int w) // 배열 속 인자를 전부 0으로 만들기(세포를 전부 죽은상태로 만들기)
{
	int i, j;

	for(i=0; i<h+2; i++) // 32X32의 배열 전체(게임에 사용되지 않는, 출력되지 않는 부분 전부)0으로 초기화
	{
		for(j=0; j<w+2; j++)
		{
			board[i][j]=0;
		}
	}
}

void PrintBoard(int board[][32], int h, int w) // 보드의 가장자리를 제외한 부분(게임이 일어나는 부분)만 출력
{
	int i, j;

	for(i=1; i<h+1; i++) // 32X32의 배열 중 가장자리 부분을 제외한 30X30만큼의 부분을 출력
	{
		for(j=1; j<w+1; j++)
		{
			if(board[i][j]==1)
				printf("%2c", 64); // 세포가 살아있으면 @ 출력

			else
				printf("%2c", 45); // 세포가 죽어있으면 - 출력
		}
		printf("\n");
	}
}

int CountNeighbors(int board[][32], int row, int col) // 행과 열을 입력받아 해당 위치의 세포(기준세포) 주변 8칸 에 살아있는 세포가 몇 개 인지 세어줌
{
	int neighbor=0; // 기준세포 주변 8칸의 살아있는 세포의 갯수가 저장(반환)될 예정
	int i, j;

	for(i=-1; i<2; i++) // 기준세포를 중심으로 3X3만큼의 세포 중 살아있는(값이 1인) 세포의 합을 구한다
	{
		for(j=-1; j<2; j++)
		{
			neighbor += board[row+i][col+j];
		}
	}
	neighbor -= board[row][col]; // 기준세포(중심)가 포함되어있기 때문에, 기준세포를 빼준다
	return neighbor;
}

void Generation(int board[][32], int h, int w) // 세포의 생존 조건에 맞춰 다음세대로 전개
{
	int nextGen[32][32]={0}; // 다음세대의 세포가 저장될 배열
	int count;
	int i, j;

	for(i=1; i<h+1; i++) // 가장자리를 제외한 부분인 30X30만큼의 부분에서 세대를 전개
	{
		for(j=1; j<w+1; j++)
		{
			count = CountNeighbors(board, i, j); // 주변 세포가 몇개인세 세어주는 함수 호출 - 변수count에 저장함

			if(board[i][j]==1 && count<2) // 세포가 살아있을 때, 살아있는 주변 세포가 하나 이하면 다음 세대에 고독사
				nextGen[i][j]=0;

			else if(board[i][j]==1 && count>3) // 세포가 살아있을 때, 살아있는 주변 세포가 넷 이상이면 다음 세대에 과밀사
				nextGen[i][j]=0;

			else if(board[i][j]==0 && count==3) // 세포가 죽어있을 때, 살아있는 주변 세포가 셋이면 다음 세대에 살아남
				nextGen[i][j]=1;

			else
				nextGen[i][j]=board[i][j]; // 그 외 세포들은 다음 세대에 그 상태를 유지
		}
	}
	
	for(i=1; i<h+1; i++)
	{
		for(j=1; j<w+1; j++)
		{
			board[i][j]=nextGen[i][j]; // 보드를 다음세대의 배열로 교체
		}
	}
}

void AddCells(int board[][32], int h, int w) // 선택지1 - 세포를 직접 추가
{
	int choice;
	int cellRow, cellCol; // 세포를 추가할 좌표

	while(1)
	{
		printf("세포를 추가하기 : 1\n이대로 시작하기 : 2\n");
		scanf("%d", &choice);
		
		if(choice==1) // 세포를 추가
		{
			printf("세포를 추가할 좌표를 입력하세요.(x,y의 형태로, 좌하단부터 1,1입니다.) : ");
			scanf("%d, %d", &cellCol, &cellRow); // 세포의 가로좌표와 세로좌표를 순서대로 입력받음

			if(0<cellRow && cellRow<h+2 && 0<cellCol && cellCol<w+2) // 30X30 내부의 좌표인지 확인
			{
				board[h+1-cellRow][cellCol]=1; // 해당 좌표의 세포를 살림(좌하단을 원점으로 삼음)
				system("cls");
				PrintBoard(board, h, w); // 보드 재출력
			}
			else
			{
				system("cls");
				PrintBoard(board, h, w);
				printf("30X30 격자판 이내의 좌표를 입력해주세요.\n");
			}
		}
		else if(choice==2) // 세포추가 끝
			break;
		else
		{
			system("cls");
			PrintBoard(board, h, w);
			printf("다시 입력해 주세요\n");
		}
	}
}

void LoadCells(int board[][32], int h, int w) // 선택지2 - 미리 정해진 형태로 세포를 배치
{
	int loadChoice;

	printf("신호등 : 1\n");
	printf("우주선 - 글라이더 : 2\n");
	printf("우주선 - 경량 우주선(LWSS) : 3\n");
	printf("진동자 - 펄서 : 4\n");
	printf("장수 - R-펜토미노 : 5\n");
	printf("장수 - 도토리 : 6\n");
	scanf("%d", &loadChoice);

	switch(loadChoice)
	{
	case 1: //신호등
		board[14][15]=1;
		board[15][14]=1;
		board[15][15]=1;
		board[15][16]=1;
		board[16][15]=1;
		break;
	case 2: //글라이더
		board[2][2]=1;
		board[3][3]=1;
		board[3][4]=1;
		board[4][2]=1;
		board[4][3]=1;
		break;
	case 3: //경량 우주선
		board[13][3]=1;
		board[13][4]=1;
		board[13][5]=1;
		board[13][6]=1;
		board[14][2]=1;
		board[14][6]=1;
		board[15][6]=1;
		board[16][2]=1;
		board[16][5]=1;
		break;
	case 4: //펄서
		board[9][11]=1;
		board[9][12]=1;
		board[9][13]=1;
		board[9][17]=1;
		board[9][18]=1;
		board[9][19]=1;
		board[11][9]=1;
		board[11][14]=1;
		board[11][16]=1;
		board[11][21]=1;
		board[12][9]=1;
		board[12][14]=1;
		board[12][16]=1;
		board[12][21]=1;
		board[13][9]=1;
		board[13][14]=1;
		board[13][16]=1;
		board[13][21]=1;
		board[14][11]=1;
		board[14][12]=1;
		board[14][13]=1;
		board[14][17]=1;
		board[14][18]=1;
		board[14][19]=1;
		board[16][11]=1;
		board[16][12]=1;
		board[16][13]=1;
		board[16][17]=1;
		board[16][18]=1;
		board[16][19]=1;
		board[17][9]=1;
		board[17][14]=1;
		board[17][16]=1;
		board[17][21]=1;
		board[18][9]=1;
		board[18][14]=1;
		board[18][16]=1;
		board[18][21]=1;
		board[19][9]=1;
		board[19][14]=1;
		board[19][16]=1;
		board[19][21]=1;
		board[21][11]=1;
		board[21][12]=1;
		board[21][13]=1;
		board[21][17]=1;
		board[21][18]=1;
		board[21][19]=1;
		break;
	case 5: //R-펜토미노
		board[14][15]=1;
		board[14][16]=1;
		board[15][14]=1;
		board[15][15]=1;
		board[16][15]=1;
		break;
	case 6: //도토리
		board[14][13]=1;
		board[15][15]=1;
		board[16][12]=1;
		board[16][13]=1;
		board[16][16]=1;
		board[16][17]=1;
		board[16][18]=1;
		break;
	default:
		system("cls");
		PrintBoard(board, h, w);
		printf("다시 입력해 주세요\n");
		LoadCells(board, h, w);
	}
}