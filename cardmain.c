#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "cardlist.h"

// This is my code! Its goal is to create and manipulate a deck of cards based on user input.

#define INSERT_BEGINNING 'b'
#define INSERT_END 'e'
#define DELETE 'd'
#define FIND 'f'
#define PRINT 'p'
#define QUIT 'q'

static const int BUFFER_LENGTH = 2;

/* Purpose: print a message and terminate the program
 * Input: the message
 * Return: never! terminates program
 */
static void die(char *msg)
{
    perror(msg);
    exit(-1);
}

/*
 * Purpose: print the programs usage to console
 * Input: nothing
 * Return: nothing
 */
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

/*
 * Purpose: Interpret user input and perform operations on the cards and deck therefore
 * Input: Program options from stdin (insert, delete, search, print, quit)
 * Return: success(0), failure(1)
 */
int main(int argc, char *argv[])
{
    printf("This program maintains a deck of cards as a linked list!\n\n");
    usage();
    char command[BUFFER_LENGTH];
    card_t card;
    card_deck_t deck = deck_create();

    while (1)
    {
        printf("\nEnter a command: ");
        if (scanf("%1s", command) < 1)
            die("scanf command: ");

        if (*command != INSERT_BEGINNING && *command != INSERT_END && *command != DELETE && *command != FIND &&
            *command != QUIT && *command != PRINT)
        {
            fprintf(stderr, "Invalid command\n\n");
            usage();
            continue; // return to loop top
        }

        if (*command != QUIT && *command != PRINT)
        {
            card = card_read();
            if (card_compare(card, INVALID_CARD) == 0)
            {
                fprintf(stderr, "You've entered an invalid card!\n");
                continue;
            }
        }

        bool found; // return value for deck_search()
        int ret; // return variable for all other deck calls

        switch (*command)
        {
            case INSERT_BEGINNING:
                ret = deck_push(&deck, card);
                if (ret == 0)
                    printf("Push success!\n");
                else
                    fprintf(stderr, "Error pushing\n");
                break;

            case INSERT_END:
                ret = deck_append(&deck, card);
                if (ret == 0)
                    printf("Append success!\n");
                else
                    fprintf(stderr, "Error appending\n");
                break;

            case DELETE:
                ret = deck_delete(&deck, card);
                if (ret == 0)
                    printf("Delete success!\n");
                else
                    fprintf(stderr, "Card not in deck\n");
                break;

            case FIND:
                found = deck_search(&deck, card);
                if (found)
                {
                    printf("Found: ");
                    card_print(card);
                }
                else
                    fprintf(stderr, "Card not in deck\n");
                break;

            case PRINT:
                if (deck == NULL)
                    fprintf(stderr, "Deck empty\n");
                else
                    deck_print(&deck);
                break;

            case QUIT:
                deck_free(&deck);
                return 0;

            default:
                fprintf(stderr, "Invalid command\n\n");
                usage();
                break;
        }
    }
}
