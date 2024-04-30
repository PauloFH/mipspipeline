#include <systemc.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

SC_MODULE(Dcode){
public:
    std::vector<std::string> readDocument(const std::string& filename) {
        std::vector<std::string> lines; 
        std::ifstream file(filename); 

        if (file.is_open()) {
            std::string line;
           
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
        } else {
            std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        }

        return lines; 
    }

    
    SC_CTOR(Dcode) {
        if (sc_argc() < 2) {
            std::cerr << "Uso: ./my_program <nome_do_arquivo>" << std::endl;
            return;
        }
        const char* filename = sc_argv()[1];
        std::vector<std::string> documentLines = readDocument(filename);

        std::cout << "Linhas do documento '" << filename << "':" << std::endl;
        for (const auto& line : documentLines) {
            std::cout << line << std::endl;
            
        }
    }
};