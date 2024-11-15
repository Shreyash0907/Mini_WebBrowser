QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simplewindow
TEMPLATE = app

# Add sources to the project
SOURCES += main.cpp \
           renderHTML.cpp
           
# Add headers (if needed)
HEADERS += parser.hpp

# Define Flex & Bison command generation steps

# Flex: Generate lex.cpp from lexer.l
flex.input = lexer.l
flex_output = lexer.cpp
flex.commands = flex -o $$flex_output lexer.l
flex.output = $$flex_output
QMAKE_EXTRA_COMPILERS += flex
SOURCES += $$flex_output
# Bison: Generate parser.cpp and parser.hpp from parser.y
bison.commands = echo "Running Bison: bison -d -o $$OUT_PWD/parser.cpp $$PWD/parser.y" && bison -d -o $$OUT_PWD/parser.cpp $$PWD/parser.y
bison.input = parser.y
bison.output = parser.cpp
bison.header = parser.hpp
QMAKE_EXTRA_COMPILERS += bison
SOURCES += parser.cpp

# Make sure the generated files are part of the build process
PRE_TARGETDEPS += lexer.cpp parser.cpp parser.hpp
