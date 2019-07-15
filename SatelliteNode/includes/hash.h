#ifndef HASH_H
#define HASH_H

typedef struct s_value {
	int key;
	void *value;
} t_value;

typedef struct s_hash {
	void *hash_table;
} t_hash;

t_hash *new_hash(int count) {
	t_hash table;

	if (!(table = (t_hash*)memalloc(count, sizeof(t_value))))
		return (NULL);
	return (table);
}

void *get(t_hash table, int key) {
	if (index < table.size)
		return (table[key]);
	return (NULL);
}

#endif