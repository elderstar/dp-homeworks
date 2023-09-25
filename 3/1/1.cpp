#include <iostream>
#include <fstream>
#include <ctime>

const std::string DEFAULT_SYS_LOG_FILE = "./logs.txt";

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogger : public LogCommand {
public:
    ConsoleLogger() {};
    ~ConsoleLogger() = default;

    void print(const std::string& message) override {
        std::cout << message << "\n";
    };
};
class FileLogger : public LogCommand {
public:
    FileLogger(std::string path = "") : path_(path != "" ? path : DEFAULT_SYS_LOG_FILE) {};
    ~FileLogger() = default;

    void print(const std::string& message) override {
        std::ofstream file(path_ , std::ios::app);
        file << message << "\n";
    };
private:
    std::string path_;
};

void print(LogCommand* logger, const std::string& message) {
    logger->print(message);
};

int main()
{
    auto logger = ConsoleLogger();
    auto f_logger = FileLogger("./f_log.txt");

    print(std::addressof(logger), "Hello World!");
    print(std::addressof(f_logger), "Hello World!");
}