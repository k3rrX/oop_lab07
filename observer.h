#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

// Screen Observer (вывод на экран)
class ScreenObserver : public BattleObserver {
public:
    void update(const std::string& event) override {
        std::cout << " " << event << std::endl;
    }
    
    void close() override {
        std::cout << "=== Наблюдение завершено ===" << std::endl;
    }
};

// Log Observer (запись в файл)
class LogObserver : public BattleObserver {
private:
    std::ofstream logFile;
    
    std::string getCurrentTime() {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
    
public:
    LogObserver(const std::string& filename) {
        logFile.open(filename, std::ios::app);
        if (logFile.is_open()) {
            logFile << "\n=== Начало сеанса " << getCurrentTime() << " ===\n";
        }
    }
    
    ~LogObserver() {
        close();
    }
    
    void update(const std::string& event) override {
        if (logFile.is_open()) {
            logFile << getCurrentTime() << " | " << event << "\n";
            logFile.flush();
        }
    }
    
    void close() override {
        if (logFile.is_open()) {
            logFile << "=== Конец сеанса ===\n\n";
            logFile.close();
        }
    }
};

#endif