#include <iostream>
#include "game.h"

int main() {
    // Устанавливаем кодировку для Windows
    system("chcp 65001 > nul");
    
    std::cout << "=== Lab 7: Multi-threaded NPC Game ===\n";
    std::cout << "Running for 10 seconds (test version)...\n\n";
    
    try {
        Game game;
        
        // Вместо вызова start(), запустим вручную на 10 секунд
        game.start();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    std::cout << "\nGame finished!\n";
    return 0;
}
