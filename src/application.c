#include "application.h"
#include <gst/gst.h>
// Need to move to another part.
#include <gst/codecparsers/gsth264parser.h>

application_t* h264lens_application_create() {
  application_t* app = g_malloc0(sizeof(application_t));
  app->parser = gst_h264_nal_parser_new();
  return app;
}

void h264lens_application_destroy(application_t* app) {
  g_assert_nonnull(app);
  gst_h264_nal_parser_free(app->parser);
  g_free(app);
}
