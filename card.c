#include <stdio.h>
#include <string.h>
#include "card.h"

// This is my code! It's goal is to create cards and perform various functions thereon.

const char *suit_fmt[] = {"#", "Clubs", "Diamonds", "Hearts", "Spades"};
const char *rank_fmt[] = {"#", "#", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
const char *suit_fmt_min[] = {"#", "C", "D", "H", "S"};
const char *rank_fmt_min[] = {"#", "#", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

const int suit_length = 5;
const int rank_length = 15;
const int BUFFER_LENGTH = 2;

/*
 * Purpose: create a new card
 * Input: rank and suit of the card
 * Return: a card of particular rank and suit
 */
card_t card_create(int rank, int suit)
{
    if ((rank < 1 || rank > 14) || (suit < 1 || suit > 4))
        return INVALID_CARD;
    card_t new_card;
    new_card.rank = rank;
    new_card.suit = suit;
    return new_card;
}

/*
 * Purpose: print a card and its values
 * Input: card to print
 * Return: nothing
 */
void card_print(card_t card)
{
    printf("%s of %s\n", rank_fmt[card.rank], suit_fmt[card.suit]);
}

/*
 * Purpose: compare two cards
 * Input: the cards to compare
 * Return: difference of rank or suit
 */
int card_compare(card_t card_one, card_t card_two)
{
    if (card_one.suit != card_two.suit)
        return card_one.suit - card_two.suit;
    return card_one.rank - card_two.rank;
}

/*
 * Purpose: retrieve index of character entered by user
 * Input: suit or rank, relative format array, size of that array
 * Return: index of that character from relative fmt_min array
 */
int get_index(char *type, char *fmt[], int size)
{
    int index = -1;
    for (int i = 0; i < size; i++)
        if (strcmp(fmt[i], type) == 0)
            index = i;
    return index;
}

/*
 * Purpose: read and create a card from user in
 * Input: rank and suit of card to create
 * Return: the card created or INVALID CARD
 */
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