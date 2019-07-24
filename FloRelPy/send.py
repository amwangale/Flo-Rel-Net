transmit_result(result):
	if result:
		result.header['flags']['transmission'] = 1
		
		simulate_transmission(result)
		sleep(1)

		return True
	return False