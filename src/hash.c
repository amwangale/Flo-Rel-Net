#include "../includes/hash.h"

t_hash *new_hash(int count) {
	t_hash *table;

	if (!(table = (t_hash*)calloc(count, sizeof(t_value))))
		return (NULL);
	return (table);
}

void *get(t_hash table, unsigned int key) {
	if (key >= table.size) return (NULL);
	
	void *value;
	value = NULL;

	if (pthread_mutex_trylock(&table.lock.lock)) {
		value = table.hash_table[key];
		pthread_mutex_unlock(&table.lock.lock);
	}
	return (value);
}

bool set(t_hash table, unsigned int key, void *data) {
	if (key >= table.size) return (false);
	
	if (pthread_mutex_trylock(&table.lock.lock)) {
		table.hash_table[key] = data;
		pthread_mutex_unlock(&table.lock.lock);
		return (true);
	}
	
	return (false);
}