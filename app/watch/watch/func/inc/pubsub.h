#ifndef PUBSUB_H
#define PUBSUB_H

#include <stdint.h>

// Message structure
typedef struct {
    int id;
    char data[256];
} PubSub_Message_t;

// subscriber_t function pointer type
typedef void (*subscriber_t)(PubSub_Message_t);

// subscriber_node_t structure
typedef struct _subscriber_node_t {
    subscriber_t subscriber;
    struct _subscriber_node_t *next;
} subscriber_node_t;

// Publisher structure
typedef struct {
    subscriber_node_t *subscribers;
} PubSub_Publisher_t;

// Function declarations
void Publisher_init(PubSub_Publisher_t *publisher);
void Publisher_subscribe(PubSub_Publisher_t *publisher, subscriber_t subscriber);
void Publisher_unsubscribe(PubSub_Publisher_t *publisher, subscriber_t subscriber);
void Publisher_publish(PubSub_Publisher_t *publisher, PubSub_Message_t message);

extern PubSub_Publisher_t SDL_KeyBoard_Publisher;

#endif // PUBSUB_H
