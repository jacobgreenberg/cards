#ifndef CARD_H
#define CARD_H

typedef struct card_s
{
    int suit;
    int rank;
} card_t;

static const card_t INVALID_CARD = {-1, -1};

card_t card_create(int rank, int suit);

void card_print(card_t card);

card_t card_read();

int card_compare(card_t card_one, card_t card_two);

#endif
