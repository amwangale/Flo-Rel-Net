import time
import simulate

def transmit_result(result):
	if result:
		result.header['flags']['transmission'] = 1
		
		simulate.transmission(result)
		time.sleep(1)

		return True
	return False