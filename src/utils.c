#include "application.h"
#include <gst/gst.h>
// Need to move to another part.
#include <gst/codecparsers/gsth264parser.h>

char const* gst_h264_nal_unit_type_to_chars(GstH264NalUnitType type) {
  if (type == GST_H264_NAL_UNKNOWN      ) return "UNKNOWN";
  else if (type == GST_H264_NAL_SLICE        ) return "SLICE";
  else if (type == GST_H264_NAL_SLICE_DPA    ) return "SLICE_DPA";
  else if (type == GST_H264_NAL_SLICE_DPB    ) return "SLICE_DPB";
  else if (type == GST_H264_NAL_SLICE_DPC    ) return "SLICE_DPC";
  else if (type == GST_H264_NAL_SLICE_IDR    ) return "SLICE_IDR";
  else if (type == GST_H264_NAL_SEI          ) return "SEI";
  else if (type == GST_H264_NAL_SPS          ) return "SPS";
  else if (type == GST_H264_NAL_PPS          ) return "PPS";
  else if (type == GST_H264_NAL_AU_DELIMITER ) return "AU_DELIMITER";
  else if (type == GST_H264_NAL_SEQ_END      ) return "SEQ_END";
  else if (type == GST_H264_NAL_STREAM_END   ) return "STREAM_END";
  else if (type == GST_H264_NAL_FILLER_DATA  ) return "FILLER_DATA";
  else if (type == GST_H264_NAL_SPS_EXT      ) return "SPS_EXT";
  else if (type == GST_H264_NAL_PREFIX_UNIT  ) return "PREFIX_UNIT";
  else if (type == GST_H264_NAL_SUBSET_SPS   ) return "SUBSET_SPS";
  else if (type == GST_H264_NAL_DEPTH_SPS    ) return "DEPTH_SPS";
  else if (type == GST_H264_NAL_SLICE_AUX    ) return "SLICE_AUX";
  else if (type == GST_H264_NAL_SLICE_EXT    ) return "SLICE_EXT";
  else if (type == GST_H264_NAL_SLICE_DEPTH  ) return "SLICE_DEPTH";
  g_assert_not_reached();
  return "??";
}
