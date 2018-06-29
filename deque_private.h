#ifndef DEQUE_PRIVATE_H
# define DEQUE_PRIVATE_H

/* Is data spread on two discontinuous memory slots */
bool				DEQUE_is_split(deque* self);

/* Pointer to the first element */
void*				DEQUE_front(deque* self);
/* Pointer to the would-be next-after-the-last element */
void*				DEQUE_back(deque* self);
/* Pointer to the start of the underlying storage */
void*				DEQUE_begin(deque* self);
/* Pointer one-past-the-end of the underlying storage */
void*				DEQUE_end(deque* self);

/* Size in memory of _count_ elements */
size_t				DEQUE_offset(deque* self, unsigned count);
/* Number of elements in the range delimited by those two elements (upper bound excluded) */
unsigned			DEQUE_distance(deque* self, void* elem1, void* elem2);
/* Number of elements between front and back */
unsigned			DEQUE_interior(deque* self);
/* Number of elements surrounding front and back */
unsigned			DEQUE_exterior(deque* self);
/* Returns -1 if out of bound, -2 if outside storage */
int					DEQUE_index(deque* self, void* element);
/* Move the specified pointer to the next/previous element */
void				DEQUE_move_one(deque* self, void** pointer, bool forward);

# define DEQUE_move_forward_one(SELF, PTR) DEQUE_move_one(SELF, &PTR, true)
# define DEQUE_move_backward_one(SELF, PTR) DEQUE_move_one(SELF, &PTR, false)

#endif /* DEQUE_PRIVATE_H */
