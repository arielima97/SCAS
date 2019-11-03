enum attendanceComplexity { EXPRESS = 2, NORMAL = 3, COMPLEX = 4 };
typedef enum attendanceComplexity attComp;

typedef struct queue_item_type
{
    attComp complexity;
    int password;
    struct queue_item_type* next_item;
} queue_item;

typedef struct {
    queue_item* first_item;
    queue_item* last_item;
    int size;
} queue;

queue_item* queue_item_allocate(int _password, attComp _complexity);
void queue_initialize(queue* q);
bool queue_add(queue* q, int _password, attComp _complexity);
bool queue_remove(queue* q, int* _password, attComp* _complexity);
void queue_clear(queue* q);