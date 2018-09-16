// Base headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Glib GST headers
#include <glib.h>

#include "application.h"
#include "utils.h"
#include "gui.h"
#include "stream_handler.h"

int main(int argc, char **argv) {
  // First argument is the path
  if (argc != 2) {
    return EXIT_FAILURE;
  }

  gtk_init(&argc, &argv);
  // Initialize GStreamer.
  gst_init(&argc, &argv);
  
  application_t* app = h264lens_application_create();
  app->main_window = create_ui();
  create_gst_pipeline_pcap(app, argv[1], 127, 6002);
  
  gst_element_set_state (app->pipeline, GST_STATE_PLAYING);
  g_print("Running ...\n");
  gtk_main();
  g_print("Not running anymore.\n");
  //msg = gst_bus_timed_pop_filtered (app->bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
  
  /* move in the application handling.
  gst_object_unref (app->bus);
  gst_element_set_state (app->pipeline, GST_STATE_NULL);
  //
  gst_object_unref(app->appsink);
  */
  h264lens_application_destroy(app);
  return EXIT_SUCCESS;
}

