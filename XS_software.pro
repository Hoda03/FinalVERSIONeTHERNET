QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    acarstcp.cpp \
    acceuil.cpp \
    form.cpp \
    form1.cpp \
    form2.cpp \
    form3.cpp \
    histoacarsudp.cpp \
    histogramme.cpp \
    histotcpacars.cpp \
    histovdltcp.cpp \
    main.cpp \
    tcpacars.cpp \
    tcpvdl2.cpp \
    udpacars.cpp \
    udpvdl2.cpp \
    version.cpp

HEADERS += \
    acarstcp.h \
    acceuil.h \
    form.h \
    form1.h \
    form2.h \
    form3.h \
    histoacarsudp.h \
    histogramme.h \
    histotcpacars.h \
    histovdltcp.h \
    tcpacars.h \
    tcpvdl2.h \
    udpacars.h \
    udpvdl2.h \
    version.h

FORMS += \
    acarstcp.ui \
    acceuil.ui \
    form.ui \
    form1.ui \
    form2.ui \
    form3.ui \
    histoacarsudp.ui \
    histogramme.ui \
    histotcpacars.ui \
    histovdltcp.ui \
    tcpacars.ui \
    tcpvdl2.ui \
    udpacars.ui \
    udpvdl2.ui \
    version.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
