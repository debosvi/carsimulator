QT += widgets core
requires(qtConfig(combobox))

HEADERS       = renderarea.h \
                model.h \
                window.h
SOURCES       = main.cpp \
                model.cpp \
                renderarea.cpp \
                window.cpp
RESOURCES     = carsimulator.qrc
