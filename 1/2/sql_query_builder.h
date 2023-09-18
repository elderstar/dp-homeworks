#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <map>

class SqlSelectQueryBuilder
{
public:
	SqlSelectQueryBuilder() = default;
	~SqlSelectQueryBuilder() {};
	SqlSelectQueryBuilder& AddColumn(const std::string& column_title) noexcept;
	SqlSelectQueryBuilder& AddFrom(const std::string&  from_db_title) noexcept;
	SqlSelectQueryBuilder& AddWhere(const std::string& col, const std::string& val) noexcept;
	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;
	bool virtual BuildQuery();
	std::string getQuery();
protected:
	std::string query_str = "";
	std::vector<std::string> columns{};
	std::string from = "";
	std::vector<std::vector<std::string>> where_conditions{};
};