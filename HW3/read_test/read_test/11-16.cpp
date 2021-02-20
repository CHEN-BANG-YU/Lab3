#include "stdio.h"

void main()
{
	char s[255];
	while ((fgets(s, 255, stdin)) != NULL);
	{
		printf("%s", s);
	}

}