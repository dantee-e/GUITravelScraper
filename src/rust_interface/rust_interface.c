#include "rust_interface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// Define C equivalents of Rust types

void print_room(Room *room) {
    printf("\t\tRoom %s for %s\n", room->name, room->price);
}
void print_hostel(Hostel *hostel) {
    printf("\tHostel %s\n", hostel->name);
    for (int i = 0; i < hostel->number_of_rooms; i++) {
        print_room(&hostel->room_options[i]);
    }
}
void print_city(City *city) {
    printf("City %s\n", city->name);
    for (int i = 0; i < city->hostels_len; i++) {
        print_hostel(&city->hostels[i]);
    }
}
void print_city_list(ListCCity *cities) {
    if (!cities)
        printf("city list nao existe\n");
    for (int i = 0; i < cities->len; i++) {
        print_city(&cities->cities[i]);
    }
}

int get_cities(const char **cities, const int num_cities,
               const char *date_start, const char *date_end) {
    //    const char *cities[] = {"Dresden", "Berlin"};
    //    int num_cities = 2;
    //    const char *date_start = "2025-07-01";
    //    const char *date_end = "2025-07-05";

    ListCString cities_names_c;
    cities_names_c.length = num_cities;
    cities_names_c.strings = (char **)malloc(num_cities * sizeof(char *));

    for (int i = 0; i < num_cities; i++) {
        cities_names_c.strings[i] = strdup(cities[i]);
        if (!cities_names_c.strings[i]) {
            fprintf(stderr, "String duplication failed\n");
            // Cleanup
            for (int j = 0; j < i; j++)
                free((void *)cities_names_c.strings[j]);
            free(cities_names_c.strings);
            return 1;
        }
    }

    // Call the Rust function
    ListCCity *result = get_many_cities(cities_names_c, date_start, date_end);

    print_city_list(result);

    // free_city_list(result);

    return 0;
}
// int get_cities(const char **cities, const int num_cities,
//                const char *date_start, const char *date_end) {
//     //    const char *cities[] = {"Dresden", "Berlin"};
//     //    int num_cities = 2;
//     //    const char *date_start = "2025-07-01";
//     //    const char *date_end = "2025-07-05";

//     ListCString cities_names_c;
//     cities_names_c.length = num_cities;
//     cities_names_c.strings = (char **)malloc(num_cities * sizeof(char *));

//     for (int i = 0; i < num_cities; i++) {
//         cities_names_c.strings[i] = strdup(cities[i]);
//         if (!cities_names_c.strings[i]) {
//             fprintf(stderr, "String duplication failed\n");
//             // Cleanup
//             for (int j = 0; j < i; j++)
//                 free((void *)cities_names_c.strings[j]);
//             free(cities_names_c.strings);
//             return 1;
//         }
//     }

//     // Call the Rust function
//     ListCCity *result = get_many_cities(cities_names_c, date_start,
//     date_end);

//     print_city_list(result);

//     free_city_list(result);

//     return 0;
// }