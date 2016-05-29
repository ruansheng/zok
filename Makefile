all:zok-server zok-cli
	.PHONY all
zok-server:zok.o z_epoll.o net.o
	@gcc -o zok-server zok.o z_epoll.o net.o
	@echo doing compile zok-server

zok-cli:zok-cli.o
	@gcc -o zok-cli zok-cli.o
	@echo doing compile zok-cli

net.o:net.c
	@gcc -o net.o -c net.c
	@echo doing compile net.o

z_epoll.o:z_epoll.c
	@gcc -o z_epoll.o -c z_epoll.c
	@echo doing compile z_epoll.o

zok.o:zok.c
	@gcc -o zok.o -c zok.c
	@echo doing compile zok.o

zok-cli.o:zok-cli.c
	@gcc -o zok-cli.o -c zok-cli.c
	@echo doing compile zok-cli.o

install:
	@echo copy files to target dir !

clean:
	@rm -rf zok-server zok-cli zok.o net.o zok-cli.o z_epoll.o
	@echo doing clean files
	@echo clean finished !