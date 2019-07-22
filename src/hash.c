#include "../includes/hash.h"

t_hash *new_hash(int count) {
	t_hash *table;

	if (!(table = (t_hash*)calloc(1, sizeof(t_hash))))
		return (NULL);
	
	if (!(table->lock = new_lock()))
		return (NULL);

	table->size = count + 1;

	if (!(table->hash_table = (void**)calloc(count, sizeof(void*)))) {
		free(&table->lock);
		free(table);
		return (NULL);
	} else {
		for (unsigned int i = 0; i < table->size; i++) {
			if (!(table->hash_table[i] = (void*)calloc(1, sizeof(t_value)))) {
				free(&table->hash_table);
				free(&table->lock);
				free(table);
				return (NULL);
			}
		}
	}

	return (table);
}

void *get(t_hash table, unsigned int key) {
	/*
	because the return type here is a void *
	all calling functions should typecast to
	assign a reliable/known value
	*/
	// printf("get key = %d table size = %d\n", key, table.size);
	if (key >= table.size) return (NULL);

	void *value;
	value = NULL;

	if (!pthread_mutex_trylock(&table.lock->lock)) {
		value = table.hash_table[key];
		// printf("value %d\n", *((int*)value));
		pthread_mutex_unlock(&table.lock->lock);
	}

	return (value);
}

bool set(t_hash table, unsigned int key, void *data) {
	if (key >= table.size) return (false);
	
	if (!pthread_mutex_trylock(&table.lock->lock)) {
		table.hash_table[key] = data;
		pthread_mutex_unlock(&table.lock->lock);
		return (true);
	}
	
	return (false);
}