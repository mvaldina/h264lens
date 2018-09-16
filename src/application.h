#ifndef H264LENS_APPLICATION_H__
#define H264LENS_APPLICATION_H__

#include <glib.h>
#include <gst/gst.h>
#include <gtk/gtk.h>
// Need to move to another part.
#include <gst/codecparsers/gsth264parser.h>

typedef struct _application {
  // Gtk main window
  GtkWidget* main_window;
  // Main loop.
  GMainLoop* loop;
  // Bus watcher.
  GstBus* bus;
  // Pipeline.
  GstPipeline* pipeline;
  // appsink.
  GstElement* appsink;
  // Parser
  GstH264NalParser* parser;
  // list store
  GtkListStore* list_store;
} application_t;

/**
 * @brief Create the application object.
 * 
 * @return application_t* 
 */
application_t* h264lens_application_create();

/**
 * @brief Destroy the application object.
 * 
 * @param app 
 */
void h264lens_application_destroy(application_t* app);

#endif