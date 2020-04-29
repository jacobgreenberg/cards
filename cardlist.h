#ifndef CARDLIST_H
#define CARDLIST_H

#include <stdbool.h>
#include "card.h"

typedef struct node_s
{
    card_t card;
    struct node_s *next;
} node_t;

typedef node_t *card_deck_t;

card_deck_t deck_create();

int deck_push(card_deck_t *deck, card_t card);

int deck_append(card_deck_t *deck, card_t card);

void deck_print(card_deck_t *deck);

bool deck_search(card_deck_t *deck, card_t card);

int deck_delete(card_deck_t *deck, card_t card);

void deck_free(card_deck_t *deck);

#endif