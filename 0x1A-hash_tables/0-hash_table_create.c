#include "hash_tables.h"

/**
 * hash_table_create - creates a hash table of any size
 * @size: size of hash table to be created
 *
 * Return: pointer to hash table or NULL if creation not successful
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *new_table;
	unsigned long int i;

	if (size == 0)
		return  (NULL);

	new_table = malloc(sizeof(hash_table_t));
	if (!new_table)
		return (NULL);

	new_table->size = size;
	new_table->array = malloc(sizeof(char *) * size);
	if (!new_table->array)
		return (NULL);

	for (i = 0; i < size; i++)
		new_table->array[i] = NULL;

	return (new_table);
}
