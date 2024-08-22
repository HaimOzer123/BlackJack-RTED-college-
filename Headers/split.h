#ifndef SPLIT_H
#define SPLIT_H

#include "hand.h"

int can_split(CardList *hand);
void perform_split(CardList *hand, CardList *hand2, CardList *deck);

#endif
