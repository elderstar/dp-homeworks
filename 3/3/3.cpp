#include <iostream>
#include "Logger.h"

void print(LogCommand* logger, const std::string& message) {
	logger->print(message);
};

class Message {
public:
	enum class Type
	{
		fatalErr,
		err,
		warn,
		unknown,
	};

	virtual ~Message() = default;
	virtual Type type() const = 0;
	virtual const char* message() const = 0;
};

class Handler {
public:
	explicit Handler(std::unique_ptr<Handler> next) : next_(std::move(next)) {};
	virtual ~Handler() = default;

	void receiveMsg(const Message& msg)
	{
		if (handle(msg))
		{
			return;
		}
		if (!next_)
		{
			throw std::runtime_error("Error: Message should be handled!");
		}
		next_->receiveMsg(msg);
	}
private:
	virtual bool handle(const Message& msg) = 0;
	std::unique_ptr<Handler> next_;
};

class FatalErrHandler : public Handler{
public:
	using Handler::Handler;
private:
	ConsoleLogger logger;
	FileLogger f_logger;
	
	bool handle(const Message& msg) override {
		if (msg.type() != Message::Type::fatalErr)
		{
			return false;
		}
		logger.print(msg.message());
		f_logger.print(msg.message());
		throw std::runtime_error(msg.message());
		//return true;
	}
};

class ErrHandler : public Handler {
public:
	using Handler::Handler;
private:
	FileLogger f_logger;

	bool handle(const Message& msg) override {
		if (msg.type() != Message::Type::err)
		{
			return false;
		}
		f_logger.print(msg.message());
		return true;
	}
};

class WarnHandler : public Handler {
public:
	using Handler::Handler;
private:
	ConsoleLogger logger;

	bool handle(const Message& msg) override {
		if (msg.type() != Message::Type::warn)
		{
			return false;
		}
		logger.print(msg.message());
		return true;
	}
};

class FatalMessage : public Message {
public:
	Type type() const override { return Type::fatalErr; }
	const char* message() const override {
		return "Fatal error occurred";
	}
};

class ErrMessage : public Message {
public:
	Type type() const override { return Type::err; }
	const char* message() const override {
		return "Error occurred";
	}
};

class WarnMessage : public Message {
public:
	Type type() const override { return Type::warn; }
	const char* message() const override {
		return "Some warning";
	}
};

class UnknownMessage : public Message {
public:
	Type type() const override { return Type::unknown; }
	const char* message() const override {
		return "Hello world!";
	}
};

int main()
{
	auto fatal_err_handler = std::make_unique<FatalErrHandler>(nullptr);
	auto warning_handler = std::make_unique<WarnHandler>(std::move(fatal_err_handler));
	auto err_handler = std::make_unique<ErrHandler>(std::move(warning_handler));

	try
	{
		err_handler->receiveMsg(FatalMessage());
		err_handler->receiveMsg(ErrMessage());
		err_handler->receiveMsg(WarnMessage());
		err_handler->receiveMsg(UnknownMessage());
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
