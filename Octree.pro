QT += core gui
QT += widgets
QT += 3dcore 3drender 3dinput 3dextras

SOURCES += \
    src/main.cpp \
    src/guiQt3D.cpp \
    src/faces.cpp \
    src/vertex.cpp \
    src/objfile.cpp \
    src/octree.cpp \
    src/bounds.cpp

HEADERS += \
    include/guiQt3D.hpp \
    include/vertex.hpp \
    include/objfile.hpp \
    include/faces.hpp \
    include/octree.hpp \
    include/bounds.hpp
    