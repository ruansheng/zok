zok-server:zok.o z_epoll.o net.o
	@gcc -o zok-server zok.o z_epoll.o net.o
	@echo doing compile zok-server

net.o:net.c
	@gcc -o net.o -c net.c
	@echo doing compile net.o

z_epoll.o:z_epoll.c
	@gcc -o z_epoll.o -c z_epoll.c
	@echo doing compile z_epoll.o

zok.o:zok.c
	@gcc -o zok.o -c zok.c
	@echo doing compile zok.o

install:
	@echo copy files to target dir !

clean:
	@rm -rf zok-server zok.o net.o
	@echo doing clean files
	@echo clean finished !