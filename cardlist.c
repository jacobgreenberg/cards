#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "card.h"
#include "cardlist.h"

// This is my code! Its goal is to create a deck of cards and perform various functions thereon.

/*
 * Purpose: create a new deck of cards
 * Input: nothing
 * Return: NULL (an empty deck)
 */
card_deck_t deck_create()
{
    return NULL;
}

/*
 * Purpose: push a card onto the beginning of the deck
 * Input: the deck being pushed to and the card to push
 * Return: success(0), failure(1)
 */
int deck_push(card_deck_t *deck, card_t card)
{
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL)
        return 1;
    new_node->card = card;
    new_node->next = *deck;
    *deck = new_node;
    return 0;
}

/*
 * Purpose: append a card onto the end of the deck
 * Input: the deck being appended to and the card to append
 * Return: success(0), failure(1)
 */
int deck_append(card_deck_t *deck, card_t card)
{
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL)
        return 1;
    node_t *tail = *deck;
    new_node->card = card;
    new_node->next = NULL;

    if (*deck == NULL) // if deck is empty
    {
        *deck = new_node;
        return 0;
    }

    while (tail->next != NULL)
        tail = tail->next;

    tail->next = new_node;
    return 0;
}

/*
 * Purpose: search the deck for a specific card
 * Input: the deck being searched and the card being search for
 * Return: true(found), false(not found)
 */
bool deck_search(card_deck_t *deck, card_t card)
{
    node_t *curr = *deck;
    while (curr != NULL)
    {
        if (card_compare(curr->card, card) == 0)
            return true;
        curr = curr->next;
    }
    return false;
}

/*
 * Purpose: delete a particular card from the deck
 * Input: deck to delete from and card being deleted
 * Return: success(0), failure(1)
 */
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

/*
 * Purpose: print the deck of cards
 * Input: the deck to print
 * Return: nothing
 */
void deck_print(card_deck_t *deck)
{
    for (node_t *curr = *deck; curr != NULL; curr = curr->next)
        card_print(curr->card);
}

/*
 * Purpose: free all memory allocated by cards in the deck
 * Input: the desk to free cards from
 * Return: nothing
 */
void deck_free(card_deck_t *deck)
{
    node_t *curr = *deck;
    node_t *temp;
    while (curr != NULL)
    {
        temp = curr;
        curr = curr->next;
        free(temp);
    }
}