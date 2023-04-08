#include "hash_tables.h"

/**
 * hash_table_delete - deletes a hash table
 * @ht: the hash table
 *
 * Return: void
 */
void hash_table_delete(hash_table_t *ht)
{
	unsigned long int i;
	hash_node_t *head;

	for (i = 0; i < ht->size; i++)
	{
		head = ht->array[i];
		if (!head)
			continue;

		free_list(head);
	}

	free(ht->array);
	free(ht);
}

/**
 * free_list - fress a hash_node_t list
 * @head: head of the list
 *
 * Return: void
 */
void free_list(hash_node_t *head)
{
	hash_node_t *temp = head, *prev;

	while (temp)
	{
		prev = temp;
		temp = temp->next;

		free_node(prev);
	}
}

/**
 * free_node - frees a node of a hash_node_t list
 * @node: the node to be freed
 *
 * Return: void
 */
void free_node(hash_node_t *node)
{
	free(node->key);
	free(node->value);
	free(node);
}
