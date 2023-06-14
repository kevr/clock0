#
# Dependencies in this file are split between test and production
# executables. Some dependencies are shared, while others are specific
# to their executable compilation.
#
# `tp_deps` contains shared third-party dependencies
#
# If get_option('tests') is true, `tp_test_deps` is populated
# with all third-party test dependencies (including stubs)
#
# If get_option('exec') is true, `tp_exe_deps` is populated
# with all real third-party dependencies
#

conf = configuration_data()
conf.set('name', 'clock0')
conf.set('version', get_option('version'))
configure_file(
  input : 'config.hpp.in',
  output : 'config.hpp',
  configuration : conf)

sources = [
  'app.cpp',
  'ncurses.cpp',
  'tui/tui.cpp',
  'logging.cpp',
  'string.cpp',
  'filesystem.cpp',
  'options.cpp',
]

# Shared third-party dependencies
tp_deps = [fmt, boost_po]

if get_option('tests')
  subdir('stubs')

  # C++ compiler flags for test compilations
  test_args = ['-DBUILD_TESTS']

  # In-house static library for tests
  libclock0_test = static_library('clock0_test', sources,
    dependencies : fmt,
    cpp_args : test_args)
  clock0_test = declare_dependency(link_with : libclock0_test)

  # Third-party (and stubbed) test dependencies
  gtest_deps = [gtest, gtest_main, gmock]
  tp_test_deps = [stubs] + tp_deps + gtest_deps

  # All test dependencies
  test_deps = [clock0_test] + tp_test_deps

  main_test = executable('main.test', 'main.test.cpp',
    dependencies : test_deps,
    cpp_args : test_args)
  test('main.test', main_test)

  logging_test = executable('logging.test', 'logging.test.cpp',
    dependencies : test_deps,
    cpp_args : test_args)
  test('logging.test', logging_test)
endif

if get_option('exec')
  # In-house static library for executables
  libclock0 = static_library('clock0', sources,
    dependencies : fmt)
  clock0 = declare_dependency(link_with : libclock0)

  # Third-party executable dependencies
  tp_exe_deps = tp_deps + [curses]

  exe = executable('clock0', 'main.cpp',
    dependencies : [clock0] + tp_exe_deps,
    install : true)
endif
