#include "sql_query_builder.h"

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column_title) noexcept
{
	columns.push_back(column_title);
	return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept
{
	for (const auto& el : columns)
	{
		AddColumn(el.c_str());
	}
	return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& from_db_title) noexcept
{
	from = from_db_title;
	return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& col, const std::string& val) noexcept
{
	where_conditions.push_back({ col, "=", val });
	return *this;
};

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept
{
	for (const auto& el:kv)
	{
		AddWhere(el.first, el.second);
	}
	return *this;
};

bool SqlSelectQueryBuilder::BuildQuery() 
{
	if (columns.size() == 0)
	{
		query_str = "SELECT * ";
	}
	else {
		query_str = "SELECT ";
		int size = columns.size();
		for (int i = 0; i < size; ++i)
		{
			query_str += columns.at(i);
			if (i != columns.size() - 1)
			{
				query_str += ",";
			}
			query_str += " ";
		}
	}
	if (from == "")
	{
		throw std::logic_error("Please add DB name");
	}
	else {
		query_str += "FROM " + from;
	}
	if (where_conditions.size() > 0)
	{
		int size = where_conditions.size();
		query_str += " WHERE ";
		for (int i = 0; i < size; ++i)
		{
			if (i != 0)
			{
				query_str += " AND ";
			}
			query_str += where_conditions.at(i).at(0);
			query_str += where_conditions.at(i).at(1);
			query_str += where_conditions.at(i).at(2);
		}
	}
	query_str += ";";

	return true;
};

std::string SqlSelectQueryBuilder::getQuery()
{
	return query_str;
};