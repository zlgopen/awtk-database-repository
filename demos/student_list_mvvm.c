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
#include "app_database.h"
#include "table_view_register.h"
#include "../res/assets_default.inc"
#include "table_client_custom_binder.h"
#include "slidable_row_register.h"
#include "repository/view_model_record.h"
#include "repository/view_model_repository.h"


view_model_t *student_list_view_model_create(navigator_request_t *req) {
  view_model_t* vm = NULL;
  view_model_repository_t* view_model = NULL;
  repository_t* repository = app_database_create_repository("scores", "name");

  vm = view_model_repository_create_with(repository);

  view_model = VIEW_MODEL_REPOSITORY(vm);
  /*设置过滤条件*/
  view_model_repository_set_filter(view_model, "Chinese > 80");
  /*设置排序规则*/
  view_model_repository_set_orderby(view_model, "Chinese");
  /*加载数据*/
  view_model_repository_search(view_model);

  /*如果需要支持“新建”操作，请设置点击“新建”按钮时打开窗口的名称*/
  view_model_repository_set_window_name_of_add(view_model, "student_add");
  /*如果需要支持“编辑”操作，请设置点击“编辑”按钮时打开窗口的名称*/
  view_model_repository_set_window_name_of_edit(view_model, "student_edit");
  /*如果需要支持“详情”操作，请设置点击“详情”按钮时打开窗口的名称*/
  view_model_repository_set_window_name_of_detail(view_model, "student_detail");

  return vm;
}

ret_t application_init(void) {
  mvvm_init();
  table_view_register();
  slidable_row_register();
  table_client_custom_binder_register();

  app_database_init("student_list_mvvm", "students.db");
  /*注册单条记录的view model，所有的表都可以共用。*/
  view_model_factory_register("record", view_model_record_create);
  /*不同的列表需要用不同的ViewModel*/
  view_model_factory_register("student_list", student_list_view_model_create);;

  return navigator_to("student_list_mvvm");
}

ret_t application_exit() {
  app_database_deinit();
  mvvm_deinit();
  return RET_OK;
}

#include "awtk_main.inc"
