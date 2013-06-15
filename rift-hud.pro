QT += core gui opengl

TARGET = rift-hud
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv

SOURCES += \
  main.cpp \
  mainwindow.cpp \
  qscenewidget.cpp \
  qcamera.cpp \
  ./cvsu/cvsu_memory.c \
  ./cvsu/cvsu_output.c \
  ./cvsu/cvsu_types.c \
  ./cvsu/cvsu_typed_pointer.c \
  ./cvsu/cvsu_pixel_image.c \
  ./cvsu/cvsu_integral.c \
  ./cvsu/cvsu_filter.c \
  ./cvsu/cvsu_edges.c \
  ./cvsu/cvsu_list.c \
  ./cvsu/cvsu_context.c \
  ./cvsu/cvsu_annotation.c \
  ./cvsu/cvsu_quad_tree.c \
  ./cvsu/cvsu_quad_forest.c \
  ./cvsu/cvsu_segmentation.c \
  ./cvsu/cvsu_parsing.c \
  ./cvsu/cvsu_temporal_forest.c \
  ./cvsu/cvsu_background_forest.c \
  ./cvsu/cvsu_opencv.c
HEADERS += \
  mainwindow.h \
  qscenewidget.h \
  qcamera.h \
  ./cvsu/cvsu_config.h \
  ./cvsu/cvsu_types.h \
  ./cvsu/cvsu_typed_pointer.h \
  ./cvsu/cvsu_macros.h \
  ./cvsu/cvsu_memory.h \
  ./cvsu/cvsu_output.h \
  ./cvsu/cvsu_pixel_image.h \
  ./cvsu/cvsu_integral.h \
  ./cvsu/cvsu_filter.h \
  ./cvsu/cvsu_edges.h \
  ./cvsu/cvsu_list.h \
  ./cvsu/cvsu_context.h \
  ./cvsu/cvsu_annotation.h \
  ./cvsu/cvsu_quad_tree.h \
  ./cvsu/cvsu_quad_forest.h \
  ./cvsu/cvsu_segmentation.h \
  ./cvsu/cvsu_parsing.h \
  ./cvsu/cvsu_temporal_forest.h \
  ./cvsu/cvsu_background_forest.h \
  ./cvsu/cvsu_opencv.h

LIBS += -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lglut
