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

// Needed options for PCAP
static gboolean arg_pcap = FALSE;
static gint arg_dst_port = 0;
static gint arg_rtp_pt = 127;
static gchar* arg_pcapfile = NULL;
// Needed options for MP4.

static GOptionEntry entries[] =
{
  { "pcap", 'p', 0, G_OPTION_ARG_NONE, &arg_pcap, "Read an RTP/H.264 stream from a PCAP file", NULL },
  { "location", 'l', 0, G_OPTION_ARG_STRING, &arg_pcapfile, "PCAP file location", NULL },
  { "dst-port", 0, 0, G_OPTION_ARG_INT, &arg_dst_port, "Destination port of H.264 stream (RTP)", NULL },
  { "rtp-pt", 0, 0, G_OPTION_ARG_INT, &arg_rtp_pt, "RTP payload type", NULL },
  { NULL }
};

int main(int argc, char **argv) {
  GError* error = NULL;
  GOptionContext* context = g_option_context_new("- H.264 stream analyzer.");
  g_option_context_add_main_entries(context, entries, "h264lens");
  // Add GTK and GST options.
  g_option_context_add_group(context, gtk_get_option_group(TRUE));
  g_option_context_add_group(context, gst_init_get_option_group());
  // Parse incoming arguments.
  if (!g_option_context_parse (context, &argc, &argv, &error)) {
    return EXIT_FAILURE;
  }

  gtk_init(&argc, &argv);
  // Initialize GStreamer.
  gst_init(&argc, &argv);
  
  // Need to move inside the creation of UI and PCAP.
  application_t* app = h264lens_application_create();
  app->main_window = create_ui(app);
  if (arg_pcap) {
    create_gst_pipeline_pcap(app, arg_pcapfile, arg_rtp_pt, arg_dst_port);
  }
  else {
    g_error("No valid input file, terminating application ...");
    h264lens_application_destroy(app);
    return EXIT_FAILURE;
  }
  gst_element_set_state (app->pipeline, GST_STATE_PLAYING);
  gtk_main();
  
  h264lens_application_destroy(app);
  return EXIT_SUCCESS;
}

