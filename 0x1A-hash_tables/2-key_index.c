#include "hash_tables.h"

/**
 * key_index - returns the index of a key
 * @key: the key to return index of
 * @size: size of the hash_table
 *
 * Return: the index at which the key/value pair should be stored
 * in the array of the hash table
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	unsigned long int hash = hash_djb2(key);

	return (hash % size);
}
