conf = configuration_data()
conf.set('name', 'clock0')
conf.set('version', get_option('version'))
configure_file(
  input : 'config.hpp.in',
  output : 'config.hpp',
  configuration : conf)

sources = [
  'ncurses.cpp',
  'tui/tui.cpp',
  'logging.cpp',
  'string.cpp',
]

if get_option('tests')
  subdir('stubs')

  # C++ compiler flags for test compilations
  test_args = ['-DBUILD_TESTS']

  # In-house static library for tests
  libclock0_test = static_library('clock0_test', sources,
    dependencies : fmt,
    cpp_args : test_args)
  clock0_test = declare_dependency(link_with : libclock0_test)

  # C++ dependencies for test compilations
  test_deps = [fmt, stubs, clock0_test, gtest, gtest_main, gmock]

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

  # C++ dependencies for executable compilations
  exe_deps = [fmt, curses, clock0]

  exe = executable('clock0', 'main.cpp',
    dependencies : exe_deps,
    install : true)
endif
