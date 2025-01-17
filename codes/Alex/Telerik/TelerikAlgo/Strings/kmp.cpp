#include <stdio.h>
#include <string.h>

void computeLPSArray (const char *pat, int M, int *lps);

void KMPSearch (const char *pat, const char *txt)
{
	int M = strlen (pat);
	int N = strlen (txt);

	int *lps = new int [M];
	int j = 0;

	computeLPSArray (pat, M, lps);

	int i = 0;
	while (i < N)
	{
		if (pat [j] == txt [i])
		{
			j ++;
			i ++;
		}

		if (j == M)
		{
			printf ("Found pattern at index %d \n", i - j);
			j = lps [j - 1];
		}
		else if (i < N && pat[j] != txt[i])
		{
			if (j != 0)
				j = lps [j - 1];
			else
				i = i + 1;
		}
	}
	delete[] lps;
}

void computeLPSArray (const char *pat, int M, int *lps)
{
	int len = 0;
	int i;

	lps [0] = 0;
	i = 1;

	while (i < M)
	{
		if (pat [i] == pat [len])
		{
			len ++;
			lps [i] = len;
			i ++;
		}
		else
		{
			if (len != 0)
				len = lps [len - 1];
			else 
			{
				lps [i] = 0;
				i ++;
			}
		}
	}
}

int main ()
{

}
