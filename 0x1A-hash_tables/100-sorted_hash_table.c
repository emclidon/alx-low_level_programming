#include "hash_tables.h"

/**
 * shash_table_create - creates a sorted hash table
 * @size: size of the table to be created
 *
 * Return: pointer to the hash table
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *new;
	unsigned long int i;

	new = malloc(sizeof(shash_table_t));
	if (!new)
		return (NULL);

	new->size = size;
	new->array = malloc(sizeof(shash_node_t) * size);
	if (!new->array)
		return (NULL);

	for (i = 0; i < size; i++)
		new->array[i] = NULL;

	new->shead = NULL;
	new->stail = NULL;

	return (new);
}

/**
 * shash_table_set - adds a new node to the hash table
 * @ht: the hash table
 * @key: the key
 * @value: the value
 *
 * Return:1 if successful and 0 if not
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *new, *head, *temp;
	unsigned long int index;

	if (!ht || !key || !value || strlen(key) == 0)
		return (0);

	index = key_index((const unsigned char *)key, ht->size);
	head = ht->array[index];

	new = malloc(sizeof(shash_node_t));
	if (!new)
		return (0);

	new->key = strdup(key);
	new->value = strdup(value);
	new->next = NULL;
	new->sprev = NULL;
	new->snext = NULL;

	sorted_insert(ht, new);
	if (!head)
	{
		ht->array[index] = new;
		return (1);
	}
	temp = head;
	while (temp)
	{
		if (strcmp(key, temp->key) == 0)
		{
			free_snode(new);
			free(temp->value);
			temp->value = strdup(value);
			return (1);
		}
	}
	return (handle_scollision(ht, index, new));
}

/**
 * compare_ascii - compare the ascii values of two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 1 if s1 > s2, 0 if s1 == s2 and -1 if s1 < s2
 */
int compare_ascii(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] || s2[i]; i++)
	{
		if (s1[i] > s2[i])
			return (1);
		else if (s1[i] < s2[i])
			return (-1);
	}

	if (s1[i])
		return (1);
	else if (s2[i])
		return (-1);

	return (0);
}

/**
 * sorted_insert - insert or update a node in a sorted linked list
 * @ht: hash table
 * @node: node to be inserted
 *
 * Return: 1 if successful and 0 otherwise
 */
int sorted_insert(shash_table_t *ht, shash_node_t *node)
{
	shash_node_t *shead, *temp, *prev;

	shead = ht->shead, temp = shead;
	if (!shead)
	{
		ht->shead = node;
		ht->stail = node;
		return (1);
	}
	while (temp)
	{
		prev = temp;
		if (strcmp(temp->key, node->key) == 0)
		{
			free(temp->value);
			temp->value = strdup(node->value);
			return (1);
		}
		if (compare_ascii(temp->key, node->key) == 1)
			break;
		temp = temp->snext;
	}
	if (temp == shead)
	{
		shead->sprev = node;
		node->snext = shead;
		ht->shead = node;
	}
	else if (temp)
	{
		temp->sprev->snext = node;
		node->sprev = temp->sprev;
		temp->sprev = node, node->snext = temp;
	}
	else
	{
		prev->snext = node, node->sprev = prev;
		ht->stail = node;
	}
	return (1);
}

/**
 * handle-scollision - handles collision in the sorted hash table
 * @ht: the hash table
 * @index: the index where collision occured
 * @node: the node to add
 *
 * Return: 1 if successful and 0 if failed
 */
int handle_scollision(shash_table_t *ht, unsigned long int index,
			shash_node_t *node)
{
	shash_node_t *head;

	head = ht->array[index];
	node->next = head;
	ht->array[index] = node;

	return (1);
}

/**
 * shash_table_get - gets the value associated with a key from a
 * sorted hash table
 * @ht: the hash table
 * @key: the key
 *
 * Return: the value associated with the key
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *temp;

	if (!ht || !key || strlen(key) == 0)
		return (NULL);

	temp = ht->shead;
	while (temp)
	{
		if (strcmp(key, temp->key) == 0)
			return (temp->value);

		temp =  temp->snext;
	}

	return (NULL);
}

/**
 * shash_table_print - prints a sorted linked list
 * @ht: the hash table
 *
 * Return: void
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *temp;

	if (!ht)
		return;

	temp = ht->shead;
	printf("{");

	while (temp)
	{
		printf("'%s': '%s'", temp->key, temp->value);
		if (temp->snext)
			printf(", ");

		temp = temp->snext;
	}

	printf("}\n");
}

/**
 * shash_table_print_rev - prints a sorted linked list in reverse
 * @ht: the hash table
 *
 * Return: void
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *temp;

	if (!ht)
		return;

	temp = ht->stail;
	printf("{");

	while (temp)
	{
		printf("'%s': '%s'", temp->key, temp->value);
		if (temp->sprev)
			printf(", ");

		temp = temp->sprev;
	}

	printf("}\n");
}

/**
 * shash_table_delete - deletes a sorted hash table
 * @ht: the hash table
 *
 * Return: void
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *temp, *prev;

	if (!ht)
		return;

	temp = ht->shead;
	while (temp)
	{
		prev = temp;
		temp = temp->snext;
		free_snode(prev);
	}

	free(ht->array);
	free(ht);
}

/**
 * free_snode - frees a shash_node node
 * @node: the node to free
 *
 * Return: void
 */
void free_snode(shash_node_t *node)
{
	free(node->value);
	free(node->key);
	free(node);
}
