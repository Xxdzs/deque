#include "deque.h"
#include "deque_private.h"

bool		DEQUE_is_split(deque* self)
{/* Is data spread on two discontinuous memory slots */
	return (self->back < self->front);
}

void*		DEQUE_front(deque* self)
{/* Pointer to the first element */
	return (self->front);
}

void*		DEQUE_back(deque* self)
{/* Pointer to the would-be next-after-the-last element */
	return (self->back);
}

void*		DEQUE_begin(deque* self)
{/* Pointer to the start of the underlying storage */
	return (self->data);
}

void*		DEQUE_end(deque* self)
{/* Pointer one-past-the-end of the underlying storage */
	return (DEQUE_begin(self) + DEQUE_offset(self, self->capacity));
}

size_t		DEQUE_offset(deque* self, unsigned count)
{/* Size in memory of _count_ elements */
	return (self->type_size * count);
}

unsigned	DEQUE_distance(deque* self, void* elem1, void* elem2)
{/* Number of elements in the range delimited by those two elements (upper bound excluded) */
	return ((elem1 < elem2 ? elem2 - elem1 : elem1 - elem2) / self->type_size);
}

unsigned	DEQUE_interior(deque* self)
{/* Number of elements between front and back */
	return (DEQUE_distance(self, self->front, self->back));
}

unsigned	DEQUE_exterior(deque* self)
{/* Number of elements surrounding front and back */
	return (self->capacity - DEQUE_interior(self));
}

int			DEQUE_index(deque* self, void* element)
{/* Returns -1 if out of bound, -2 if outside storage */
	if (element < DEQUE_begin(self) || DEQUE_end(self) <= element)
		return (-2);
	if (self->front <= element && (element < self->back || DEQUE_is_split(self)))
		return (DEQUE_distance(self, element, self->front));
	if (element < self->back && DEQUE_is_split(self))
		return (DEQUE_size(self) - DEQUE_distance(self, element, self->back));
	return (-1);
}
