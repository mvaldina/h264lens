#include "application.h"
#include "utils.h"

#include <gst/gst.h>
#include <gst/codecparsers/gsth264parser.h>
#include <gst/app/gstappsink.h>

#include <gtk/gtk.h>
// Constants
// This is the caps for H.264 as application inputs
// NAL byte-stream
gchar const* h264avc_caps = "video/x-h264,stream-format=byte-stream,alignment=nal";
// AU AVC stream
//gchar const* h264avc_caps = "video/x-h264,stream-format=avc,alignment=au";

int counter = 0;
static GstFlowReturn on_new_sample_from_sink(GstElement* elt, application_t* data) {
  GstBuffer* buffer;
  GstSample* sample;
  GstFlowReturn ret = GST_FLOW_OK;

  sample = gst_app_sink_pull_sample (GST_APP_SINK (elt));
  buffer = gst_sample_get_buffer (sample);
  // Parse.
  GstMapInfo info;
  gst_buffer_map(buffer, &info, GST_MAP_READ);
  
  int offset = 0;
  GstH264ParserResult result = GST_H264_PARSER_OK;
  
  GtkTreeIter iter;
  do { 
    GstH264NalUnit nalu;
    result = gst_h264_parser_identify_nalu(data->parser, info.data, offset, info.size, &nalu);
    offset = nalu.offset + nalu.size;
    
    //if (counter <= 10) {
      gtk_list_store_append(data->list_store, &iter);
      gtk_list_store_set(data->list_store, &iter, 0, (gint64)counter, 1, gst_h264_nal_unit_type_to_chars(nalu.type), 2, (int)nalu.size, -1);
    //}
    /*
    g_print("H.264 parse \t%d - Get a new sample (%d, size %u bytes, type %s)\n", result, counter++, nalu.size,
            gst_h264_nal_unit_type_to_chars(nalu.type));
*/
    counter++;
    if (nalu.type == GST_H264_NAL_SPS) {
      GstH264SPS sps;
      gst_h264_parse_sps(&nalu, &sps, TRUE);
      g_print("profile_idc %hhu\n", sps.profile_idc);
    }
  } while (result == GST_H264_PARSER_OK);

  gst_buffer_unmap(buffer, &info);
  gst_sample_unref (sample);
  return ret;
}

GstPipeline* create_gst_pipeline_pcap(application_t* app, char const* location, int pt, int port) {
  GstPipeline* pipeline = NULL;
  gchar* cmd_line = g_strdup_printf("filesrc location=\"%s\" ! pcapparse dst-port=%d !  application/x-rtp, payload=%d, media=video, clock-rate=90000, encoding-name=H264 ! rtph264depay ! appsink caps=\"%s\" name=mysink", location, port, pt, h264avc_caps);
  pipeline = gst_parse_launch(cmd_line, NULL);
  g_free(cmd_line);

  if (pipeline != NULL) {
    app->appsink = gst_bin_get_by_name(GST_BIN(pipeline), "mysink");
    g_object_set(G_OBJECT(app->appsink), "emit-signals", TRUE, "sync", FALSE, NULL);
    g_signal_connect(app->appsink, "new-sample", G_CALLBACK (on_new_sample_from_sink), app);
    app->pipeline = pipeline;
    // Wait until error or EOS
    app->bus = gst_element_get_bus (app->pipeline);
  
  }
  
  return pipeline;
}
