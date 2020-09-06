#-------------------------------------------------
#
# Project created by QtCreator 2017-10-24T16:50:42
#
#-------------------------------------------------

QT       += core gui\
        network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Math_design
TEMPLATE = app




SOURCES += main.cpp\
        widget.cpp \
    g_SnakeView.cpp \
    g_Snakemath.cpp \
    ranks.cpp \
    option.cpp \
    gameWidget.cpp \
    g_mgview.cpp \
    g_mgmath.cpp \
    checkupdate.cpp \
    filelock.cpp \
    changece.cpp \
    ransl.cpp \
    mouseWheel.cpp \
    chinesechange.cpp \
    daypass.cpp \
    Gameabout.cpp \
    form.cpp \
    BarWidget.cpp \
    qizi.cpp \
    gvc.cpp \
    qipan.cpp \
    SusWidget.cpp \
    TimeThread.cpp \
    SystemTimeThread.cpp \
    shutdown.cpp \
    pastehtml.cpp \
    Enmin.cpp \
    YYSTask.cpp \
    CPUTest.cpp \
    CheckFail.cpp \
    ScreenShot.cpp \
    downWindow.cpp  \
    widgetUpdate.cpp

HEADERS  += widget.h \
    g_Snake.h \
    g_Snakemath.h \
    ranks.h \
    option.h \
    gameWidget.h \
    handoption.h \
    g_mgview.h \
    g_mgmath.h \
    checkupdate.h \
    filelock.h \
    changece.h \
    ransl.h \
    mouseWheel.h \
    chinesechange.h \
    daypass.h \
    Gameabout.h \
    form.h \
    BarWidget.h \
    gvc.h \
    handle.h \
    qizi.h \
    qipan.h \
    SusWidget.h \
    TimeThread.h \
    SystemTimeThread.h \
    shutdown.h \
    pastehtml.h\
    Enmin.h \
    YYSTask.h \
    CPUTest.h \
    CheckFail.h \
    ScreenShot.h \
    downWindow.h \
    widgetUpdate.h
#\
#    aip-cpp-sdk-0.7.10/speech.h \
#    aip-cpp-sdk-0.7.10/body_analysis.h \
#    aip-cpp-sdk-0.7.10/content_censor.h \
#    aip-cpp-sdk-0.7.10/easydl.h \
#    aip-cpp-sdk-0.7.10/face.h \
#    aip-cpp-sdk-0.7.10/image_classify.h \
#    aip-cpp-sdk-0.7.10/image_search.h \
#    aip-cpp-sdk-0.7.10/kg.h \
#    aip-cpp-sdk-0.7.10/nlp.h \
#    aip-cpp-sdk-0.7.10/ocr.h \
#    base/base.h \
#    base/base64.h \
#    base/http.h \
#    base/utils.h

#LIBS += libcurl/lib/libcurl.dll.a
#LIBS += -Lopenssl/OpenSSL-Win32/lib/MinGW -leay32
#INCLUDEPATH += libcurl/include
#INCLUDEPATH += openssl/OpenSSL-Win32/include


#include(json/json.pri)

#OTHER_FILES += \
#    json/json.pri
#QMAKE_CXXFLAGS+=-std=gnu++0x

RC_FILE = setup.rc

FORMS += \
    form.ui \
    sqlhandle.ui \
    login.ui \
    zcwidget.ui \
    mianban.ui \
    pastehtml.ui \
    widget.ui



