#include "adv_sql_query_builder.h"
#include "sql_query_builder.h"

AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddWhereComp(const std::vector<std::string>& kv) noexcept
{
	where_conditions.push_back({ kv.at(0), kv.at(1), kv.at(2) });
	return *this;
};
