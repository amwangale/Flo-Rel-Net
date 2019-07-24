#ifndef RECEIVE_H
#define RECEIVE_H

#include "utils.h"
#include "node.h"

void 		*receiving(void *arg);
t_message *strip_message(t_result *result);
t_header *strip_header(t_result *result);

#endif