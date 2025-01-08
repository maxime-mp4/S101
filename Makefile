# Nom de l'exécutable
EXECUTABLE = jeu

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -I$(HOME)/local/include
LDFLAGS = -L$(HOME)/local/lib -lyaml-cpp

# Dossier pour les fichiers objets
OBJDIR = build

# Fichiers sources
SOURCES = \
    src/game.cpp \
    src/grid_management.cpp \
    src/settings.cpp \
    src/player_management.cpp \
    src/terminal_management.cpp \
    src/menu.cpp \
    main.cpp

# Générez une liste d'objets à partir des sources et placez-les dans le répertoire OBJDIR
OBJECTS = $(addprefix $(OBJDIR)/, $(notdir $(SOURCES:.cpp=.o)))

# Règle par défaut : construire l'exécutable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

# Créer le dossier build s'il n'existe pas
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Règle générique pour la compilation des .cpp en .o dans le répertoire build
$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Règle spécifique pour compiler main.cpp dans build/
$(OBJDIR)/main.o: main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers intermédiaires et de l'exécutable
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

# Optionnel : installation ou autres commandes
install: $(EXECUTABLE)
	@echo "Installation pas définie."

.PHONY: all clean install
