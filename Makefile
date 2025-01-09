# Nom de l'exécutable
EXECUTABLE = jeu

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -I$(HOME)/local/include
LDFLAGS = -L$(HOME)/local/lib -lyaml-cpp

OBJDIR = build

SOURCES = \
    src/game.cpp \
    src/grid_management.cpp \
    src/settings.cpp \
    src/player_management.cpp \
    src/terminal_management.cpp \
    src/menu.cpp \
    main.cpp

OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

install: $(EXECUTABLE)
	@echo "Installation pas définie."

.PHONY: all clean install

## SOURCES
# pour la ligne OBJECTS, stackoverflow
# JUVEN Alexis pour nous avoir fourni le fichier
# pour l'inclusion de yaml-cpp, stackoverflow et +- des recherches web
##