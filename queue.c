#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SEEN_STATES 10461394944

void enqueue(struct queue *q, struct game_state state) {
    size_t value = serialize(state);
    insert_at_tail(&q->data, value);
}

struct game_state dequeue(struct queue *q) { 
    size_t value = remove_from_head(&q->data);
    return (struct game_state){0}; 
}

int number_of_moves(struct game_state start) { 
    if (is_solved(start)) {
        return 0;
    }

    bool *seen = calloc(MAX_SEEN_STATES, sizeof(bool));
    if (!seen) {
        return -1;  // Memory allocation failure
    }

    struct node {
        struct game_state state;
        struct node *next;
    };

    struct node *queue_front = malloc(sizeof(struct node));
    queue_front->state = start;
    queue_front->next = NULL;
    struct node *queue_rear = queue_front;

    while (queue_front) {
        struct game_state cur = queue_front->state;

        struct node *temp = queue_front;
        queue_front = queue_front->next;
        free(temp);

        struct game_state children[4];
        int n = valid_moves(cur, children);

        for (int i = 0; i < n; i++) {
            uint64_t hash = serialize(children[i]) % MAX_SEEN_STATES;
            if (!seen[hash]) {
                seen[hash] = true;

                if (is_solved(children[i])) {
                    free(seen);
                    while (queue_front) {
                        struct node *temp = queue_front;
                        queue_front = queue_front->next;
                        free(temp);
                    }
                    return children[i].num_steps;
                }

                struct node *new_node = malloc(sizeof(struct node));
                new_node->state = children[i];
                new_node->next = NULL;
                queue_rear->next = new_node;
                queue_rear = new_node;
            }
        }
    }

    free(seen);
    return -1;
}
