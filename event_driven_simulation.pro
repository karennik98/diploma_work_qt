QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        db/gate.cpp \
        db/net.cpp \
        db/netlist.cpp \
        logic_operations/logicoperations.cpp \
        main.cpp \
        netlist_builder/netlistbuilder.cpp \
        netlist_builder/verilogkeywords.cpp \
        simulation/event.cpp \
        simulation/simulation.cpp \
        simulation/timewheel.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    db/gate.h \
    db/net.h \
    db/netlist.h \
    logic_operations/logicoperations.h \
    netlist_builder/netlistbuilder.h \
    netlist_builder/verilogkeywords.h \
    simulation/event.h \
    simulation/simulation.h \
    simulation/timewheel.h

RESOURCES += \
    verilog/verilog.qrc
