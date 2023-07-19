
CONFIG += c++11

INCLUDEPATH += \
    $$PWD/include \

HEADERS += \
    $$PWD/src/collectionstack.h \
    $$PWD/src/contrib/graphbuilderadapter.h \
    $$PWD/src/directives.h \
    $$PWD/src/emitterstate.h \
    $$PWD/src/emitterutils.h \
    $$PWD/src/exp.h \
    $$PWD/src/indentation.h \
    $$PWD/src/nodebuilder.h \
    $$PWD/src/nodeevents.h \
    $$PWD/src/ptr_vector.h \
    $$PWD/src/regex_yaml.h \
    $$PWD/src/regeximpl.h \
    $$PWD/src/scanner.h \
    $$PWD/src/scanscalar.h \
    $$PWD/src/scantag.h \
    $$PWD/src/setting.h \
    $$PWD/src/singledocparser.h \
    $$PWD/src/stream.h \
    $$PWD/src/streamcharsource.h \
    $$PWD/src/stringsource.h \
    $$PWD/src/tag.h \
    $$PWD/src/token.h

SOURCES += \
    $$PWD/src/binary.cpp \
    $$PWD/src/contrib/graphbuilder.cpp \
    $$PWD/src/contrib/graphbuilderadapter.cpp \
    $$PWD/src/convert.cpp \
    $$PWD/src/depthguard.cpp \
    $$PWD/src/directives.cpp \
    $$PWD/src/emit.cpp \
    $$PWD/src/emitfromevents.cpp \
    $$PWD/src/emitter.cpp \
    $$PWD/src/emitterstate.cpp \
    $$PWD/src/emitterutils.cpp \
    $$PWD/src/exceptions.cpp \
    $$PWD/src/exp.cpp \
    $$PWD/src/memory.cpp \
    $$PWD/src/node.cpp \
    $$PWD/src/node_data.cpp \
    $$PWD/src/nodebuilder.cpp \
    $$PWD/src/nodeevents.cpp \
    $$PWD/src/null.cpp \
    $$PWD/src/ostream_wrapper.cpp \
    $$PWD/src/parse.cpp \
    $$PWD/src/parser.cpp \
    $$PWD/src/regex_yaml.cpp \
    $$PWD/src/scanner.cpp \
    $$PWD/src/scanscalar.cpp \
    $$PWD/src/scantag.cpp \
    $$PWD/src/scantoken.cpp \
    $$PWD/src/simplekey.cpp \
    $$PWD/src/singledocparser.cpp \
    $$PWD/src/stream.cpp \
    $$PWD/src/tag.cpp







