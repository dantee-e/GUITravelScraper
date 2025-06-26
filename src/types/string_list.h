#include "src/rust_interface/rust_interface.h"
#define NUMBER_OF_CITIES 100

struct StringList {
    int length;
    char *cities[NUMBER_OF_CITIES];
};
typedef struct StringList StringList;

void push_to_string_list(StringList *list, const char *string);

void free_string_list(StringList *list);

StringList *string_list_new();

StringList *city_list();

ListCString *string_list_as_list_c_string(struct StringList *list);