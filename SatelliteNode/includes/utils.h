

typedef struct s_status {
	enum {
		bool running;
		bool success,
		bool failure
	} status;
} t_status;

typedef struct s_float21 {
	float sign: 1;
	float value: 20;
} float21;

float21 float_to_float21(float num) {
	if (num > pow(2, 10)) return (null);

	int i;
	float21 f;
	double value;
	double fraction;
	double integral;

	value = 0;
	f = new_float21();
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