#ifndef SEND_H
	#define SEND_H
#endif

#ifndef NODE_ID_SIZE
	#define NODE_ID_SIZE 10
#endif

#ifndef PACKET_SIZE
	#define PACKET_SIZE 60
#endif

typedef struct s_flags {
	float transmission: 1;
	float panic: 1;
	float failure: 1;
	float disconnect: 1;
	float programmable: 1;
} t_flags;

typedef struct s_queue {

} t_queue;

typedef struct s_hash {

} t_hash;

typedef struct s_sender {

} t_sender;

typedef struct s_item {

} t_item;

typedef struct s_result {
	float buffer[PACKET_SIZE];
} t_result;

typedef struct s_node {
	short id: NODE_ID_SIZE;
	enum {
		bool running;
		bool success,
		bool failure
	} status;
	t_sender sender;
} t_node;

typedef struct s_float15 {
	float sign: 1;
	float value: 20;
} float15;

t_node new_node(char **argv) {
	//
}

float15 float_to_float15(float num) {
	if (num > pow(2, 10)) return (null);

	int i;
	float15 f;
	double value;
	double fraction;
	double integral;

	value = 0;
	f = new_float15();
	fraction = modf(num, &integral);
	f.sign = (num >> 32) & 0x1;
	f.value |= integral;
	f.value <<= 10; // half-size

	i = -1;
	while (num > 0x3FF) {
		num /= 10;
	}

	f.value |= num;

	return (f);
}