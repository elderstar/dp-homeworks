#pragma once

#include "sql_query_builder.h"

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder
{
public:
	AdvancedSqlSelectQueryBuilder() = default;
	~AdvancedSqlSelectQueryBuilder() {};
	AdvancedSqlSelectQueryBuilder& AddWhereComp(const std::vector<std::string>& kv) noexcept;
};