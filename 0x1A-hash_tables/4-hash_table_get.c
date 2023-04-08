#include "hash_tables.h"

/**
 * hash_table_get - retrieves the value associated with a key
 * @ht: the hash table
 * @key: the key
 *
 * Return: value associated with key or NULL if key not found
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	unsigned long int index;
	hash_node_t *head, *temp;

	if (!ht || !key || strlen(key) == 0)
		return (NULL);

	index = key_index((const unsigned char *)key, ht->size);

	head = ht->array[index];
	if (!head)
		return (NULL);

	if (strcmp(head->key, key) == 0)
		return (head->value);

	if (!head->next)
		return (NULL);

	temp = head;
	while (temp)
	{
		if (strcmp(temp->key, key) == 0)
			return (temp->value);

		temp = temp->next;
	}
	return (NULL);
}
