/*User Interface For Playlist

Allows the user to configure the songs they want in their playlist
by using linked list functionality.

This file contains the following functions:

    * ask_inputs - adjusts the field values for the song_node struct
    * main - displays the UI and calls upon functions to configure the playlist
*/


#include <stdio.h>
#include <string.h>
#include "linked_list_playlist.h"


char artist[4096];
char song_title[4096];
int minute_len = 0;
char term;

char ask_inputs(){
    /*
    Asks the users a series of questions to adjust field values in the 
    song_node struct
    */

    printf("Enter Artist's Name: ");
    fgets(artist, sizeof(artist), stdin);
    artist[strcspn(artist, "\n")] = 0;

    printf("Enter Song Title: ");
    fgets(song_title, sizeof(song_title), stdin);
    song_title[strcspn(song_title, "\n")] = 0;

    printf("Enter Length of Song in Minutes: ");
    scanf("%d%c", &minute_len, &term);

}

int main(){
    /*
    Displays the options to configure the user's playlist
    and then calls upon the appropriate linked list functions
    to adjust the playlist.
    */

    node *head = NULL;

    int user_input = 0;
    int index = 0;
    int total_nodes = 0;

    puts("\nWelcome to the Virtual Playlist!\n");

    while(1){

        puts("\nPlease choose one of the options below:");
        puts("1. Add Song to Beginning of Playlist");
        puts("2. Add Song to End of Playlist");
        puts("3. Add Song at i-th Place in Playlist");
        puts("4. Remove First Song in Playlist");
        puts("5. Remove Last Song in Playlist");
        puts("6. Remove i-th Song in Playlist");
        puts("7. Show Total Number of Songs");
        puts("8. Show First Song in Playlist");
        puts("9. Show Last Song in Playlist");
        puts("10. Show i-th Song in Playlist");
        puts("11. Show All Songs");
        puts("12. Check if Song is in Playlist");
        puts("13. Find Song");
        puts("14. Erase Entire Playlist");
        puts("15. Exit Program\n");
        fputs("Option: ", stdout);

        if((scanf("%d%c", &user_input, &term) == 2) || (term = '\n')){
            puts("");

            switch(user_input){
                case 1:
                    ask_inputs();
                    prepend_node(&head, artist, song_title, minute_len);
                    break;

                case 2:
                    ask_inputs();
                    append_node(&head, artist, song_title, minute_len);
                    break;

                case 3:
                    printf("Enter Index to Insert Song At: ");
                    scanf("%d%c", &index, &term);
                    ask_inputs();
                    insert_node_at(&head, index, artist, song_title, minute_len);
                    total_nodes = count_nodes(head);
                    if(total_nodes < index){
                        index = total_nodes;
                        printf("Largest index value possible is %d. So...\n", total_nodes);
                    }
                    printf("Inserted Song in Index %d of Playlist.\n", index);
                    break;

                case 4:
                    remove_head_node(&head);
                    printf("Removed First Song in Playlist.\n");
                    break;

                case 5:
                    remove_tail_node(&head);
                    printf("Removed Last Song in Playlist.\n");
                    break;

                case 6:
                    printf("Enter Index to Remove Song At: ");
                    scanf("%d%c", &index, &term);
                    total_nodes = count_nodes(head);
                    remove_node_at(&head, index);
                    if(total_nodes < index){
                        index = total_nodes;
                        printf("Largest index value possible is %d. So...\n", total_nodes);
                    }
                    printf("Removed Song %d in Playlist.\n", index);
                    break;

                case 7:
                    total_nodes = count_nodes(head);
                    printf("Total Songs in Playlist: %u\n", total_nodes);
                    break;

                case 8:
                    display_head_node(head);
                    break;

                case 9:
                    display_tail_node(head);
                    break;

                case 10:
                    printf("Enter Index to Display Song At: ");
                    scanf("%d%c", &index, &term);
                    display_node_at(head, index);
                    break;

                case 11:
                    display_nodes(head);
                    break;

                case 12:
                    printf("What song would you like to see is in the Playlist?\n");
                    fgets(song_title, sizeof(song_title), stdin);
                    song_title[strcspn(song_title, "\n")] = 0;
                    int contains_bool = 0;
                    contains_bool = contains_value(head, song_title);
                    if(contains_bool){
                        puts("This Song is in the Playlist!");
                    }
                    else{
                        puts("This Song is NOT in the Playlist!");
                    }
                    break;

                case 13:
                    printf("What song would you like to find in the Playlist?\n");
                    fgets(song_title, sizeof(song_title), stdin);
                    song_title[strcspn(song_title, "\n")] = 0;
                    int found_node_index = 0;
                    found_node_index = find_node(head, song_title);
                    if(found_node_index){
                        printf("\nThis Song is in index %d of the Playlist!\n", found_node_index);
                    }
                    else{
                        puts("\nThis Song is NOT in the Playlist!");
                    }
                    break;

                case 14:
                    free_nodes(&head);
                    puts("Erased Entire Playlist!");
                    break;

                case 15:
                    free_nodes(&head);
                    return 0;

                default:
                    puts("Not a Valid Option. Try Again!");
            }
        }

        else{
            puts("Not a Valid Option. Try Again!");
        }

    }

    return 0;

}


