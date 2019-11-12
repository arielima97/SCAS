typedef struct list_item_type 
{
    int complexity;
    int ID;
    int password;
    bool priority;
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
list_item* list_item_allocate(bool _priority, int _ID, int _password, int _complexity);
void list_clear(list* l);
void list_print(list* l);
bool list_insert_at(list* l, bool _priority, int _ID, int _password, int _complexity, int pos);
bool list_insert_end(list* l, bool _priority, int _ID, int _password, int _complexity);
bool list_at(list* l, bool* _priority, int* _ID, int* _password, attComp* _complexity);
bool list_remove(list* l, int pos);
