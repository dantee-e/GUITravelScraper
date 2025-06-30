#include "src/rust_interface/rust_interface.h"
#include "src/types/string_list.h"
#include "src/utils.h"
#include <glib-object.h>
#include <glib.h>
#include <glibconfig.h>
#include <gtk/gtk.h>
#include <gtk/gtkshortcut.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *cities_box_maker(WidgetList **check_buttons) {
    GtkWidget *inner_box = NULL;
    GtkWidget *scrolled_window;
    StringList *cities = city_list();

    scrolled_window = gtk_scrolled_window_new();

    inner_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);

    *check_buttons = widget_list_new();

    for (int i = 0; i < cities->length; i++) {
        GtkWidget *button = gtk_check_button_new_with_label(cities->cities[i]);

        push_to_widget_list(*check_buttons, button);
        gtk_box_append(GTK_BOX(inner_box), button);
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),
                                  inner_box);

    gtk_box_set_homogeneous(GTK_BOX(inner_box), TRUE);

    free_string_list(cities);

    for (int i = 0; i < (*check_buttons)->length; i++) {
        bool active = gtk_check_button_get_active(
            (GTK_CHECK_BUTTON((*check_buttons)->widgets[i])));

        if (active) {
            const char *label = gtk_check_button_get_label(
                GTK_CHECK_BUTTON((*check_buttons)->widgets[i]));
            g_print("Active shit is %s", label);
        }
    }

    return scrolled_window;
}

typedef struct {
    ListCString *c_string;
    const char *date_start;
    const char *date_end;
    ListCCity *results;
    bool is_ready;
} GetManyCitiesArgs;

void threaded_get_many_cities(void *data) {
    GetManyCitiesArgs *args = data;

    args->results =
        get_many_cities(*args->c_string, args->date_start, args->date_end);
    args->is_ready = true;

    print_city_list(args->results);
}
typedef struct {
    WidgetList *check_buttons;
    GtkEntry *date_start;
    GtkEntry *date_end;
} SubmitSearchParams;

static void submit_search(GtkWidget *button, gpointer data) {
    SubmitSearchParams *search_params = data;

    WidgetList *check_buttons = search_params->check_buttons;
    StringList *list = string_list_new();
    ListCString *c_string;
    pthread_t get_cities_thread;

    if (!check_buttons) {
        g_print("check buttons is null");
        return;
    }
    for (int i = 0; i < check_buttons->length; i++) {
        if (!check_buttons->widgets[i]) {
            g_print("Button is null");
            continue;
        }
        if (!gtk_check_button_get_active(
                GTK_CHECK_BUTTON(check_buttons->widgets[i]))) {
            continue;
        }

        const char *label = gtk_check_button_get_label(
            GTK_CHECK_BUTTON(check_buttons->widgets[i]));
        push_to_string_list(list, label);
    }
    if (list->length == 0) {
        g_print("No city selected, ignoring");
    }

    c_string = string_list_as_list_c_string(list);

    GetManyCitiesArgs *args = malloc(sizeof(GetManyCitiesArgs));

    args->c_string = c_string;
    args->date_start =
        gtk_editable_get_text(GTK_EDITABLE(search_params->date_start));
    args->date_end =
        gtk_editable_get_text(GTK_EDITABLE(search_params->date_end));

    pthread_create(&get_cities_thread, NULL, (void *)threaded_get_many_cities,
                   (void *)args);
}

GtkWidget *navbar_box_maker(GtkWindow *win) {
    GtkWidget *grid;
    GtkWidget *city_list_box;
    GtkWidget *submit_button;
    GtkWidget *date_start, *date_end;
    WidgetList *check_buttons = NULL;

    grid = gtk_grid_new();

    city_list_box = cities_box_maker(&check_buttons);
    if (!check_buttons) {
        g_print("check buttons is null 1");
    }

    submit_button = gtk_button_new_with_label("Submit");
    date_start = gtk_entry_new();
    date_end = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(date_start), 10);
    gtk_entry_set_max_length(GTK_ENTRY(date_end), 10);
    gtk_entry_set_placeholder_text(GTK_ENTRY(date_start),
                                   "Input date in the format DD.MM.YEAR");
    gtk_entry_set_placeholder_text(GTK_ENTRY(date_end),
                                   "Input date in the format DD.MM.YEAR");

    // Creating the struct to pass to the callback and binding the signal
    SubmitSearchParams *search_params = malloc(sizeof(SubmitSearchParams));
    search_params->check_buttons = check_buttons;
    search_params->date_start = GTK_ENTRY(date_start);
    search_params->date_end = GTK_ENTRY(date_end);

    g_signal_connect(submit_button, "clicked", G_CALLBACK(submit_search),
                     search_params);

    gtk_grid_attach(GTK_GRID(grid), city_list_box, 0, 0, 1, 18);
    gtk_grid_attach(GTK_GRID(grid), date_start, 0, 19, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), date_end, 0, 20, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 21, 1, 1);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

    gtk_widget_set_vexpand(grid, TRUE);

    return grid;
}

// GtkWidget *dropdown_maker() {
//     GtkBuilder *builder;
//     GError *error = NULL;
//     GtkWidget *dropdown;
//
//     builder = gtk_builder_new_from_file("builders/dropdown.xml");
//     if (!builder) {
//         g_printerr("Error loading dropdown.xml: %s\n",
//                    error ? error->message : "Unknown error");
//         if (error)
//             g_error_free(error);
//         return NULL;
//     }
//
//     dropdown = GTK_WIDGET(gtk_builder_get_object(builder, "dropdown"));
//     if (!dropdown) {
//         g_printerr("Dropdown is null: %s\n",
//                    error ? error->message : "Unknown error");
//         if (error)
//             g_error_free(error);
//         return NULL;
//     }
//
//     GtkExpression *exp =
//         gtk_property_expression_new(GTK_TYPE_STRING_OBJECT, NULL, "string");
//
//     gtk_drop_down_set_expression(GTK_DROP_DOWN(dropdown), exp);
//
//     gtk_drop_down_set_enable_search(GTK_DROP_DOWN(dropdown), TRUE);
//
//     return dropdown;
// }