/**
 * File:   view_model_repository.h
 * Author: AWTK Develop Team
 * Brief:  repository view model
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

#include "repository/repository.h"
#include "mvvm/base/view_model_array.h"

#ifndef TK_VIEW_MODEL_REPOSITORY_H
#define TK_VIEW_MODEL_REPOSITORY_H

BEGIN_C_DECLS

/**
 * @class view_model_repository_t
 *
 * view model of repository
 *
 */
typedef struct _view_model_repository_t {
  view_model_array_t view_model_array;

  /*private*/
  repository_t* r;

  char* filter;
  char* fields;
  char* orderby;

  int32_t limit;
  bool_t ascending;
  int32_t start_row;

  char* window_name_of_add;
  char* window_name_of_edit;
  char* window_name_of_detail;
} view_model_repository_t;

#define VIEW_MODEL_REPOSITORY_CMD_SEARCH "search"
#define VIEW_MODEL_REPOSITORY_PROP_LIMIT "limit"
#define VIEW_MODEL_REPOSITORY_PROP_FILTER "filter"
#define VIEW_MODEL_REPOSITORY_PROP_FIELDS "fields"
#define VIEW_MODEL_REPOSITORY_PROP_orderby "orderby"
#define VIEW_MODEL_REPOSITORY_PROP_ASCENDING "ascending"
#define VIEW_MODEL_REPOSITORY_PROP_START_ROW "start_row"

/**
 * @method view_model_repository_create_with
 * 创建repository view model对象。
 *
 * @annotation ["constructor"]
 * @param {repository_t*}  r repository对象。
 *
 * @return {view_model_t} 返回view_model_t对象。
 */
view_model_t* view_model_repository_create_with(repository_t* r);

/**
 * @method view_model_repository_set_filter 
 * 设置过滤条件(SQL的WHERE语句)。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {const char*} filter 过滤条件。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_filter(view_model_repository_t* vm, const char* filter);

/**
 * @method view_model_repository_set_fields
 * 设置选择的字段(缺省为全部即*)。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {const char*} fields 选择的字段。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_fields(view_model_repository_t* vm, const char* fields);

/**
 * @method view_model_repository_set_orderby
 * 设置排序的字段。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {const char*} orderby 排序的字段。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_orderby(view_model_repository_t* vm, const char* orderby);

/**
 * @method view_model_repository_set_ascending
 * 设置升序排序。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {bool_t} ascending 是否升序。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_ascending(view_model_repository_t* vm, bool_t ascending);

/**
 * @method view_model_repository_set_limit
 * 设置查询条数限制。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {int32_t} limit 条数限制。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_limit(view_model_repository_t* vm, int32_t limit);

/**
 * @method view_model_repository_set_start_row
 * 设置查询开始位置。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {int32_t} start_row 查询开始位置。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_start_row(view_model_repository_t* vm, int32_t start_row);

/**
 * @method view_model_repository_set_window_name_of_add
 * 设置新增记录的窗口名称。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {const char*} window_name 窗口名称。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_window_name_of_add(view_model_repository_t* vm,
                                                   const char* window_name);

/**
 * @method view_model_repository_set_window_name_of_edit
 * 设置编辑记录的窗口名称。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {const char*} window_name 窗口名称。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_window_name_of_edit(view_model_repository_t* vm,
                                                    const char* window_name);

/**
 * @method view_model_repository_set_window_name_of_detail
 * 设置查看记录的窗口名称。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * @param {const char*} window_name 窗口名称。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_set_window_name_of_detail(view_model_repository_t* vm,
                                                      const char* window_name);

/**
 * @method view_model_repository_search
 * 按当前条件进行查询。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * 
 * @return {ret_t} 返回RET_OK表示成功，否则表示失败
 */
ret_t view_model_repository_search(view_model_repository_t* vm);

/**
 * @method view_model_repository_cast
 * 把view_model对象转view_model_repository对象。
 *
 * @param {view_model_repository_t*}  vm view_model对象。
 * 
 * @return {view_model_repository_t*} 返回view_model_repository对象。
 */
view_model_repository_t* view_model_repository_cast(view_model_t* vm);

#define VIEW_MODEL_REPOSITORY(vm) view_model_repository_cast(vm)

END_C_DECLS

#endif /*TK_VIEW_MODEL_REPOSITORY_H*/
