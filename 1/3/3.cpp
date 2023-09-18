#include <iostream>
#include <cassert>
#include "adv_sql_query_builder.h"
#include "sql_query_builder.h"

int main()
{
    AdvancedSqlSelectQueryBuilder query_builder;
    query_builder.AddColumns({ "name", "phone" });
    query_builder.AddFrom("students");
    query_builder.AddWhereComp({ "id", ">", "42" }).AddWhereComp({ "created_at", ">", "2000-01-01" }).AddWhere("name", "john"); // Добавляем условие id > 42
    assert(query_builder.BuildQuery(),
        "SELECT name, phone FROM students WHERE id=42 AND name=John;");
    std::cout << query_builder.getQuery();
}
