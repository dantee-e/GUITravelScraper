#include <gtk/gtk.h>
void widget_set_size_request_percent_window(GtkWindow *win, GtkWidget *widget,
                                            int width_percent,
                                            int height_percent);
typedef struct {
    GtkWidget **widgets;
    int length;
    int capacity;
} WidgetList;
WidgetList *widget_list_new();
void push_to_widget_list(WidgetList *list, GtkWidget *widget);