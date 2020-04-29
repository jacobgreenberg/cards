# Cardlist Design Decisions

```c
card_t card_read()
{
    card_t new_card;
    char suit[BUFFER_LENGTH];
    char rank[BUFFER_LENGTH];

    printf("Enter a rank: ");
    scanf("%2s", rank);
    printf("Enter a suit: ");
    scanf("%1s", suit);
    int rank_index = get_index(rank, (char **) rank_fmt_min, rank_length);
    int suit_index = get_index(suit, (char **) suit_fmt_min, suit_length);

    if (suit_index == -1 || rank_index == -1)
        new_card = INVALID_CARD;
    else
        new_card = card_create(rank_index, suit_index);
    
    return new_card;
}
```

The above method required a some thought in how the user would enter a new card from the console without having to type the entire rank and suit, such as "Ace of Spades", rather they could enter "A" in the first prompt (rank), then "S" int the second prompt (suit). Originally I wanted the ability for the user to enter "AS" on just one line, but this presented an issue with the user entering "10" for a card's rank, since it would be the only rank represented by two characters, making it more difficult to parse the input string and extract rank and suit separately. I realized that "10" could have been represented by "T", but that didn't follow the style of the other cards since only high ranks (Jack, Queen, King, Ace) and suits should be represented by letters. 



```c
void card_print(card_t card) // method one
{
    printf("%s of %s\n", rank_fmt[card.rank], suit_fmt[card.suit]);
}

void deck_print(card_deck_t *deck) // method two
{
    for (node_t *curr = *deck; curr != NULL; curr = curr->next)
        card_print(curr->card);
}
```

The first of the above methods prints a singular card, but I chose to include a newline character at the end of that statement. The second method calls card_print() when traversing the linked list and in doing so, prints each card on its own line. I felt that printing each card on a new line would improve readability and speed in potentially different sized terminal windows so that the outputs aren't split across lines.



```c
int deck_delete(card_deck_t *deck, card_t card)
{
    node_t *curr = *deck;
    if (curr == NULL)
        return 1;

    else if (card_compare(curr->card, card) == 0) // if head is the element to delete
    {
        node_t *temp = *deck;
        *deck = temp->next;
        free(temp);
        return 0;
    }

    while (curr->next != NULL) // if element to delete is not head
    {
        if (card_compare(curr->next->card, card) == 0)
        {
            node_t *temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
            return 0;
        }
        curr = curr->next;
    }
    return 1;
}
```

While I though deck_delete() would be nearly identical to deck_search() at first glance, I realized that instead of checking if the current element was NULL, I needed to check if the next element was NULL before operating on it. I started with modifying the search_deck() method by operating on the next element of current; and although this seemed like the most efficient way to delete a particular element in the list, I knew that I was ignoring the head of the list by first looking at its next element. Working backwards, I took the guts of what was inside the while loop and basically removed the next condition. 



```c
static void die(char *msg)
{
    perror(msg);
    exit(-1);
}

if (scanf("%1s", command) < 1)
    die("scanf command: ");

switch (*command)
{
	case PRINT:
		if (deck == NULL)
            fprintf(stderr, "Deck empty\n");
		else
            deck_print(&deck);
		break;
}
```

Although Dr. Isaacman provided the above method and implementation, I chose not to call die() in any of my code. I wanted to make sure my program was equipped to handle errors and exceptions without having to exit. In order to accomplish this, I used a series of sentinel conditions and prints to stderr throughout. The above block from a switch statement demonstrates on of the ways in which I implemented this type of procedure. 



```c
void usage()
{
    printf("Options:\n"
           "b: Insert a card at beginning of deck\n"
           "e: Insert a card at end of deck\n"
           "d: Delete a card from the deck\n"
           "f: Find a card in the deck\n"
           "p: Print the deck of cards\n"
           "q: Quit\n");
}

if (*command != INSERT_BEGINNING && *command != INSERT_END && *command != DELETE 
    && *command != FIND && *command != QUIT && *command != PRINT)
        {
            fprintf(stderr, "Invalid command\n\n");
            usage();
            continue; // return to loop top
        }
```

A simple design choice, but it's definitely important to remind the user of the proper program commands when the user fails to follow such.  An example call to usage() is displayed in the body of the above conditional. 