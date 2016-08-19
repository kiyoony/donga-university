#include <stdio.h>
char Text[61];
int tLength = 0;
char stack[61];
int top = 0;
int n;
int length(char *x)
{
	int index = 0;
	while (x[index] != '\0')index++;

	return index;
}
int f(int index) // 0 none 1 slimp  2 slump  3 c  4 h  5 f  6 g 7 b
{
	if (index == tLength - 1) {
		if (Text[index] == 'G')return 6;
		else return 0;
	}
	int rt = f(index + 1);
	if (Text[index] == 'F') {
		if (rt == 2 || rt == 5 || rt == 6)
			return 5;
	}
	else if (Text[index] == 'G') {
		if (rt == 3 || rt == -1)
			return 6;
	}
	else if (Text[index] == 'A') {
		if (rt == 2 || rt == 4 || rt == 7)
			return 1;
	}
	else if (Text[index] == 'B') {
		if (rt == 1)
			return 7;
	}
	else if (Text[index] == 'H') {
		if (rt == 2 || rt == 3)
			return 4;
	}
	else if (Text[index] == 'C') {
		if (rt == 3 || rt == 2)
			return 3;
	}
	else if (Text[index] == 'D' || Text[index] == 'E') {
		if (rt == 5)
			return 2;
	}
	return 0;
}
int main()
{
	FILE *inp = fopen("p00384.inp", "r");
	FILE *out = fopen("p00384.out", "w");
	int testcase;
	int iCount = 0;
	
	fscanf(inp, "%d", &testcase);
	fprintf(out, "SLURPYS OUTPUT\n");
	for (iCount = 0; iCount < testcase; iCount++)
	{
		fscanf(inp, "%s", Text);
		tLength = length(Text);
		fprintf(out, "%s\n", f(0) == 1 ? "YES":"NO");
	}
	fprintf(out, "END OF OUTPUT\n");
	return 0;
}