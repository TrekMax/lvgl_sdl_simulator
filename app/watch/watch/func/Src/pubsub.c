#include "pubsub.h"
#include <stdlib.h>
#include <stdio.h>

PubSub_Publisher_t SDL_KeyBoard_Publisher;

// Initialize the publisher
void Publisher_init(PubSub_Publisher_t *publisher)
{
    publisher->subscribers = NULL;
}

// Subscribe a new subscriber
void Publisher_subscribe(PubSub_Publisher_t *publisher, subscriber_t subscriber)
{
    subscriber_node_t *node = (subscriber_node_t *)malloc(sizeof(subscriber_node_t));
    if (node == NULL) {
        // Handle memory allocation failure
        return;
    }
    node->subscriber = subscriber;
    node->next = publisher->subscribers;
    publisher->subscribers = node;
}

// Unsubscribe an existing subscriber
void Publisher_unsubscribe(PubSub_Publisher_t *publisher, subscriber_t subscriber)
{
    subscriber_node_t **current = &publisher->subscribers;
    while (*current != NULL) {
        if ((*current)->subscriber == subscriber) {
            subscriber_node_t *to_delete = *current;
            *current = (*current)->next;
            free(to_delete);
            return;
        }
        current = &((*current)->next);
    }
}

// Publish a message to all subscribers
void Publisher_publish(PubSub_Publisher_t *publisher, PubSub_Message_t message)
{
    subscriber_node_t *node = publisher->subscribers;
    while (node != NULL) {
        node->subscriber(message);
        node = node->next;
    }
}
