
PREFIX = /opt/clang+llvm-3.5.2-x86_64-linux-gnu/bin

#NDK

CC = gcc 
AR = ar 

#FLAGS = -Wall 
FLAGS = 

#src-y = src/vcos-logic.c
src-y = $(wildcard src/commandprocess/*.c) $(wildcard src/multichannel/*.c) $(wildcard src/files/*.c)
#${info ${src-y}}

obj-y = $(patsubst %.c, %.o, ${src-y})
#${info ${obj-y}}

all: build

build: libvcos.a

%.o:%.c
#	echo $^
	${CC} ${FLAGS} -o $@  -c $< 

libvcos.a: ${obj-y}
#	echo $^
	${AR} -rcv $@ $^
	cp libvcos.a ../../testvcos/
	
clean:
	@find . -name "*.o" -exec rm {} \;
	@find . -name "*.a" -exec rm {} \;
