#include <iostream>
#include "sql_query_builder.h"
#include <cassert>

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumns({ "phone", "id", "created_at" });
    query_builder.AddFrom("students");
    //query_builder.AddWhere("id", "42").AddWhere("name", "John");
    query_builder.AddWhere("id", "42").AddWhere({{ "name","John" }, { "created_at","2023-09-18" }});
    query_builder.BuildQuery();
    std::cout << query_builder.getQuery();
}