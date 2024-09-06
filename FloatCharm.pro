QT       += core gui
QT       += svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    additemcommand.cpp \
    charwidget.cpp \
    class_Charts/chart_base.cpp \
    class_Charts/chart_capsule.cpp \
    class_Charts/chart_circle.cpp \
    class_Charts/chart_diamond.cpp \
    class_Charts/chart_ellipse.cpp \
    class_Charts/chart_image.cpp \
    class_Charts/chart_label.cpp \
    class_Charts/chart_line.cpp \
    class_Charts/chart_parallelogram.cpp \
    class_Charts/chart_plaintext.cpp \
    class_Charts/chart_rect.cpp \
    class_Charts/chart_roundrect.cpp \
    class_Charts/chart_subflort.cpp \
    class_Charts/chart_trapezoid.cpp \
    class_Charts/chart_triangle.cpp \
    dialog.cpp \
    flowchart.cpp \
    main.cpp \
    floatchatwindow.cpp \
    mainwindow.cpp \
    moveitemcommand.cpp \
    selection.cpp

HEADERS += \
    additemcommand.h \
    charwidget.h \
    class_Charts/chart_base.h \
    class_Charts/chart_capsule.h \
    class_Charts/chart_circle.h \
    class_Charts/chart_diamond.h \
    class_Charts/chart_ellipse.h \
    class_Charts/chart_image.h \
    class_Charts/chart_label.h \
    class_Charts/chart_line.h \
    class_Charts/chart_parallelogram.h \
    class_Charts/chart_plaintext.h \
    class_Charts/chart_rect.h \
    class_Charts/chart_roundrect.h \
    class_Charts/chart_subflort.h \
    class_Charts/chart_trapezoid.h \
    class_Charts/chart_triangle.h \
    comdef.h \
    dialog.h \
    floatchatwindow.h \
    flowchart.h \
    mainwindow.h \
    moveitemcommand.h \
    selection.h

FORMS += \
    charwidget.ui \
    dialog.ui \
    floatchatwindow.ui \
    mainwindow.ui \
    selection.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
