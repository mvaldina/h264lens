#ifndef H264LENS_APPLICATION_H__
#define H264LENS_APPLICATION_H__

#include <glib.h>
#include <gst/gst.h>
// Need to move to another part.
#include <gst/codecparsers/gsth264parser.h>

typedef struct _application {
  // Main loop.
  GMainLoop* loop;
  // Bus watcher.
  GstBus* bus;
  // Pipeline.
  GstElement* pipeline;
  // appsink.
  GstElement* appsink;
  // Parser
  GstH264NalParser* parser;
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