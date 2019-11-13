typedef struct list_item_type 
{
    int complexity;
    int entranceTime;
    int password;
    int priority;
    struct list_item_type* next_item;
} list_item;

typedef struct 
{
    list_item* first_item;
    int size;
    bool isPriority;
    int estimatedTime;
    bool stopType;
    int periodLastStop; 
} list;

void list_initialize(list* l);
list_item* list_item_allocate(int _priority, int _entranceTime, int _password, int _complexity);
void list_print(list* l);
bool list_insert_at(list* l, int _priority, int _entranceTime, int _password, int _complexity, int pos);
bool list_insert_end(list* l, int _priority, int _entranceTime, int _password, int _complexity);
bool list_at(list* l, int* _priority, int* _entranceTime, int* _password, int* _complexity, int pos);
bool list_remove_at(list* l, int pos);
