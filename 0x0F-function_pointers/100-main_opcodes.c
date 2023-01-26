#include <stdlib.h>
#include <stdio.h>

/**
 * main - prints opcodes of its main function
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
	char *code = (char *)main;
	int i, bytes;

	if (argc != 2)
	{
		printf("Error\n");
		exit(1);
	}

	bytes = atoi(argv[1]);

	if (bytes < 0)
	{
		printf("Error\n");
		exit(2);
	}

	for (i = 0; i < bytes; i++)
	{
		printf("%02x", code[i] & 0xFF);
		if (i != bytes - 1)
			printf(" ");
	}

	printf("\n");

	return (0);
}
