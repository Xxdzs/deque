#include "deque.h"
#include "deque_private.h"

#include <string.h>

#ifndef MIN
# define MIN(A,B) (A < B ? A : B)
#endif

deque		DEQUE_new(void* data, size_t type_size, unsigned capacity)
{/* Returns an initialized deque that uses the specified storage */
	return ((deque){data, data, data, type_size, capacity});
}

/*
** Before pushing any element, we can clarify our intentions to lower the chances of splitting data
** 'B' : will only push back
** 'b' : will mostly push back
** '2' : will push on both side
** 'f' : will mostly push front
** 'F' : will only push front
*/
bool        DEQUE_intent(deque* self, char intent)
{
	if (!DEQUE_is_empty(self))
		return (false);
	switch (intent)
	{
	case 'B' :	self->front = DEQUE_begin(self);											break;
	case 'b' :	self->front = DEQUE_begin(self) + DEQUE_offset(self, self->capacity / 4);	break;
	case '2' :	self->front = DEQUE_begin(self) + DEQUE_offset(self, self->capacity / 2);	break;
	case 'f' :	self->front = DEQUE_end(self) - DEQUE_offset(self, self->capacity / 4);		break;
	case 'F' :	self->front = DEQUE_end(self) - DEQUE_offset(self, 1);						break;
	default :	return (false);
	}
	self->back = self->front;
	return (true);
}

void*		DEQUE_first(deque* self)
{
	return (self->front);
}

void*		DEQUE_last(deque* self)
{
	return (((self->back == DEQUE_begin(self)) ? DEQUE_end(self) : self->back)
			- DEQUE_offset(self, 1));
}

unsigned	DEQUE_size(deque* self)
{/* Number of elements stored */
	return (DEQUE_is_split(self) ? DEQUE_exterior(self) : DEQUE_interior(self));
}

unsigned	DEQUE_max(deque* self)
{/* Maximum number of elements that can be stored */
	return (self->capacity - 1);
}

bool		DEQUE_is_empty(deque* self)
{
	return (self->front == self->back);
}

bool		DEQUE_is_full(deque* self)
{
	return (DEQUE_distance(self, self->front, self->back)
			== (DEQUE_is_split(self) ? 1 : DEQUE_max(self)));
}

bool		DEQUE_push_front_one(deque* self, void* element)
{
	if (DEQUE_size(self) == DEQUE_max(self))
		return (false);
	if (self->front == DEQUE_begin(self))
		self->front = DEQUE_end(self);
	self->front -= DEQUE_offset(self, 1);
	memcpy(self->front, element, DEQUE_offset(self, 1));
	return (true);
}

bool		DEQUE_push_front(deque* self, void* elements, unsigned count)
{
	if (DEQUE_max(self) < DEQUE_size(self) + count)
		return (false);
	while (count-- > 0)
	{
		DEQUE_push_front_one(self, elements);
		elements += DEQUE_offset(self, 1);
	}
	return (true);
}

bool		DEQUE_push_back_one(deque* self, void* element)
{
	if (DEQUE_size(self) == DEQUE_max(self))
		return (false);
	memcpy(self->back, element, DEQUE_offset(self, 1));
	self->back += DEQUE_offset(self, 1);
	if (self->back == DEQUE_end(self))
		self->back = DEQUE_begin(self);
	return (true);
}

bool		DEQUE_push_back(deque* self, void* elements, unsigned count)
{
	unsigned		first;

	if (DEQUE_max(self) < DEQUE_size(self) + count)
		return (false);
	first = MIN(count, DEQUE_distance(self, DEQUE_end(self), self->back));
	memcpy(self->back, elements, DEQUE_offset(self, first));
	self->back += DEQUE_offset(self, first);
	if (self->back == DEQUE_end(self))
	{
		self->back = DEQUE_begin(self);
		DEQUE_push_back(self, elements + DEQUE_offset(self, first), count - first);
	}
	return (true);
}
