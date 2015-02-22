#!/usr/bin/python3
# -*- coding: utf-8 -*-
from os import listdir
from sys import argv, exit

argv = argv[1:]

if '--version' in argv:
    print('makegen.py : version 1.0')
    exit(0)


# Liste des fichiers finissant en .cpp, à compiler
compilable_files = set([x for x in listdir() if x[len(x)-4:] == '.cpp'])

#
if 'cppcms' in argv:
    compilable_files = compilable_files.union(set([x[:len(x)-5] + '.cpp' for x in listdir() if x[len(x)-5:] == '.html']))

# Ouverture du fichier Makefile
makefile = open('Makefile', 'w')

# Ecrtiure des sources
makefile.write('SOURCES =')

for f in compilable_files:
    makefile.write(' ')
    makefile.write(str(f))

makefile.write('\n\n')

# Ecriture des autres variables
makefile.write('OBJECTS = $(SOURCES:.cpp=.o)\n')
makefile.write('TARGET = main\n')
makefile.write('LIBS = ')

if 'sfml' in argv:
    makefile.write('-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio ')

if 'cppcms' in argv:
    makefile.write('-lcppcms -lbooster')

if 'ogre' in argv:
    makefile.write('-I/usr/include/OGRE -lboost_system ')

if 'sdl' in argv:
    makefile.write('$(shell sdl-config --libs) -lSDL_image ')

if 'opengl' in argv:
    makefile.write('-lGL -lGLU -lglut ')

if 'opencv' in argv:
    makefile.write('$(shell pkg-config opencv --libs)')

makefile.write('\n')
makefile.write('CXX = g++')
makefile.write('\n\n')

# Ecriture de la compilation de template en cppcms
if 'cppcms' in argv:
    makefile.write('%.cpp: %.html\n')
    makefile.write('\tcppcms_tmpl_cc $< -o $@\n\n')

# Ecriture de la règle de compilation des .cpp
makefile.write('%.o: %.cpp\n')
makefile.write('\t$(CXX) ')

if 'openmp' in argv or 'omp' in argv:
    makefile.write('-fopenmp ')

makefile.write('-std=c++0x -o $@ -c $< -Wall ')

if 'opencv' in argv:
    makefile.write('`pkg-config opencv --cflags` ')

makefile.write('\n\n')

# Ecriture de la règle d'édition des liens
makefile.write('all: $(OBJECTS)\n')
makefile.write('\t$(CXX) ')

if 'openmp' in argv or 'omp' in argv:
    makefile.write('-fopenmp ')

makefile.write('-std=c++0x -o $(TARGET) $(OBJECTS) $(LIBS) -Wall\n\n')

# Ecriture de la règle d'exécution avec x
makefile.write('x: all\n')
makefile.write('\t./$(TARGET)\n\n')

# Ecriture de la règle de nettoyage
makefile.write('clean:\n')
makefile.write('\trm -rf $(OBJECTS)\n\n')

# Ecriture de la règle de nettoyage total
makefile.write('superclean: clean\n')
makefile.write('\trm -rf $(TARGET)\n')

# Fermeture du fichier
makefile.close()
