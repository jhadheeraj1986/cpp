# makefile for REST project

#CC=g++
#CFLAG=-c -Wall
#lib=-lboost_system -lcrypto -lssl -lcpprest

#all: RestServer

#RestServer: Server.o handler.o
#	$(CC) Server.o handler.o -o RestServer $(lib)

#Server.o: Server.cpp handler.h handler.o
#	$(CC) $(CFLAGS) Server.cpp $(lib)

#handler.o: handler.cpp handler.h stdafx.h
#	$(CC) $(CFLAG) handler.cpp $(lib)
	
g++ -std=c++11 Server.cpp handler.cpp  -o RestServer -lboost_system -lcrypto -lssl -lcpprest
	
