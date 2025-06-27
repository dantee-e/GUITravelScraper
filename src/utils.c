#include "utils.h"
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

void widget_set_size_request_percent_window(GtkWindow *win, GtkWidget *widget,
                                            int width_percent,
                                            int height_percent) {
    int width_win;
    int height_win;

    gtk_window_get_default_size(win, &width_win, &height_win);

    int width_new = width_win * width_percent / 100;
    int height_new = height_win * height_percent / 100;

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
    list->capacity = 0;
    list->widgets = NULL;
    return list;
}

void push_to_widget_list(WidgetList *list, GtkWidget *widget) {
    if (!list)
        return;

    if (list->capacity == 0) {
        list->capacity = 4;
        list->length = 0;
        list->widgets = malloc(sizeof(GtkWidget *) * list->capacity);
        if (!list->widgets)
            return;
    }

    if (list->length >= list->capacity) {
        int new_capacity = list->capacity * 2;
        GtkWidget **new_widgets =
            realloc(list->widgets, sizeof(GtkWidget *) * new_capacity);
        if (!new_widgets)
            return; // realloc failed
        list->widgets = new_widgets;
        list->capacity = new_capacity;
    }

    list->widgets[list->length] = widget;
    list->length++;
}