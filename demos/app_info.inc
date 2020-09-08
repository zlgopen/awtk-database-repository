#include "sqlite3/repository_sqlite3.h"

typedef struct _app_info_t {
  sqlite3* db;
} app_info_t;

static app_info_t s_app_info;

static ret_t app_info_init(const char* database) {
  sqlite3_initialize();
  return_value_if_fail(database != NULL, RET_BAD_PARAMS);

  memset(&s_app_info, 0, sizeof(app_info_t));
  ENSURE(sqlite3_open(database, &(s_app_info.db)) == SQLITE_OK);

  return RET_OK;
}

static ret_t app_info_deinit(void) {
  if (s_app_info.db != NULL) {
    sqlite3_close(s_app_info.db);
    s_app_info.db = NULL;
  }

  return RET_OK;
}

