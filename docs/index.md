# dababase-repository 使用方法

dababase-repository 下层对数据库管理系统进行封装（目前支持 sqlite3），上层对接 awtk-mvvm，让应用程序开发人员，无需编写操作数据库的代码，即可实现数据库的增删改查。

## 1. 初始化

### 1.1 初始化数据库

首先需要创建一个缺省的数据库文件，里面有各个表的 schema 和缺省数据。这个数据库文件在第一次运行或恢复出厂设置时，会从资源中拷贝到运行目录，用来生成初始的数据库文件。

```c
/**
 * @method app_database_init
 * @annotation ["global"]
 * 初始化数据库。
 *
 * 通常我们在资源中放一个初始的数据库文件，里面有缺省的表和数据。
 * 本函数检查数据库文件是否存在，如果不存在，就从资源中取出初始的数据库文件，拷贝到用户运行目录。
 * 然后打开数据库。
 *
 * @param {const char*} appname 应用程序的名称。
 * @param {const char*} dbname 数据库名称。
 * 
 * @return {ret_t} 返回 RET_OK 表示成功，否则表示失败。
 */
ret_t app_database_init(const char* appname, const char* dbname);
```

> 对于 sqlite3 数据库，可以用 sqlite3 命令行工具创建缺省数据库文件。

在本例子中，缺省数据库文件为：

```
design/default/data/students.db
```

所以初始化代码为：

```
  app_database_init("student_list_mvvm", "students.db");
```

### 1.2 注册 view model

```c
  /*注册单条记录的 view model，所有的表都可以共用。*/
  view_model_factory_register("record", view_model_record_create);
  /*不同的列表需要用不同的 ViewModel*/
  view_model_factory_register("student_list", student_list_view_model_create);
```

## 2 实现 view model

### 2.1 创建 list view model

在创建 list view model 时，可以参考下面的模版进行修改，根据自己的需要设置相关参数即可：

```c
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
```

### 2.2 创建 record view model

单条记录共享 view\_model\_record，不需要自己实现，但是要注册一下（参考：注册 view model)。

## 3 实现 view

视图中的数据绑定和命令绑定和其它 MVVM 应用一样，这里列出 view model 支持的属性和命令。

### 3.1 view_model_repository 支持的属性和命令

 * 支持的属性：
    * limit: 限制最多加载的条数
    * filter: 过滤条件。缺省不过滤，加载全部。
    * fields: 加载的字段。缺省*，加载全部。
    * orderby: 排序方式，缺省主键。
    * ascending: 是否升序排列。
    * start_row: 从指定行查询数据。
    * 数据库记录中的字段(适用于列表中显示)。


* 支持的命令：
    * search: 用当前条件查询
    * add: 新建记录。
    * clear: 清除全部数据。
    * remove: 删除当前记录。
    * edit: 编辑当前记录。
    * detail: 查看当前记录。

> 具体用法请参考：design/default/ui/student_list_mvvm.xml

### 3.2 view_model_record 支持的属性和命令

 * 支持的属性： 
    * 由数据库表本身的字段决定。
 
 * 支持的命令：
    * add 用于新增记录。
    * save 用于更新记录。

> 具体用法请参考：
> * design/default/ui/student_add.xml
> * design/default/ui/student_edit.xml
> * design/default/ui/student_detail.xml