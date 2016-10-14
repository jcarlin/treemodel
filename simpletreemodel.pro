QT += qml quick widgets sql core

CONFIG += c++11

HEADERS     = treeitem.h \
              treemodel.h \
              setup.h \
              shippingactivities.h
RESOURCES   = simpletreemodel.qrc
SOURCES     = treeitem.cpp \
              treemodel.cpp \
              main.cpp \
              setup.cpp \
              shippingactivities.cpp

