if get_option('tests')
  test_deps = [gtest, gtest_main, gmock]

  main_test = executable('main.test', 'main.test.cpp',
    dependencies : test_deps)
  test('main.test', main_test)
endif

if get_option('exec')
  exe_deps = [curses]

  exe = executable('clock0', 'main.cpp',
    dependencies : exe_deps,
    install : true)
endif
