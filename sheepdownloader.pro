QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG+= console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Downloader.cpp \
    downloadinfdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    setting.cpp \
    settingwindow.cpp

HEADERS += \
    Downloader.h \
    constant.h \
    downloadinfdialog.h \
    mainwindow.h \
    setting.h \
    settingwindow.h

FORMS += \
    downloadinfdialog.ui \
    mainwindow.ui \
    settingwindow.ui

TRANSLATIONS += \
    sheepdownloader_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(debug,debug|release){
DESTDIR = ./../debug_bin
LIBS += -L./../debug_bin
}
CONFIG(release,debug|release){
DESTDIR = ./../release_bin
LIBS += -L./../release_bin
}
