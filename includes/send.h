#ifndef SEND_H
#define SEND_H

#include "queue.h"
#include "threads.h"

#ifndef MHZ
	#define MHZ 900
#endif

#ifndef HEADER_SIZE
	#define HEADER_SIZE BIT_WIDTH
#endif

#ifndef MESSAGE_SIZE
	#define MESSAGE_SIZE MHZ - HEADER_SIZE
#endif

#ifndef PACKET_SIZE
	#define PACKET_SIZE HEADER_SIZE + MESSAGE_SIZE
#endif

#ifndef BITDEX // BIT INDEX
	#define BITDEX(i) i / BIT_WIDTH
#endif

#endif