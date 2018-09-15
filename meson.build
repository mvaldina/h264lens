project('h264lens', 'c')

glibdep = dependency('glib-2.0')
gstdep = dependency('gstreamer-1.0')
gstappdep = dependency('gstreamer-app-1.0')
gstcodecdep = dependency('gstreamer-codecparsers-1.0')

executable('h264lens', [ 'src/main.c', 'src/application.c' ], dependencies: [glibdep, gstdep, gstappdep, gstcodecdep])

