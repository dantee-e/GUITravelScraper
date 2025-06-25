#include "src/types/string_list.h"
#include "src/utils.h"
#include <gtk/gtk.h>

GtkWidget *cities_box_maker() {
    GtkWidget *box = NULL;
    GtkWidget *scrolled_window;
    StringList *cities = city_list();
    GtkWidget *check_buttons[cities->length];

    scrolled_window = gtk_scrolled_window_new();
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);

    for (int i = 0; i < cities->length; i++) {
        check_buttons[i] = gtk_check_button_new_with_label(cities->cities[i]);
        gtk_widget_set_size_request(check_buttons[i], 100, 50);
        gtk_box_append(GTK_BOX(box), check_buttons[i]);
    }

    free_string_list(cities);

    gtk_widget_set_size_request(box, 10000, 10000);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), box);

    return scrolled_window;
}

GtkWidget *dropdown_maker() {
    GtkBuilder *builder;
    GError *error = NULL;
    GtkWidget *dropdown;

    builder = gtk_builder_new_from_file("builders/dropdown.xml");
    if (!builder) {
        g_printerr("Error loading dropdown.xml: %s\n",
                   error ? error->message : "Unknown error");
        if (error)
            g_error_free(error);
        return NULL;
    }

    dropdown = GTK_WIDGET(gtk_builder_get_object(builder, "dropdown"));
    if (!dropdown) {
        g_printerr("Dropdown is null: %s\n",
                   error ? error->message : "Unknown error");
        if (error)
            g_error_free(error);
        return NULL;
    }

    GtkExpression *exp =
        gtk_property_expression_new(GTK_TYPE_STRING_OBJECT, NULL, "string");

    gtk_drop_down_set_expression(GTK_DROP_DOWN(dropdown), exp);

    gtk_drop_down_set_enable_search(GTK_DROP_DOWN(dropdown), TRUE);

    return dropdown;
}

GtkWidget *navbar_box_maker(GtkWindow *win) {
    GtkWidget *navbar;
    GtkWidget *city_list_box;

    navbar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_set_homogeneous(GTK_BOX(navbar), TRUE);

    city_list_box = cities_box_maker();

    gtk_box_append(GTK_BOX(navbar), city_list_box);

    return navbar;
}