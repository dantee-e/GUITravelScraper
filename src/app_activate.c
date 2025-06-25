#include <gdk/gdk.h>

#include "app_activate.h"
#include "navbar/navbar.h"
#include "src/types/string_list.h"
#include "utils.h"

typedef struct {
    GtkWidget *display;
    GtkWidget *navbar;
    GtkWidget *results;
} Display;

void display_sizes(GtkWidget *win, gpointer display_box) {
    GtkWindow *winwin = GTK_WINDOW(win);
    Display *display = display_box;
    widget_set_size_request_percent_window(winwin, display->navbar, 20, 100);
}

void scaling(GtkWidget *win, gpointer display_box) {
    GdkSurface *surface;
    GdkMonitor *monitor;
    GdkDisplay *display;

    GdkRectangle geometry_actual, *geometry = &geometry_actual;
    int win_width, win_heigth;
    // double scale_factor;

    display = gdk_display_get_default();

    surface = gtk_native_get_surface(GTK_NATIVE(GTK_WINDOW(win)));
    monitor = gdk_display_get_monitor_at_surface(display, surface);
    if (!monitor || !GDK_IS_MONITOR(monitor)) {
        g_print("Fudeu\n");
    }

    gdk_monitor_get_geometry(monitor, geometry);

    // scale_factor = gdk_surface_get_scale(surface);
    win_width = geometry->width * WINDOW_WIDTH_PERCENT / 100;
    win_heigth = geometry->height * WINDOW_HEIGHT_PERCENT / 100;

    gtk_window_set_default_size(GTK_WINDOW(win), win_width, win_heigth);

    display_sizes(win, display_box);
}

void app_activate(GtkApplication *app) {
    GtkWidget *win;
    GtkWindow *win_win;
    Display display;

    win = gtk_application_window_new(app);
    win_win = GTK_WINDOW(win);

    // gtk_window_maximize(win_win);
    //      OR
    // Calculate scale

    display.display = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    display.navbar = navbar_box_maker(win_win);
    display.results = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    g_signal_connect(GTK_WIDGET(win), "show", G_CALLBACK(scaling), &display);

    gtk_box_append(GTK_BOX(display.display), GTK_WIDGET(display.navbar));
    gtk_box_append(GTK_BOX(display.display), GTK_WIDGET(display.results));

    gtk_box_set_homogeneous(GTK_BOX(display.display), FALSE);

    gtk_window_set_child(win_win, GTK_WIDGET(display.display));

    gtk_window_present(win_win);
}
