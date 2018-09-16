#ifndef H264LENS_STREAM_HANDLER_H__
#define H264LENS_STREAM_HANDLER_H__

#include <gst/gst.h>
// Forward declarations.
typedef struct application_t;

/**
 * @brief Create a gst pipeline for a PCAP file
 * 
 * @param location 
 * @param pt 
 * @param port 
 * @return GstPipeline* 
 */
GstPipeline* create_gst_pipeline_pcap(application_t* app, char const* location, int pt, int port);

#endif