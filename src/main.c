// Base headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Glib GST headers
#include <glib.h>
#include <gst/gst.h>
#include <gst/app/gstappsink.h>

#include "application.h"



// Constants
// This is the caps for H.264 as application inputs
gchar const* h264avc_caps = "video/x-h264,stream-format=byte-stream,alignment=nal";
//gchar const* h264avc_caps = "video/x-h264,stream-format=avc,alignment=au";

int counter = 0;
static GstFlowReturn on_new_sample_from_sink (GstElement* elt, application_t* data) {
  GstBuffer* buffer;
  GstSample* sample;
  GstFlowReturn ret = GST_FLOW_OK;

  sample = gst_app_sink_pull_sample (GST_APP_SINK (elt));
  buffer = gst_sample_get_buffer (sample);
  // Parse.
  GstMapInfo info;
  gst_buffer_map(buffer, &info, GST_MAP_READ);
  GstH264NalUnit nalu;
  GstH264ParserResult result = gst_h264_parser_identify_nalu(data->parser, info.data, 0, info.size, &nalu);
  
  //GstH264ParserResult result = gst_h264_parser_identify_nalu_avc(data->parser, info.data, 0, info.size,info.size, &nalu);
  g_print("H.264 parse \t%d - Get a new sample (%d, size %lu bytes, type  %hu)\n", result, counter++, gst_buffer_get_size(buffer), nalu.type);

  gst_buffer_unmap(buffer, &info);
  // 7 10 p
  //app_buffer = gst_buffer_copy (buffer);
  gst_sample_unref (sample);

  /* we don't need the appsink sample anymore */
  /* get source an push new buffer */

  //ret = gst_app_src_push_buffer (GST_APP_SRC (source), app_buffer);
  //source = gst_bin_get_by_name (GST_BIN (data->sink), "testsource");
  //gst_object_unref (source);
  return ret;
}


int main(int argc, char **argv) {
  GstMessage* msg = NULL;

  g_print("H.264lens 8.9\n");

  // First argument is the path
  if (argc != 2) {
    return EXIT_FAILURE;
  }
  // Initialize GStreamer.
  gst_init(&argc, &argv);
  
  application_t* app = h264lens_application_create();
  
  // Build the pipeline
#if 0 // Display
  gchar* cmd_line = g_strdup_printf("filesrc location=\"%s\" ! pcapparse dst-port=6002 !  application/x-rtp, payload=127, media=video, clock-rate=90000, encoding-name=H264 ! rtph264depay ! avdec_h264 ! videoconvert ! glimagesink", argv[1]);
#else
  gchar* cmd_line = g_strdup_printf("filesrc location=\"%s\" ! pcapparse dst-port=6002 !  application/x-rtp, payload=127, media=video, clock-rate=90000, encoding-name=H264 ! rtph264depay ! appsink caps=\"%s\" name=mysink", argv[1], h264avc_caps);
#endif
  app->pipeline = gst_parse_launch (cmd_line, NULL);
  g_free(cmd_line);

  app->appsink = gst_bin_get_by_name(GST_BIN(app->pipeline), "mysink");
  g_object_set(G_OBJECT(app->appsink), "emit-signals", TRUE, "sync", FALSE, NULL);
  g_signal_connect(app->appsink, "new-sample", G_CALLBACK (on_new_sample_from_sink), &app);

  // Start playing  
  gst_element_set_state (app->pipeline, GST_STATE_PLAYING);
  // Wait until error or EOS
  app->bus = gst_element_get_bus (app->pipeline);
  msg = gst_bus_timed_pop_filtered (app->bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  // Free resources
  if (msg != NULL) {
    gst_message_unref (msg);
  }
  gst_object_unref (app->bus);
  gst_element_set_state (app->pipeline, GST_STATE_NULL);
  gst_object_unref(app->pipeline);
  //
  gst_object_unref(app->appsink);

  h264lens_application_destroy(app);
  return EXIT_SUCCESS;
}

