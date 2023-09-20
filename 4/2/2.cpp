#include <iostream>
#include <fstream>

class DataHandler
{
public:
    DataHandler() {};
    DataHandler(std::string data) : data_(data) {};
    ~DataHandler() = default;

    virtual std::string printData() const
    {
        return data_;
    }
protected:
    std::string data_;
};

class HTMLDataHandler : public DataHandler
{
public:
    HTMLDataHandler(std::string data) {
        data_ = data;
    };
    ~HTMLDataHandler() = default;

    std::string printData() const override
    {
        return "<html>" + data_ + "<html/>";
    }
};

class JSONDataHandler : public DataHandler
{
public:
    JSONDataHandler(std::string data)
    {
        data_ = data;
    };
    ~JSONDataHandler() = default;

    std::string printData() const override
    {
        return "{ \"data\": \"" + data_ + "\"}";
    }
};

void sendTo(std::ostream& stream, DataHandler* handler)
{
    stream << handler->printData();
}

int main()
{
    std::ofstream file("./file.txt");
    auto f = DataHandler("message");
    auto fh = HTMLDataHandler("message");
    auto fj = JSONDataHandler("message");

    sendTo(std::cout, std::addressof(f));
    std::cout << std::endl;
    sendTo(std::cout, std::addressof(fh));
    std::cout << std::endl;
    sendTo(std::cout, std::addressof(fj));

    sendTo(file, std::addressof(f));
    file << '\n';
    sendTo(file, std::addressof(fh));
    file << '\n';
    sendTo(file, std::addressof(fj));
}