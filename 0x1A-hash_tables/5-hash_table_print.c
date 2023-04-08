#include "hash_tables.h"

/**
 * hash_table_print - prints a hash table
 * @ht: the hash table
 *
 * Return void
 */
void hash_table_print(const hash_table_t *ht)
{
	unsigned long int i, len;
	hash_node_t *head;
	char *res = NULL;

	if (!ht)
		return;

	res = realloc_res(res, "{");

	for (i = 0; i < ht->size; i++)
	{
		head = ht->array[i];
		if (!head)
			continue;

		while (head)
		{
			res = realloc_res(res, "'");
			res = realloc_res(res, head->key);
			res = realloc_res(res, "': '");
			res = realloc_res(res, head->value);
			res = realloc_res(res, "', ");

			head = head->next;
		}
	}

	len = strlen(res);

	if (len > 1)
	{
		res[len - 2] = '\0';
		res[len - 1] = '\0';
	}

	res = realloc_res(res, "}");
	printf("%s\n", res);

	free(res);
}


/**
 * realloc_res - allocates a new space for res and concatenates the new string
 * to res
 * @res: previous string
 * @str: string to concat
 *
 * Return: a pointer to res or NULL
 */
char *realloc_res(char *res, char *str)
{
	char *new;
	unsigned int i, j;

	if (!res)
	{
		res = strdup(str);
		return (res);
	}

	new = strdup(res);
	free(res);
	res = malloc((strlen(new) + strlen(str) + 1) * sizeof(char));
	if (!res)
		return (NULL);

	for (i = 0; i < strlen(new); i++)
		res[i] = new[i];

	for (j = 0; j < strlen(str); j++, i++)
		res[i] = str[j];

	res[i] = '\0';

	free(new);

	return (res);
}
