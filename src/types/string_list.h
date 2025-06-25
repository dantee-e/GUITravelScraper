
#define NUMBER_OF_CITIES 100

struct StringList {
    int length;
    char *cities[NUMBER_OF_CITIES];
};
typedef struct StringList StringList;

void push_to_string_list(StringList *list, char *string);

void free_string_list(StringList *list);

StringList *string_list_new();

StringList *city_list();