/*
20810 ������
C�� Ȱ���� �ܿ����� ������� ����
*/

#include <stdio.h>
#include <windows.h>

void ResetBoard(int board[][32], int h, int w); // �����ʱ�ȭ
void PrintBoard(int board[][32], int h, int w); // ���� ���
int CountNeighbors(int board[][32], int row, int col); // ����ִ� �ֺ� ������ ����
void Generation(int board[][32], int h, int w); // ���� ����
void AddCells(int board[][32], int h, int w); // ������1 - ���� ���� �߰�
void LoadCells(int board[][32], int h, int w); // ������2 - �̸� ��ġ�� ����

int main(void)
{
	int const WIDTH = 30; // ��� ���� - ������ ����Ǵ� ������ ���� = 30
	int const HEIGHT = 30; // ��� ���� - ������ ����Ǵ� ������ ���� = 30

	int board[32][32]; // �迭 ���� - ������ �����ڸ��κ��� ������� �������̱� ������(0���� �� ��), ����+2, ����+2
	int choice;

	ResetBoard(board, HEIGHT, WIDTH); // ���� ��ü�� 0���� �ʱ�ȭ
	
	PrintBoard(board, HEIGHT, WIDTH); // ��(��� ������ �׾��ִ�) ���� ���

	/* ������ - ������ ���� �߰��ϰų� �̸� ��ġ�� ������ �ҷ����� */
	while(1)
	{
		printf("������ ���� �߰��ϱ� : 1\n�̸� ��ġ�� ���� �ҷ����� : 2\n");
		scanf("%d", &choice);
		system("cls");
		PrintBoard(board, HEIGHT, WIDTH);

		if(choice==1)// ������ ���� �߰��ϱ�
		{
			AddCells(board, HEIGHT, WIDTH);
			break;
		}
		else if(choice==2) // �̸� ��ġ�� ������ �ҷ�����
		{
			LoadCells(board, HEIGHT, WIDTH);
			break;
		}
		else
			printf("�ٽ� �Է��� �ּ���.\n");
    }
	system("cls");
	PrintBoard(board, HEIGHT, WIDTH); // ������ �߰��� ����� �����


	/* ���� ���� */
	while(1)
	{
		printf("�������� �����ϱ� : 1\n�����ϱ� : 2\n");
		scanf("%d", &choice);

		if(choice==1) // �������� ����
		{
			Generation(board, HEIGHT, WIDTH); // ���� ����� �迭�� ����
			system("cls");
			PrintBoard(board, HEIGHT, WIDTH); // ������ �迭�� ���� �����
		}
		else if(choice==2) // ����
			break;
		else
		{
			system("cls");
			PrintBoard(board, HEIGHT, WIDTH);
			printf("�ٽ� �Է��� �ּ���.\n");
		}
	}
	return 0;
}

void ResetBoard(int board[][32], int h, int w) // �迭 �� ���ڸ� ���� 0���� �����(������ ���� �������·� �����)
{
	int i, j;

	for(i=0; i<h+2; i++) // 32X32�� �迭 ��ü(���ӿ� ������ �ʴ�, ��µ��� �ʴ� �κ� ����)0���� �ʱ�ȭ
	{
		for(j=0; j<w+2; j++)
		{
			board[i][j]=0;
		}
	}
}

void PrintBoard(int board[][32], int h, int w) // ������ �����ڸ��� ������ �κ�(������ �Ͼ�� �κ�)�� ���
{
	int i, j;

	for(i=1; i<h+1; i++) // 32X32�� �迭 �� �����ڸ� �κ��� ������ 30X30��ŭ�� �κ��� ���
	{
		for(j=1; j<w+1; j++)
		{
			if(board[i][j]==1)
				printf("%2c", 64); // ������ ��������� @ ���

			else
				printf("%2c", 45); // ������ �׾������� - ���
		}
		printf("\n");
	}
}

int CountNeighbors(int board[][32], int row, int col) // ��� ���� �Է¹޾� �ش� ��ġ�� ����(���ؼ���) �ֺ� 8ĭ �� ����ִ� ������ �� �� ���� ������
{
	int neighbor=0; // ���ؼ��� �ֺ� 8ĭ�� ����ִ� ������ ������ ����(��ȯ)�� ����
	int i, j;

	for(i=-1; i<2; i++) // ���ؼ����� �߽����� 3X3��ŭ�� ���� �� ����ִ�(���� 1��) ������ ���� ���Ѵ�
	{
		for(j=-1; j<2; j++)
		{
			neighbor += board[row+i][col+j];
		}
	}
	neighbor -= board[row][col]; // ���ؼ���(�߽�)�� ���ԵǾ��ֱ� ������, ���ؼ����� ���ش�
	return neighbor;
}

void Generation(int board[][32], int h, int w) // ������ ���� ���ǿ� ���� ��������� ����
{
	int nextGen[32][32]={0}; // ���������� ������ ����� �迭
	int count;
	int i, j;

	for(i=1; i<h+1; i++) // �����ڸ��� ������ �κ��� 30X30��ŭ�� �κп��� ���븦 ����
	{
		for(j=1; j<w+1; j++)
		{
			count = CountNeighbors(board, i, j); // �ֺ� ������ ��μ� �����ִ� �Լ� ȣ�� - ����count�� ������

			if(board[i][j]==1 && count<2) // ������ ������� ��, ����ִ� �ֺ� ������ �ϳ� ���ϸ� ���� ���뿡 ����
				nextGen[i][j]=0;

			else if(board[i][j]==1 && count>3) // ������ ������� ��, ����ִ� �ֺ� ������ �� �̻��̸� ���� ���뿡 ���л�
				nextGen[i][j]=0;

			else if(board[i][j]==0 && count==3) // ������ �׾����� ��, ����ִ� �ֺ� ������ ���̸� ���� ���뿡 ��Ƴ�
				nextGen[i][j]=1;

			else
				nextGen[i][j]=board[i][j]; // �� �� �������� ���� ���뿡 �� ���¸� ����
		}
	}
	
	for(i=1; i<h+1; i++)
	{
		for(j=1; j<w+1; j++)
		{
			board[i][j]=nextGen[i][j]; // ���带 ���������� �迭�� ��ü
		}
	}
}

void AddCells(int board[][32], int h, int w) // ������1 - ������ ���� �߰�
{
	int choice;
	int cellRow, cellCol; // ������ �߰��� ��ǥ

	while(1)
	{
		printf("������ �߰��ϱ� : 1\n�̴�� �����ϱ� : 2\n");
		scanf("%d", &choice);
		
		if(choice==1) // ������ �߰�
		{
			printf("������ �߰��� ��ǥ�� �Է��ϼ���.(x,y�� ���·�, ���ϴܺ��� 1,1�Դϴ�.) : ");
			scanf("%d, %d", &cellCol, &cellRow); // ������ ������ǥ�� ������ǥ�� ������� �Է¹���

			if(0<cellRow && cellRow<h+2 && 0<cellCol && cellCol<w+2) // 30X30 ������ ��ǥ���� Ȯ��
			{
				board[h+1-cellRow][cellCol]=1; // �ش� ��ǥ�� ������ �츲(���ϴ��� �������� ����)
				system("cls");
				PrintBoard(board, h, w); // ���� �����
			}
			else
			{
				system("cls");
				PrintBoard(board, h, w);
				printf("30X30 ������ �̳��� ��ǥ�� �Է����ּ���.\n");
			}
		}
		else if(choice==2) // �����߰� ��
			break;
		else
		{
			system("cls");
			PrintBoard(board, h, w);
			printf("�ٽ� �Է��� �ּ���\n");
		}
	}
}

void LoadCells(int board[][32], int h, int w) // ������2 - �̸� ������ ���·� ������ ��ġ
{
	int loadChoice;

	printf("��ȣ�� : 1\n");
	printf("���ּ� - �۶��̴� : 2\n");
	printf("���ּ� - �淮 ���ּ�(LWSS) : 3\n");
	printf("������ - �޼� : 4\n");
	printf("��� - R-����̳� : 5\n");
	printf("��� - ���丮 : 6\n");
	scanf("%d", &loadChoice);

	switch(loadChoice)
	{
	case 1: //��ȣ��
		board[14][15]=1;
		board[15][14]=1;
		board[15][15]=1;
		board[15][16]=1;
		board[16][15]=1;
		break;
	case 2: //�۶��̴�
		board[2][2]=1;
		board[3][3]=1;
		board[3][4]=1;
		board[4][2]=1;
		board[4][3]=1;
		break;
	case 3: //�淮 ���ּ�
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
	case 4: //�޼�
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
	case 5: //R-����̳�
		board[14][15]=1;
		board[14][16]=1;
		board[15][14]=1;
		board[15][15]=1;
		board[16][15]=1;
		break;
	case 6: //���丮
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
		printf("�ٽ� �Է��� �ּ���\n");
		LoadCells(board, h, w);
	}
}