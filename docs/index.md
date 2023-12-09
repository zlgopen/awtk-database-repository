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

## 2 实现 view

视图中的数据绑定和命令绑定和其它 MVVM 应用一样，这里列出 view model 支持的属性和命令。

database 视图模型的初始化参数有：

 * table: 数据库表名。
 * key: 主键字段名。
 * start: 起始行。
 * count: 加载的行数。
 * filter: 过滤条件。
 * fields: 加载的字段。
 * orderby: 排序方式。
 * ascending: 是否升序排列。
  
如：
```xml
<window theme="main" v-model="database(table=scores, key=name, start=0, count=100, filter='Chinese > 80', orderby=Chinese, fields='*')" >
```

record 视图模型一般不需要初始化参数，只有创建记录才需要，此时需要指定各个字段的默认值。
 
如：
```xml
<window  anim_hint="htranslate" text="User New" v-model="record(name='', Chinese=70, Math=80, English=90, memo='')" 
  children_layout="default(h=40,c=2,m=5,s=10)">
```

### 2.1 view_model_repository 支持的属性和命令

 * 支持的属性：
    * limit: 限制最多加载的条数
    * filter: 过滤条件。缺省不过滤，加载全部。
    * fields: 加载的字段。缺省*，加载全部。
    * orderby: 排序方式，缺省主键。
    * ascending: 是否升序排列。
    * start_row: 从指定行查询数据。
    * 数据库记录中的字段（适用于列表中显示）。

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
> * design/default/ui/scores_add.xml
> * design/default/ui/scores_edit.xml
> * design/default/ui/scores_detail.xml