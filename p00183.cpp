#include <stdio.h>
int arr[201][201];
int m, n;
char DivideText[40001];
char inputText[51];
int pLine;
int index;
FILE *inp = fopen("p00183.inp", "r");
FILE *out = fopen("p00183.out", "w");
void printText(char Text)
{
	if (pLine == 50)
	{
		pLine = 0;
		fprintf(out, "\n");
	}
	fprintf(out, "%c", Text);
	pLine++;
}
void processB(int sX, int sY, int eX, int eY)
{
	int i, j, cnt = 0;
	if (sX == eX)eX++;
	if (sY == eY)eY++;
	int Xsize = eX - sX;
	int Ysize = eY - sY;
	for (i = sX; i < eX; i++)
	{
		for (j = sY; j < eY; j++)
		{
			if (arr[i][j])cnt++;
		}
	}
	if (((eX - sX) * (eY - sY)) == cnt)
	{
		printText('1');
		return;
	}
	else if (!cnt)
	{
		printText('0');
		return;
	}
	else
	{
		printText('D');
		if (Xsize != 1 && Xsize % 2 != 0)Xsize++;
		if (Ysize != 1 && Ysize % 2 != 0)Ysize++;
		processB(sX, sY, sX + (Xsize / 2), sY + (Ysize / 2)); // 1사분면
		if (Ysize != 1)
		{
			processB(sX, sY + (Ysize / 2), sX + (Xsize / 2), eY);    // 2사분면
		}
		if (Xsize != 1)
		{
			processB(sX + (Xsize / 2), sY, eX, sY + (Ysize / 2));	   // 3사분면
		}
		if (Xsize != 1 && Ysize != 1)
		{
			processB(sX + (Xsize / 2), sY + (Ysize / 2), eX, eY);		   // 4사분면
		}
	}
}
void processD(int sX, int sY, int eX, int eY)
{
	int i, j;
	if (sX == eX)eX++;
	if (sY == eY)eY++;
	int Xsize = eX - sX;
	int Ysize = eY - sY;
	if (DivideText[index] != 'D')
	{
		for (i = sX; i < eX; i++)
		{
			for (j = sY; j < eY; j++)
			{
				arr[i][j] = DivideText[index] - '0';
			}
		}
		index++;
		return;
	}
	index++;
	//Divide
	if (Xsize != 1 && Xsize % 2 != 0)Xsize++;
	if (Ysize != 1 && Ysize % 2 != 0)Ysize++;
	processD(sX, sY, sX + (Xsize / 2), sY + (Ysize / 2)); // 1사분면
	if (Ysize != 1)
	{
		processD(sX, sY + (Ysize / 2), sX + (Xsize / 2), eY);    // 2사분면
	}
	if (Xsize != 1)
	{
		processD(sX + (Xsize / 2), sY, eX, sY + (Ysize / 2));	   // 3사분면
	}
	if (Xsize != 1 && Ysize != 1)
	{
		processD(sX + (Xsize / 2), sY + (Ysize / 2), eX, eY);		   // 4사분면
	}
}
int main()
{
	char temp;
	int i, j, Line = 0;
	while (1)
	{
		if (inputText[0] == '\0')fscanf(inp, "%s", inputText);
		if (inputText[0] == '#')return 0;
		pLine = 0, Line = 0, index = 0; //출력 라인 , 입력 라인
		fscanf(inp, "%d", &m);
		fscanf(inp, "%d", &n);
		fprintf(out, "%c%4d%4d\n", inputText[0] == 'D' ? 'B' : 'D', m, n);
		if (inputText[0] == 'B')
		{
			for (i = 0; i < m; i++)
			{
				for (j = 0; j < n; j++)
				{
					if (((i*n) + j) % 50 == 0)
					{
						fscanf(inp, "%c", &temp); // 줄바꿈
					}
					fscanf(inp, "%c", &temp);
					arr[i][j] = temp - '0';
				}
			}
			processB(0, 0, m, n);
			inputText[0] = '\0';
		}
		else  // temp == 'D'
		{
			while (1)
			{
				fscanf(inp, "%s", inputText);
				if (inputText[1] == '\0')
				{
					if (inputText[0] != '#')
					{
						fscanf(inp, "%c", &temp);
						if (temp == '\n')
						{
							DivideText[50 * Line] = inputText[0];
							inputText[0] = '\0';
						}
					}
					break;
				}
				for (i = 0; inputText[i] != '\0'; i++)
				{
					DivideText[i + (50 * Line)] = inputText[i];
				}
				DivideText[i + (50 * Line)] = '\0';
				Line++;
			}
			processD(0, 0, m, n);
			for (i = 0; i < m; i++)
			{
				for (j = 0; j< n; j++)
				{
					printText(arr[i][j] ? '1' : '0');
				}
			}

		}
		fprintf(out, "\n");
	}

	return 0;
}