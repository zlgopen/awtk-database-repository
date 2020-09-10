/**
 * File:   application.c
 * Author: AWTK Develop Team
 * Brief:  application
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2020-09-06 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "awtk.h"
#include "mvvm/mvvm.h"
#include "table_view_register.h"
#include "../res/assets_default.inc"
#include "table_client_custom_binder.h"
#include "slidable_row_register.h"
#include "repository/view_model_record.h"
#include "repository/view_model_repository.h"

#include "app_info.inc"

view_model_t *student_list_view_model_create(navigator_request_t *req) {
  view_model_t* vm = NULL;
  view_model_repository_t* view_model = NULL;
  repository_t* repository = repository_sqlite3_create(s_app_info.db, "scores", "name");

  vm = view_model_repository_create_with(repository);
  view_model = VIEW_MODEL_REPOSITORY(vm);

  view_model_repository_set_filter(view_model, "Chinese > 80");
  view_model_repository_set_orderby(view_model, "Chinese");
  view_model_repository_search(view_model);

  view_model_repository_set_window_name_of_add(view_model, "student_add");
  view_model_repository_set_window_name_of_edit(view_model, "student_edit");
  view_model_repository_set_window_name_of_detail(view_model, "student_detail");

  return vm;
}

ret_t application_init(void) {
  app_info_init("student_list_mvvm", "students.db");

  mvvm_init();
  table_view_register();
  slidable_row_register();
  table_client_custom_binder_register();

  view_model_factory_register("record", view_model_record_create);
  view_model_factory_register("student_list", student_list_view_model_create);

  return navigator_to("student_list_mvvm");
}

ret_t application_exit() {
  app_info_deinit();
  mvvm_deinit();
  return RET_OK;
}

#include "awtk_main.inc"
