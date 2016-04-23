zok-server:zok.o net.o
	@gcc -o zok-server zok.o net.o
	@echo doing compile zok-server

net.o:net.c
	@gcc -o net.o -c net.c
	@echo doing compile net.o

zok.o:zok.c
	@gcc -o zok.o -c zok.c
	@echo doing compile zok.o

install:
	@echo copy files to target dir !

clean:
	@rm -rf zok-server zok.o net.o
	@echo doing clean files
	@echo clean finished !