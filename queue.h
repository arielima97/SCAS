enum attendanceComplexity { EXPRESS = 1, NORMAL = 2, COMPLEX = 3 };
typedef enum attendanceComplexity attComp;

typedef struct queue_item_type
{
    attComp complexity;
    int ID;
    int timestamp;
    int password;
    bool priority;
    struct queue_item_type* next_item;
} queue_item;

typedef struct {
    queue_item* first_item;
    queue_item* last_item;
    int size;
} queue;

queue_item* queue_item_allocate(bool _priority, int _timestamp, int _ID, int _password, attComp _complexity);
void queue_initialize(queue* q);
bool queue_add(queue* q, bool priority, int _timestamp, int _ID, int _password, attComp _complexity);
bool queue_remove(queue* q, bool* priority, int* _timestamp, int* _ID, int* _password, attComp* _complexity);
void queue_clear(queue* q);
void queue_print(queue* q);