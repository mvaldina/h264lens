project('h264lens', 'c', default_options : ['c_std=c11'], license: 'MIT', version: '0.0.0')

# Disable warning for GstH264Parser (unstable API).
add_global_arguments('-DGST_USE_UNSTABLE_API', language : 'c')

glibdep = dependency('glib-2.0')
gstdep = dependency('gstreamer-1.0')
gstappdep = dependency('gstreamer-app-1.0')
gstcodecdep = dependency('gstreamer-codecparsers-1.0')

executable('h264lens', [ 'src/main.c', 'src/application.c', 'src/utils.c' ], dependencies: [glibdep, gstdep, gstappdep, gstcodecdep])

