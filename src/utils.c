#include <gtk/gtk.h>

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
