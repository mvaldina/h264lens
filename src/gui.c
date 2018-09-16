#include "gui.h"
#include "application.h"

#include <gtk/gtk.h>

GtkWidget* create_ui(application_t* app) {
  GtkWidget *main_window;  /* The uppermost window, containing all other windows */

  GtkBuilder* builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "ui/MainWindow.glade", NULL);
  main_window = GTK_WIDGET(gtk_builder_get_object(builder, "MainWindow"));
  GtkListStore* list_store = gtk_builder_get_object(builder, "StreamContent");
  // Release builder resources.
  app->list_store = list_store;
  //GtkTreeIter iter;
  //gtk_list_store_append(list_store, &iter);
  //      gtk_list_store_set(list_store, &iter,
  //                        1, "SPS", 33, -1);
  //main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW (main_window), 640, 480);

  gtk_widget_show(main_window);
  g_object_unref(builder);

  return main_window;
}
