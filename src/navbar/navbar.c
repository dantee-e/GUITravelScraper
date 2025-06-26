#include "src/rust_interface/rust_interface.h"
#include "src/types/string_list.h"
#include "src/utils.h"
#include <glib-object.h>
#include <glib.h>
#include <glibconfig.h>
#include <gtk/gtk.h>
#include <gtk/gtkshortcut.h>
#include <stdlib.h>

GtkWidget *cities_box_maker(WidgetList **check_buttons) {
    GtkWidget *inner_box = NULL;
    GtkWidget *scrolled_window;
    StringList *cities = city_list();
    GtkWidget *check_buttons_new[cities->length];

    scrolled_window = gtk_scrolled_window_new();

    inner_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);

    *check_buttons = widget_list_new();

    for (int i = 0; i < cities->length; i++) {
        check_buttons_new[i] =
            gtk_check_button_new_with_label(cities->cities[i]);
        push_to_widget_list(*check_buttons, check_buttons_new[i]);
        gtk_box_append(GTK_BOX(inner_box), check_buttons_new[i]);
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),
                                  inner_box);

    gtk_box_set_homogeneous(GTK_BOX(inner_box), TRUE);

    free_string_list(cities);

    return scrolled_window;
}

static void submit_search(GtkWidget *button, gpointer data) {
    WidgetList *check_buttons = data;
    StringList *list = string_list_new();
    ListCString *c_string;

    if (!check_buttons) {
        g_print("check buttons is null");
        return;
    }
    for (int i = 0; i < check_buttons->length; i++) {
        if (!check_buttons->widgets[i]) {
            g_print("Button is null");
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
    ListCCity *cities = get_many_cities(*c_string, "30.06.2025", "02.07.2025");
    print_city_list(cities);
}

GtkWidget *navbar_box_maker(GtkWindow *win) {
    GtkWidget *grid;
    GtkWidget *city_list_box;
    GtkWidget *submit_button;
    WidgetList *check_buttons = NULL;

    grid = gtk_grid_new();

    city_list_box = cities_box_maker(&check_buttons);
    if (!check_buttons) {
        g_print("check buttons is null 1");
    }

    submit_button = gtk_button_new_with_label("Submit");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(submit_search),
                     check_buttons);

    gtk_grid_attach(GTK_GRID(grid), city_list_box, 0, 0, 1, 9);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 10, 1, 1);
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