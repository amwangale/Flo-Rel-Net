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
#include <pigpio.h>

#include "../sx1278-LoRa-RaspberryPi/incl/LoRa.h"

#ifndef MHZ
	#define MHZ 900
#endif

#ifndef BITDEX // BIT INDEX
	#define BITDEX(i) i / BIT_WIDTH
#endif

#endif