#ifndef __DOUBLY_LINK_H__
#define __DOUBLY_LINK_H__

typedef struct doubly_link {
    struct doubly_link *next, *prev;
} doubly_link_t;

static inline void doubly_link_init_head(doubly_link_t *head) {
    head->next = head;
    head->prev = head;
}

static inline void doubly_link_add(doubly_link_t *new, doubly_link_t *head) {
    head->next->prev = new;
    new->next = head->next;
    new->prev = head;
    head->next = new;
}

#endif
