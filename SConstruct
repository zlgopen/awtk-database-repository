﻿import os
import scripts.app_helper as app

DEPENDS_LIBS = [
  {
    "root" : '../awtk-sqlite3',
    'static_libs': [],
    'shared_libs': ['sqlite3']
  },
  {
    "root" : '../awtk-mvvm',
    'shared_libs': ['mvvm'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-table-view',
    'shared_libs': ['table_view'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-slidable-row',
    'shared_libs': ['slidable_row'],
    'static_libs': []
  },
  {
    "root" : '../awtk-widget-table-view-mvvm',
    'shared_libs': ['table_view_mvvm'],
    'static_libs': []
  }
]

helper = app.Helper(ARGUMENTS);
helper.set_deps(DEPENDS_LIBS).set_dll_def('src/repository.def').set_libs(['repository']).call(DefaultEnvironment)

CustomWidgetSConscriptFiles = []
SConscriptFiles = CustomWidgetSConscriptFiles + ['src/SConscript','demos/SConscript', 'tests/SConscript']
helper.SConscript(SConscriptFiles)
