#ifndef DEQUE
# define DEQUE

# ifndef ARRAY_LENGTH
#  define ARRAY_LENGTH(A) (sizeof(A) / sizeof(*(A)))
# endif

# include <stddef.h>
# include <stdbool.h>

typedef struct s_deque	deque;

/* Structure members shall not be accessed directly */
struct              s_deque
{
	void*		data;
	void*		front;
	void*		back;
	size_t		type_size;
	unsigned	capacity;
};

/* This constructor can be used if the storage is a C static array */
# define DEQUE_NEW(ARRAY) DEQUE_new(ARRAY, sizeof(*ARRAY), ARRAY_LENGTH(ARRAY))

/* Returns an initialized deque that uses the specified storage */
deque				DEQUE_new(void* data, size_t type_size, unsigned capacity);
/* Right after creation, specify an intended usage */
bool				DEQUE_intent(deque* self, char intent);

void*				DEQUE_first(deque* self);
void*				DEQUE_last(deque* self);

/* Number of elements stored */
unsigned			DEQUE_size(deque* self);
/* Maximum number of elements that can be stored */
unsigned			DEQUE_max(deque* self);

bool				DEQUE_is_empty(deque* self);
bool				DEQUE_is_full(deque* self);

bool				DEQUE_push_back(deque* self, void* elements, unsigned count);
bool				DEQUE_push_front(deque* self, void* elements, unsigned count);
bool				DEQUE_push_back_one(deque* self, void* element);
bool				DEQUE_push_front_one(deque* self, void* element);

#endif /* DEQUE */
