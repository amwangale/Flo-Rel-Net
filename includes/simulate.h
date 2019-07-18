#ifndef SIMULATE_H
#define SIMULATE_H

#include "node.h"

float 		simulate_collect_data(void);
t_result 	*simulate_random_result(t_node node);
t_result 	simulate_receive(t_node node);
bool 		simulate_transmission(t_result *result);

#endif