typedef struct s_node {
	short id: NODE_ID_SIZE;
	t_status status;
	t_hash device_hash;
	t_hash results_hash;
	t_hash receive_hash;
	t_sender sender;
} t_node;

t_node new_node(char **argv) {
	//
}