# Nom de l'exécutable
EXECUTABLE = myapp

# Compilateur et options
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g -I$(HOME)/local/include
LDFLAGS = -L$(HOME)/local/lib -lyaml-cpp

# Dossier pour les fichiers objets
OBJDIR = build

# Fichiers sources
SOURCES = \
    src/game.cpp \
    src/gridmanagement.cpp \
    src/settings.cpp \
    main.cpp

# Générez une liste d'objets à partir des sources et placez-les dans le répertoire OBJDIR
OBJECTS = $(SOURCES:.cpp=$(OBJDIR)/%.o)

# Règle par défaut : construire l'exécutable
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDFLAGS) -o $(EXECUTABLE)

# Créer le dossier build s'il n'existe pas
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Règle générique pour la compilation des .cpp en .o dans le répertoire build
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers intermédiaires et de l'exécutable
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE)

# Optionnel : installation ou autres commandes
install: $(EXECUTABLE)
	@echo "Installation pas définie."

.PHONY: all clean install
