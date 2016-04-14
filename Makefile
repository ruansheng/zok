zok-server:zok.o
	@gcc -o zok-server zok.o
	@echo doing compile zok-server

zok.o:zok.c
	@gcc -o zok.o -c zok.c
	@echo doing compile zok.o

install:
	@echo copy files to target dir !

clean:
	@rm -rf zok-server zok.o
	@echo doing clean files
	@echo clean finished !