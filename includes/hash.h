#ifndef HASH_H
#define HASH_H

#include "florel.h"
#include "utils.h"

typedef struct s_value {
	/*
	can't have a
	negative key
	*/
	unsigned int key;
	void *value;
} t_value;

typedef struct s_hash {
	void **table;
	unsigned int size;

	t_lock *lock;
} t_hash;

void 	*get(t_hash table, unsigned int key);
bool 	set(t_hash table, unsigned int key, void *data);
void 	new_hash(t_hash *hash, unsigned int count);

#endif