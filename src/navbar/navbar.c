#include "src/types/string_list.h"
#include "src/utils.h"
#include <glibconfig.h>
#include <gtk/gtk.h>

GtkWidget *cities_box_maker() {
    GtkWidget *inner_box = NULL;
    GtkWidget *scrolled_window;
    StringList *cities = city_list();
    GtkWidget *check_buttons[cities->length];

    scrolled_window = gtk_scrolled_window_new();

    inner_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);

    for (int i = 0; i < cities->length; i++) {
        check_buttons[i] = gtk_check_button_new_with_label(cities->cities[i]);
        gtk_box_append(GTK_BOX(inner_box), check_buttons[i]);
    }

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window),
                                  inner_box);

    gtk_box_set_homogeneous(GTK_BOX(inner_box), TRUE);

    free_string_list(cities);

    return scrolled_window;
}

GtkWidget *navbar_box_maker(GtkWindow *win) {
    GtkWidget *grid;
    GtkWidget *city_list_box;
    GtkWidget *submit_button;

    grid = gtk_grid_new();

    city_list_box = cities_box_maker();

    submit_button = gtk_button_new_with_label("Submit");

    gtk_grid_attach(GTK_GRID(grid), city_list_box, 0, 0, 1, 8);
    gtk_grid_attach(GTK_GRID(grid), submit_button, 0, 8, 1, 1);
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