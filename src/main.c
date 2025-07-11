#include "app_activate.h"
#include <gio/gio.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdio.h>

int main(int argc, char **argv) {
    GtkApplication *app;
    int stat;

    app = gtk_application_new("com.github.ToshioCP.pr1",
                              G_APPLICATION_DEFAULT_FLAGS);

    g_signal_connect(app, "activate", G_CALLBACK(app_activate), NULL);

    stat = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);
    return stat;
}