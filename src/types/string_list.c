#include "string_list.h"
#include "src/rust_interface/rust_interface.h"
#include <stdlib.h>
#include <string.h>

void push_to_string_list(StringList *list, const char *string) {
    char **city = &(list->cities[list->length++]);

    *city = malloc(strlen(string) + 1);

    strcpy(*city, string);
}

void free_string_list(StringList *list) {
    for (int i = 0; i < list->length; i++)
        free(list->cities[i]);

    free(list);
}

StringList *string_list_new() {
    StringList *list;
    list = malloc(sizeof(StringList));
    list->length = 0;
    return list;
}

ListCString *string_list_as_list_c_string(struct StringList *list) {
    ListCString *c_list = malloc(sizeof(ListCString));
    if (!c_list)
        return NULL;

    c_list->length = list->length;

    c_list->strings = malloc(sizeof(char *) * list->length);
    if (!c_list->strings) {
        free(c_list);
        return NULL;
    }

    for (int i = 0; i < list->length; ++i) {
        c_list->strings[i] = list->cities[i];
    }

    return c_list;
}

StringList *city_list() {
    StringList *cities = string_list_new();
    push_to_string_list(cities, "Aachen");
    push_to_string_list(cities, "Antwerpen");
    push_to_string_list(cities, "Berlin");
    push_to_string_list(cities, "Bremen");
    push_to_string_list(cities, "Brighton");
    push_to_string_list(cities, "Brüssel");
    push_to_string_list(cities, "Budapest");
    push_to_string_list(cities, "Dortmund");
    push_to_string_list(cities, "Dresden");
    push_to_string_list(cities, "Düsseldorf");
    push_to_string_list(cities, "Edinburgh");
    push_to_string_list(cities, "Florenz");
    push_to_string_list(cities, "Frankfurt");
    push_to_string_list(cities, "Graz");
    push_to_string_list(cities, "Hamburg");
    push_to_string_list(cities, "Köln");
    push_to_string_list(cities, "Kopenhagen");
    push_to_string_list(cities, "Leipzig");
    push_to_string_list(cities, "Mailand");
    push_to_string_list(cities, "München");
    push_to_string_list(cities, "Nürnberg");
    push_to_string_list(cities, "Prag");
    push_to_string_list(cities, "Rotterdam");
    push_to_string_list(cities, "Salzburg");
    push_to_string_list(cities, "Stuttgart");
    push_to_string_list(cities, "Venedig");
    push_to_string_list(cities, "Warschau");
    push_to_string_list(cities, "Weimar");
    push_to_string_list(cities, "Wien");

    return cities;
}