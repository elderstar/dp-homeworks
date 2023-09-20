#pragma once
#include <map>
#include <string>

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept;
};

class CacheProxyDB : VeryHeavyDatabase {
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {};
    std::string GetData(const std::string& key) noexcept;

private:
    std::map<std::string, std::string> cache_;
    VeryHeavyDatabase* real_db_;
};

class TestDB : VeryHeavyDatabase {
public:
    explicit TestDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {};
    std::string GetData(const std::string& key) noexcept;
private:
    VeryHeavyDatabase* real_db_;
};

class OneShotDB : VeryHeavyDatabase {
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) : real_db_(real_object), shots_(shots) {};
    std::string GetData(const std::string& key) noexcept;
private:
    VeryHeavyDatabase* real_db_;
    size_t shots_;
};
