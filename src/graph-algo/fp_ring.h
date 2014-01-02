#ifndef FP_RING_H_
#define FP_RING_H_

/* A data-structure to communicate pointers between components */
struct fp_ring {
	uint32_t head;
	uint32_t tail;
	uint32_t mask;
	void *elem[0]; // must be last in struct
};

/**
 * Creates a new backlog queue, with 2^{log_size} elements
 */
static inline
struct fp_ring *fp_ring_create(uint32_t log_size) {
	uint32_t num_elems = (1 << log_size);
	uint32_t mem_size = sizeof(struct fp_ring)
							+ num_elems * sizeof(void *);
    struct fp_ring *ring = malloc(mem_size);
    assert(ring != NULL);

    ring->mask = num_elems - 1;
	ring->head = 0;
	ring->tail = 0;
    return ring;
}

// Insert new bin to the back of this backlog queue
static inline
void fp_ring_enqueue(struct fp_ring *ring, void *elem) {
	assert(ring != NULL);
	assert(elem != NULL);
	assert(ring->tail != ring->head - ring->mask - 1);

	ring->elem[ring->tail & ring->mask] = elem;
	ring->tail++;
}

// Insert new bin to the back of this backlog queue
static inline void * fp_ring_dequeue(struct fp_ring *ring) {
	assert(ring != NULL);
	assert(ring->head != ring->tail);

	return ring->elem[ring->head++ & ring->mask];
}

// Insert new bin to the back of this backlog queue
static inline int fp_ring_empty(struct fp_ring *ring) {
	assert(ring != NULL);
	return (ring->head == ring->tail);
}

static inline
void destroy_pointer_queue(struct fp_ring *queue) {
    assert(queue != NULL);
	assert(queue->head == queue->tail);

    free(queue);
}


#endif /* FP_RING_H_ */