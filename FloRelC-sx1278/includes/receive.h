#ifndef RECEIVE_H
#define RECEIVE_H

#include "utils.h"
#include "node.h"

void 		*receiving(void *arg);
void 		rx_callback(rxData *data);
t_header 	*strip_header(char **data);
t_message 	*strip_message(char **data);

#endif