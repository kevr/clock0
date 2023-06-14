project('clock0', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
  ])

if get_option('exec')
  # https://github.com/mirror/ncurses
  curses = dependency('ncursesw', required : true)
endif

if get_option('tests')
  # https://github.com/google/googletest
  gtest_proj = subproject('gtest')
  gtest = gtest_proj.get_variable('gtest_dep')
  gtest_main = gtest_proj.get_variable('gtest_main_dep')
  gmock = gtest_proj.get_variable('gmock_dep')
endif

# https://github.com/fmtlib/fmt
fmt_proj = subproject('fmt',
  default_options : ['default_library=static'])
fmt = fmt_proj.get_variable('fmt_dep')

# https://github.com/boostorg/boost
boost_po = dependency('boost',
  modules : ['program_options'],
  required : true)

subdir('src')
