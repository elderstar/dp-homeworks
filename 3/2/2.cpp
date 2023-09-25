#include <iostream>
#include <vector>
#include <fstream>

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

class Observer {
public:
    Observer() {};
    ~Observer() = default;

    virtual void onWarning(const std::string& message)
    {
        auto logger = ConsoleLogger();
        print(std::addressof(logger), message);
    }

    virtual void onError(const std::string& message)
    {
        auto logger = FileLogger("./f_log.txt");
        print(std::addressof(logger), message);
    }

    virtual void onFatalError(const std::string& message)
    {
        auto c_logger = ConsoleLogger();
        auto f_logger = FileLogger("./f_log.txt");

        print(std::addressof(c_logger), message);
        print(std::addressof(f_logger), message);
    }
};

class Observed {
public:
    Observed() {};
    ~Observed() = default;

    void addObserver(std::weak_ptr<Observer> observer)
    {
        observers_.push_back(observer);
    }

    void warning(const std::string& message) const 
    {
        for (auto observer : observers_)
        {
            if (auto strong_ptr = observer.lock())
            {
                strong_ptr->onWarning(message);
            };
        }
    };

    void error(const std::string& message) const
    {
        for (auto observer : observers_)
        {
            if (auto strong_ptr = observer.lock())
            {
                strong_ptr->onError(message);
            };
        }
    };

    void fatalError(const std::string& message) const
    {
        for (auto observer : observers_)
        {
            if (auto strong_ptr = observer.lock())
            {
                strong_ptr->onFatalError(message);
            };
        }
    };

private:
    std::vector<std::weak_ptr<Observer>> observers_;
};

int main()
{
    auto observed = Observed();
    std::shared_ptr<Observer> first_shrd_observer(new Observer());
    std::shared_ptr<Observer> second_shrd_observer(new Observer());

    observed.addObserver(std::weak_ptr<Observer>(first_shrd_observer));
    observed.addObserver(std::weak_ptr<Observer>(second_shrd_observer));

    observed.error("Some error");
    observed.warning("Some warning");
    observed.fatalError("Some fatal error");
}
