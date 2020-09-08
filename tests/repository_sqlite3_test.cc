#include "gtest/gtest.h"
#include "csv_file.h"
#include "awtk.h"
#include "sqlite3/repository_sqlite3.h"

TEST(Repository, basic) {
  char sql[512];
  uint32_t i = 0;
  uint32_t rows = 0;
  uint32_t count = 0;
  object_t* o = NULL;
  sqlite3* db = NULL;
  ENSURE(sqlite3_open("data/test.db", &(db)) == SQLITE_OK);
  csv_file_t* csv = csv_file_create("data/scores.csv", ',');
  repository_t* r = repository_sqlite3_create(db, "scores", "name");

  o = repository_create_object(r);
  rows = csv_file_get_rows(csv);

  count = repository_count(r, NULL);

  tk_snprintf(sql, sizeof(sql), "DELETE FROM scores;", csv_file_get(csv, i, 0));
  count = repository_exec_sql(r, sql);

  for (i = 0; i < rows; i++) {
    object_set_prop_str(o, "name", csv_file_get(csv, i, 0));
    object_set_prop_int(o, "Chinese", tk_atoi(csv_file_get(csv, i, 1)));
    object_set_prop_int(o, "English", tk_atoi(csv_file_get(csv, i, 2)));
    object_set_prop_int(o, "Math", tk_atoi(csv_file_get(csv, i, 3)));
    object_set_prop_str(o, "memo", csv_file_get(csv, i, 4));
    ASSERT_EQ(repository_insert(r, o), RET_OK);
    ASSERT_EQ(repository_update(r, o), RET_OK);
    ASSERT_EQ(repository_exist(r, o), TRUE);
  }

  count = repository_count(r, NULL);
  ASSERT_EQ(count, rows);
  repository_select(r, NULL);
  ASSERT_EQ(repository_get_cache_nr(r), rows);

  for (i = 0; i < rows; i++) {
    object_set_prop_str(o, "name", csv_file_get(csv, i, 0));
    ASSERT_EQ(repository_exist(r, o), TRUE);
    ASSERT_EQ(repository_remove(r, o), RET_OK);
    ASSERT_EQ(repository_exist(r, o), FALSE);
  }
  count = repository_count(r, NULL);
  ASSERT_EQ(count, 0);

  OBJECT_UNREF(o);
  csv_file_destroy(csv);
  repository_destroy(r);
  sqlite3_close(db);
}
