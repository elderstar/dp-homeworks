#include "proxy.h"
#include<iostream>

std::string VeryHeavyDatabase::GetData(const std::string& key) const noexcept {
    return "Very Big Data String: " + key;
}

std::string CacheProxyDB::GetData(const std::string& key) noexcept {
    if (cache_.find(key) == cache_.end()) {
        std::cout << "Get from real object\n";
        cache_[key] = real_db_->GetData(key);
    }
    else {
        std::cout << "Get from cache\n";
    }
    return cache_.at(key);
}

std::string TestDB::GetData(const std::string& key) noexcept {
    return "test_data\n";
}

std::string OneShotDB::GetData(const std::string& key) noexcept {
    if (shots_ > 0)
    {
        --shots_;
        return real_db_->GetData(key);
    }
    else {
        return "error";
    }
}
