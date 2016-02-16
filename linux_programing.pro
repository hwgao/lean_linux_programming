TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lpthread

QMAKE_CFLAGS += -fsanitize=thread
QMAKE_CFLAGS += -g
QMAKE_LFLAGS += -fsanitize=thread

# SOURCES += signal.c
# SOURCES += ipc.c
# SOURCES += socket_client.c
# SOURCES += server_name.c
SOURCES += socket_server.c
