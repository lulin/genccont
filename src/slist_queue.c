#include "slist_queue.h"

void genc_slq_init(struct slist_queue* queue)
{
	queue->head = NULL;
	queue->tail = &queue->head;
}

/** Inserts the given item at the back of the queue. */
void genc_slq_push_back(struct slist_queue* queue, struct slist_head* new_item)
{
	queue->tail = genc_slist_insert_at(new_item, queue->tail);
}

/** Inserts the given at the front of the queue. */
void genc_slq_push_front(struct slist_queue* queue, struct slist_head* new_item)
{
	if (!queue->head)
	{
		/* adding to front of empty queue is identical to adding to its back (tail needs updating) */
		genc_slq_push_back(queue, new_item);
	}
	else
	{
		genc_slist_insert_at(new_item, &queue->head);
	}
}


/** Pops an item off the front of the queue, returning it. */
struct slist_head* genc_slq_pop_front(struct slist_queue* queue)
{
	struct slist_head* removed = genc_slist_remove_at(&queue->head);
	if (!removed) return NULL;
	if (!queue->head)
	{
		/* queue is now empty */
		queue->tail = &queue->head;
	}
	return removed;
}

int genc_slq_is_empty(struct slist_queue* queue)
{
	return !queue->head;
}

void genc_slq_swap(struct slist_queue* queue1, struct slist_queue* queue2)
{
	if (queue1 == queue2)
		return;
	
	struct slist_queue tmp_q = *queue1;
	*queue1 = *queue2;
	*queue2 = tmp_q;
		
	/* fix up empty queue tails if necessary*/
	if (queue1->tail == &queue2->head)
		queue1->tail = &queue1->head;
	if (queue2->tail == &queue1->head)
		queue2->tail = &queue2->head;
}
