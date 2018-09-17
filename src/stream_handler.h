#ifndef H264LENS_STREAM_HANDLER_H__
#define H264LENS_STREAM_HANDLER_H__

// Forward declarations.
struct application_t;
struct GstElement;
/**
 * @brief Create a gst pipeline for a PCAP file
 * 
 * @param location 
 * @param pt 
 * @param port 
 * @return GstPipeline* 
 */
GstElement* create_gst_pipeline_pcap(application_t* app, char const* location, int pt, int port);

#endif