#include <iostream>
#include <fstream>
#include <string>

class FileHandler {
    std::ifstream file;
    std::string content;
public:
    FileHandler(const std::string& filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Impossible d'ouvrir le fichier");
        }
    }
    ~FileHandler() {
        if (file.is_open()) {
            file.close(); // Fermeture automatique
        }
    }
    std::string read() {
        std::getline(file, content);
        return content;
    }
};