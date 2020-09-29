/*Linked List Algorithms

Linked List functionality that can be called upon to adjust the created
song_node structs (nodes)

    * create_node - return a new node with field values inputted by the user
    * prepend_node - places a node at the beginning of the linked list
    * append_node -  places a node at the end of the linked list
    * insert_node_at - inserts a node in a specified position of the linked list
    * remove_head_node - removes the first node of the linked list
    * remove_tail_node - removes the last node of the linked list
    * remove_node_at - removes a node in a specified position of the linked list
    * count_nodes - returns the number of nodes in the linked list
    * display_head_node - shows the contents of the first node in the linked list
    * display_tail_node - shows the contents of the last node in the linked list
    * display_node_at - shows a nodes' contents in a specified position of the linked list
    * display_nodes - displays the contents of all nodes in the linked list
    * contains_value - returns true or false if a song is within one of the nodes
    *                  in the linked list
    * find_node - returns the node's index for a specified song
    * free_nodes - frees all allocated nodes from the linked list
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list_playlist.h"

node *create_node(char *artist, char *song_title, int minute_len){
    /*
    Allocates space for a new node with field values inputted by the user

    Parameters
    ----------
    artist : char
        The artist's name to be used for the artist_field
    song_title : char
        The song title to be used for the song_title field
    minute_len : int
        The length of the song to be used for the minute_len field

    Returns
    -------
    node
        a node with the field values inputted by the user
    */

    node *new_node = malloc(sizeof(node));
    new_node->artist = strdup(artist);
    new_node->song_title = strdup(song_title);
    new_node->minute_len = minute_len;
    new_node->next = NULL;

    return new_node;
}

void prepend_node(node **head, char *artist, char *song_title, int minute_len){
    /*
    Creates a node and places it as the head of the linked list

    Parameters
    ----------
    head : double ptr
        The address to a pointer that has the address of the first node
        in the linked list
    artist : char
        The artist's name to be used for the artist field in the new node
    song_title : char
        The song title to be used for the song_title field in the new node
    minute_len : int
        The length of the song to be used for the minute_len field in the new node
    */

    node *new_node = create_node(artist, song_title, minute_len);

    new_node->next = *head;
    *head = new_node;

}

void append_node(node **head, char *artist, char *song_title, int minute_len){
    /*
    Creates a node and places it as the tail of the linked list

    Parameters
    ----------
    head : double ptr
        The address to a pointer that has the address of the first node
        in the linked list
    artist : char
        The artist's name to be used for the artist field in the new node
    song_title : char
        The song title to be used for the song_title field in the new node
    minute_len : int
        The length of the song to be used for the minute_len field in the new node
    */

    node *new_node = create_node(artist, song_title, minute_len);

    //Case 1: There are no nodes so head will be changed to this created node
    if (*head == NULL){
        *head = new_node;
    }

    //Case 2: Head will remain unaltered so go to the end of the linked list
    //        and append new node
    else{
        node *temp = *head;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void insert_node_at(node **head, int index, char *artist, char *song_title, int minute_len){
    /*
    Creates a node and places it in a specified position of the linked list

    Parameters
    ----------
    head : double ptr
        The address to a pointer that has the address of the first node
        in the linked list
    artist : char
        The artist's name to be used for the artist field in the new node
    song_title : char
        The song title to be used for the song_title field in the new node
    minute_len : int
        The length of the song to be used for the minute_len field in the new node
    */

    int total_nodes = 0;

    total_nodes = count_nodes(*head);

    //Case 1: Insert as head node so use prepend_node function
    if(index == 1){

        prepend_node(head, artist, song_title, minute_len);

    }


    //Case 2: Insert as tail node so use append_node function
    else if (index > total_nodes)
    {
        append_node(head, artist, song_title, minute_len);
    }


    //Case 3: Place new node in between two other nodes
    else
    {
        node *new_node = create_node(artist, song_title, minute_len);

        node *temp = *head;

        for(int count = 1; count != index; count++){

            if (count == (index-1)){
                new_node->next = temp->next;
                temp->next = new_node;
            }

            temp = temp->next;

        }
    }
}


void remove_head_node(node **head){
    /*
    Frees the head node of the linked list

    Parameters
    ----------
    head : double ptr
        The address to a pointer that has the address of the first node
        in the linked list
    */

    //Case 1: No nodes to remove so just return
    if (*head == NULL){

        return;

    }

    //Case 2: Remove head node
    else{

        node *temp = *head;
        *head = (*head)->next;
        free(temp->artist);
        free(temp->song_title);
        free(temp);
    }
}

void remove_tail_node(node **head){
    /*
    Frees the tail node of the linked list

    Parameters
    ----------
    head : double ptr
        The address to a pointer that has the address of the first node
        in the linked list
    */

    //Case 1: No nodes to remove so just return
    if (*head == NULL){

        return;

    }

    //Case 2: Only one node so head will change
    else if((*head)->next == NULL){

        free((*head)->artist);
        free((*head)->song_title);
        free(*head);
        *head = NULL;

    }

    //Case 3: Head will not change so keep its position and free tail node
    else{

        node *temp = *head;
        while(temp->next->next != NULL){
            temp = temp->next;
        }

        free(temp->next->artist);
        free(temp->next->song_title);
        free(temp->next);
        temp->next = NULL;

    }
}

void remove_node_at(node **head, int index){
    /*
    Frees a specified node in the linked list

    Parameters
    ----------
    head : double ptr
        The address to a pointer that has the address of the first node
        in the linked list
    index : int
        The node to be freed from the linked list
    */

    int total_nodes = 0;

    total_nodes = count_nodes(*head);


    //Case 1: No nodes to remove so just return
    if (head == NULL){
        return;
    }

    //Case 2: Free head node
    else if(index == 1){
        remove_head_node(head);
    }

    //Case 3: Free tail node
    else if(index >= total_nodes){
        remove_tail_node(head);

    }


    //Case 4: Remove node that is in between two other nodes
    else{

        node *temp1 = *head;
        node *temp2 = *head;

        for(int count = 1; count != index; count++){

            if(count == (index-1)){
                temp2 = temp2->next;
                temp1->next = temp1->next->next;
                free(temp2->artist);
                free(temp2->song_title);
                free(temp2);
                temp2 = temp1;
            }

            temp1 = temp1->next;
            temp2 = temp2->next;
        }

    }
}

int count_nodes(node *head){
    /*
    Counts the number of nodes in the linked list

    Parameters
    ----------
    head : ptr
        The address of the first node of the linked list

    Returns
    -------
    int
        the number of nodes in the linked list
    */

    int count = 0;

    for(; head != NULL; head = head->next){
        count++;
    }

    return count;

}

void display_head_node(node *head){
    /*
    Displays the head nodes' content

    Parameters
    ----------
    head : ptr
        The address of the first node of the linked list
    */

    if(head != NULL){
        printf("First Song in Playlist: \nArtist: %s; Song: %s; Duration: %d\n", head->artist, head->song_title, head->minute_len);
    }
    else{
        puts("No Song to Display");
    }

}

void display_tail_node(node *head){
    /*
    Displays the tail nodes' content

    Parameters
    ----------
    head : ptr
        The address of the first node of the linked list
    */

    if(head != NULL){
        while(head->next != NULL){
            head = head->next;
        }
        printf("Last Song in Playlist: \nArtist: %s; Song: %s; Duration: %d\n", head->artist, head->song_title, head->minute_len);
    }

    else{
        puts("No Song to Display");
    }
}


void display_node_at(node *head, int index){
    /*
    Displays the specified nodes' content

    Parameters
    ----------
    head : ptr
        The address of the first node of the linked list
    index : int
        The node to be displayed from the linked list
    */

    int total_nodes = 0;
    int count = 1;

    total_nodes = count_nodes(head);

    if(head != NULL){
        while((head->next != NULL) && (index != count)){
            head = head->next;
            count++;
        }
        if(total_nodes < index){
            index = total_nodes;
            printf("Largest index value possible is %d. So...\n", total_nodes);
        }
        printf("\nSong %d in Playlist: \nArtist: %s; Song: %s; Duration: %d\n", index, head->artist, head->song_title, head->minute_len);
    }

    else{
        puts("\nNo Song to Display");
    }
}

void display_nodes(node *head){
    /*
    Displays every nodes' content

    Parameters
    ----------
    head : ptr
        The address of the first node of the linked list
    */

    if(head == NULL){
        puts("No Song(s) to Display");
        return;
    }

    int count = 1;

    for(; head != NULL;  head = head->next){

        printf("Song %d: (Artist: %s; Song: %s; Duration: %d)\n", count, head->artist, head->song_title, head->minute_len);
        count++;
    }
}

int contains_value(node *head, char *input_song_title){
    /*
    Determines if a specified song is contained in a node

    Parameters
    ----------
    head : ptr
        The address of the first node of the linked list
    input_song_title : char
        The string to be searched for within the linked list

    Returns
    -------
    int
        a true or false value that will tell the user whether the linked
        list contains the specified song
    */

    for(; head != NULL; head = head->next){

        if(!(strcmp(head->song_title, input_song_title))){
            return 1;
        }
    }
    return 0;

}

int find_node(node *head, char *input_song_title){
    /*
    Finds the node that contains the specified song

    Parameters
    ----------
    head : ptr
        The address of the first node of the linked list
    input_song_title : char
        The string to be searched for within the linked list

    Returns
    -------
    int
        the index value of the node that contains the specified song
    */

    int index = 1;

    for(; head != NULL; head = head->next){

        if(!(strcmp(head->song_title, input_song_title))){
            return index;
        }

        index++;

    }

    return 0;

}

void free_nodes(node **head){
    /*
    Frees all nodes in the linked list

    Parameters
    ----------
    head : double ptr
        The address to a pointer that has the address of the first node
        in the linked list
    */

    node *temp1 = *head;
    node *temp2 = *head;

    while(temp1 != NULL){

        temp1 = temp1->next;
        free(temp2->artist);
        free(temp2->song_title);
        free(temp2);
        temp2 = temp1;
    }

    *head = NULL;

    return;

}