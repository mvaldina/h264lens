#include "gui.h"

#include <gtk/gtk.h>

GtkWidget* create_ui() {
  GtkWidget *main_window;  /* The uppermost window, containing all other windows */

  GtkBuilder* builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "ui/MainWindow.glade", NULL);
  main_window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
  //main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW (main_window), 640, 480);

  gtk_widget_show_all (main_window);
  return main_window;
}
