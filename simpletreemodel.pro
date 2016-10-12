QT += widgets sql qml quick

HEADERS     = treeitem.h \
              treemodel.h \
              setup.h
RESOURCES   = simpletreemodel.qrc
SOURCES     = treeitem.cpp \
              treemodel.cpp \
              main.cpp \
              setup.cpp

# install
//target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/simpletreemodel
//INSTALLS += target
