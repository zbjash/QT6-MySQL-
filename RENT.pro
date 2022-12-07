                           QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwindow.cpp \
    edit.cpp \
    findback.cpp \
    main.cpp \
    login.cpp \
    mrh_addrecord.cpp \
    mrh_cancelrent.cpp \
    mrh_rent.cpp \
    myrentinghouse.cpp \
    tenant_upassword.cpp \
    tenant_update.cpp \
    tenantwindow.cpp

HEADERS += \
    adminwindow.h \
    edit.h \
    findback.h \
    login.h \
    mrh_addrecord.h \
    mrh_cancelrent.h \
    mrh_rent.h \
    myrentinghouse.h \
    share.h \
    tenant_upassword.h \
    tenant_update.h \
    tenantwindow.h

FORMS += \
    adminwindow.ui \
    edit.ui \
    findback.ui \
    login.ui \
    mrh_addrecord.ui \
    mrh_cancelrent.ui \
    mrh_rent.ui \
    myrentinghouse.ui \
    tenant_upassword.ui \
    tenant_update.ui \
    tenantwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
