project('clock0', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
  ])

if get_option('exec')
  # Production dependencies
  curses = dependency('ncursesw', required : true)
endif

if get_option('tests')
  # Test dependencies
  gtest_proj = subproject('gtest')
  gtest = gtest_proj.get_variable('gtest_dep')
  gtest_main = gtest_proj.get_variable('gtest_main_dep')
  gmock = gtest_proj.get_variable('gmock_dep')
endif

subdir('src')
