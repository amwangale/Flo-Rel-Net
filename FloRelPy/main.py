if __name__ == "__main__":
	node = Node()

	if len(sys.argv) == 2:
		if configure(node):
			if node.go_online():
				return 0