#pragma once
#include <string>

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

    void print(const std::string& message) override;
};

class FileLogger : public LogCommand {
public:
    FileLogger(std::string path = "") : path_(path != "" ? path : DEFAULT_SYS_LOG_FILE) {};
    ~FileLogger() = default;

    void print(const std::string& message) override;
private:
    std::string path_;
};