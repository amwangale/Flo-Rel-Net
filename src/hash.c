#include "../includes/hash.h"

void free_hash(t_hash *table) {
	if (table) {
		for (unsigned int i = 0; i < table->size; i++) {
			if (table->table[i]) {
				free(table->table[i]);
			}
		}
		free(table);
	}
}

bool new_hash(t_hash **hash, unsigned int count) {
	if (((*hash)->lock = new_lock())) {
		(*hash)->size = count + 1;

		if (!((*hash)->table = (void**)calloc((*hash)->size, sizeof(void*)))) {
			free(&(*hash)->lock);
			free((*hash));
			return (false);
		} else {
			for (unsigned int i = 0; i < (*hash)->size; i++) {
				if (!((*hash)->table[i] = (void*)calloc(1, sizeof(t_value)))) {
					free(&(*hash)->table); // free all?
					free(&(*hash)->lock);
					free((*hash));
					return (false);
				}
			}
		}
	}

	return (true);
}

void *get(t_hash *hash, unsigned int key) {
	/*
	because the return type here is a void *
	all calling functions should typecast to
	assign a reliable/known value
	*/
	if (key > hash->size) return (NULL);

	void *value;
	value = NULL;

	if (!pthread_mutex_trylock(&hash->lock->lock)) {
		value = hash->table[key];
		pthread_mutex_unlock(&hash->lock->lock);
	}

	return (value);
}

bool set(t_hash **hash, unsigned int key, void **data, size_t size) {
	if (key > (*hash)->size) return (false);
	
	if (!pthread_mutex_trylock(&(*hash)->lock->lock)) {
		
		if (!memcpy(&(*hash)->table[key], data, size)) {
			pthread_mutex_unlock(&(*hash)->lock->lock);
			return (false);
		}
		pthread_mutex_unlock(&(*hash)->lock->lock);
		return (true);
	}
	
	return (false);
}