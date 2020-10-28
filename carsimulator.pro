QT += widgets
requires(qtConfig(combobox))

HEADERS       = renderarea.h \
                window.h
SOURCES       = main.cpp \
                renderarea.cpp \
                window.cpp
RESOURCES     = carsimulator.qrc
