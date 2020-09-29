typedef struct song_node{

    char *artist;
    char *song_title;
    int minute_len;
    struct song_node *next;

} node;

node *create_node(char *artist, char *song_title, int minute_len);

void prepend_node(node **head, char *artist, char *song_title, int minute_len);

void append_node(node **head, char *artist, char *song_title, int minute_len);

void insert_node_at(node **head, int index, char *artist, char *song_title, int minute_len);

void remove_head_node(node **head);

void remove_tail_node(node **head);

void remove_node_at(node **head, int index);

int count_nodes(node *head);

void display_head_node(node *head);

void display_tail_node(node *head);

void display_node_at(node *head, int index);

void display_nodes(node *head);

int contains_value(node *head, char *input_song_title);

int find_node(node *head, char *input_song_title);

void free_nodes(node **head);