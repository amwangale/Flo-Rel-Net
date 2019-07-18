#ifndef FLOREL_H
#define FLOREL_H

#include <math.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "../sx1278-LoRa-RaspberryPi/LoRa.h"

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