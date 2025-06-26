#include "utils.h"
#include <glib-object.h>
#include <gtk/gtk.h>
#include <string.h>

void widget_set_size_request_percent_window(GtkWindow *win, GtkWidget *widget,
                                            int width_percent,
                                            int height_percent) {
    int width_win;
    int height_win;

    gtk_window_get_default_size(win, &width_win, &height_win);

    g_print("width_win: %d, height win: %d\n", width_win, height_win);
    int width_new = width_win * width_percent / 100;
    int height_new = height_win * height_percent / 100;

    g_print("width_new: %d, height new: %d\n", width_new, height_new);

    gtk_widget_set_size_request(widget, (gint)width_new, (gint)height_new);

    gtk_widget_get_size_request(widget, &width_win, &height_win);
}

void free_widget_list(WidgetList *list) {
    for (int i = 0; i < list->length; i++) {
        g_object_unref(list->widgets[i]);
    }
    free(list->widgets);
    free(list);
    list = NULL;
}

WidgetList *widget_list_new() {
    WidgetList *list;
    list = malloc(sizeof(WidgetList));
    list->length = 0;
    list->widgets = NULL;
    return list;
}

void push_to_widget_list(WidgetList *list, GtkWidget *widget) {
    list->widgets[list->length++] = widget;
}