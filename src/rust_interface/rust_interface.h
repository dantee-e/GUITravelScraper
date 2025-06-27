#ifndef GUITRAVELSCRAPER_RUST_INTERFACE_H
#define GUITRAVELSCRAPER_RUST_INTERFACE_H

typedef struct {
    const char *name;
    const char *price;
    const char *url;
    const unsigned int a_n_o_hostel_club;
} Room;

typedef struct {
    const char *name;
    Room *room_options;
    const char *link;
    unsigned int number_of_rooms;
} Hostel;

typedef struct {
    const char *name;
    const char *ano_url;
    Hostel *hostels;
    unsigned int hostels_len;
} City;

typedef struct {
    City *cities;
    unsigned int len;
} ListCCity;

typedef struct {
    char **strings;
    unsigned int length;
} ListCString;

extern ListCCity *get_many_cities(ListCString cities_names_c,
                                  const char *date_start, const char *date_end);
extern void free_city_list(ListCCity *city);
extern void
free_list_c_string(ListCString *ptr); // TODO change this name in the rust lib

void print_city_list(ListCCity *cities);
#endif // GUITRAVELSCRAPER_RUST_INTERFACE_H
