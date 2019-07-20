#ifndef SEND_H
#define SEND_H

#include "florel.h"
#include "node.h"

void *sending(void *arg);
bool transmit_result(t_node *node, t_result *result);

#endif