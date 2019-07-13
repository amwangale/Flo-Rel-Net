
typedef struct s_flags {
	float transmission: 1;
	float panic: 1;
	float failure: 1;
	float disconnect: 1;
	float programmable: 1;
} t_flags;

typedef struct s_header {
	t_flags flags;
	float id: 10;
} t_header;