CC = gcc
DEBUG = -g

all: playlist

linked_list_playlist.o: linked_list_playlist.c linked_list_playlist.h
	$(CC) $(DEBUG) -c linked_list_playlist.c

main.o: main.c linked_list_playlist.h
	$(CC) $(DEBUG) -c main.c

playlist: main.o linked_list_playlist.o
	$(CC) $(DEBUG) main.o linked_list_playlist.o -o playlist

clean:
	rm -f *.o *.exe