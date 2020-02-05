server:
	 gcc -Wall server.c -o server
	 gcc -Wall client.c -o client
clean:
	@rm -rf server client
