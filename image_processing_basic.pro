#-------------------------------------------------
#
# Project created by QtCreator 2016-10-20T22:05:36
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = image_processing_basic
TEMPLATE = app

INCLUDEPATH += include
DEFINES += NODE_EDITOR_SHARED

SOURCES += main.cpp\
        mainwindow.cpp \
    node/Connection.cpp \
    node/ConnectionBlurEffect.cpp \
    node/ConnectionGeometry.cpp \
    node/ConnectionGraphicsObject.cpp \
    node/ConnectionPainter.cpp \
    node/ConnectionState.cpp \
    node/DataModelRegistry.cpp \
    node/FlowItemInterface.cpp \
    node/FlowScene.cpp \
    node/FlowView.cpp \
    node/Node.cpp \
    node/NodeConnectionInteraction.cpp \
    node/NodeDataModel.cpp \
    node/NodeGeometry.cpp \
    node/NodeGraphicsObject.cpp \
    node/NodePainter.cpp \
    node/NodeState.cpp \
    node/Properties.cpp \
    model/ImageLoaderModel.cpp \
    model/ImageShowModel.cpp \
    model/monofilter.cpp \
    model/thresholdfilter.cpp \
    model/histogram.cpp \
    model/spatialfilter.cpp \
    model/sobelfilter.cpp \
    model/scaler.cpp \
    model/erosionfilter.cpp \
    model/delatefilter.cpp \
    model/segmentation.cpp \
    model/boundryextraction.cpp

HEADERS  += mainwindow.h \
    node/Compiler.hpp \
    node/Connection.hpp \
    node/ConnectionBlurEffect.hpp \
    node/ConnectionGeometry.hpp \
    node/ConnectionGraphicsObject.hpp \
    node/ConnectionPainter.hpp \
    node/ConnectionState.hpp \
    node/DataModelRegistry.hpp \
    node/Export.hpp \
    node/FlowItemInterface.hpp \
    node/FlowScene.hpp \
    node/FlowView.hpp \
    node/Node.hpp \
    node/NodeConnectionInteraction.hpp \
    node/NodeData.hpp \
    node/NodeDataModel.hpp \
    node/NodeGeometry.hpp \
    node/NodeGraphicsObject.hpp \
    node/NodePainter.hpp \
    node/NodeState.hpp \
    node/OperatingSystem.hpp \
    node/PortType.hpp \
    node/Properties.hpp \
    node/QStringStdHash.hpp \
    node/Serializable.hpp \
    node/UniquePtr.hpp \
    include/nodes/DataModelRegistry \
    include/nodes/FlowScene \
    include/nodes/FlowView \
    include/nodes/NodeData \
    include/nodes/NodeDataModel \
    model/ImageLoaderModel.hpp \
    model/ImageShowModel.hpp \
    model/PixmapData.hpp \
    model/monofilter.h \
    model/thresholdfilter.h \
    model/histogram.h \
    model/spatialfilter.h \
    model/sobelfilter.h \
    model/scaler.h \
    model/erosionfilter.h \
    model/delatefilter.h \
    model/segmentation.h \
    model/boundryextraction.h

FORMS    += mainwindow.ui
