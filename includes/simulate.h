#ifndef SIMULATE_H
#define SIMULATE_H

bool simulate_transmission(t_result result);
t_result *simulate_random_result(t_node node);
t_result simulate_receive(t_node node);

#endif