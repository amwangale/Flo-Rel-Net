#ifndef HASH_H
#define HASH_H

typedef struct s_value {
	/*
	can't have a
	negative key
	*/
	unsigned int key;
	void *value;
} t_value;

typedef struct s_hash {
	void **hash_table;
	unsigned int size;
} t_hash;

t_hash *new_hash(int count) {
	t_hash *table;

	if (!(table = (t_hash*)calloc(count, sizeof(t_value))))
		return (NULL);
	return (table);
}

void *get(t_hash table, unsigned int key) {
	if (key >= table.size) return (NULL);
	
	return (table.hash_table[key]);
}

bool set(t_hash table, unsigned int key, void *data) {
	if (key >= table.size) return (false);
	
	table.hash_table[key] = data;
	return (true);
}

#endif