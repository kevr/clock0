# clock0 - manage tasks like clockwork

A command-line task manager that interfaces with web-based VCS

![lint](https://github.com/kevr/clock0/actions/workflows/lint.yaml/badge.svg?branch=master)
![build](https://github.com/kevr/clock0/actions/workflows/build.yaml/badge.svg?branch=master)
![tests](https://github.com/kevr/clock0/actions/workflows/tests.yaml/badge.svg?branch=master)

## Building

Dependencies: C++17 compiler, [ncursesw](https://github.com/mirror/ncurses),
[boost/program_options](https://github.com/boostorg/boost/tree/master/libs)

This project relies on the [meson](https://mesonbuild.com/) build system as
well as compiler tools [ninja](https://github.com/ninja-build/ninja) or
[samurai](https://github.com/michaelforney/samurai) to configure and build its
executables and tests.

By default, the primary executable and test builds are enabled; to disable,
they can be toggled off by setting the `exec` and `tests` meson options
to false:

    ## Setup a build directory solely for tests
    $ meson setup -Dexec=false build-tests

    ## Setup a build directory solely for program executables
    $ meson setup -Dtests=false build-exec

## Coverage

Dependencies: [gcovr](https://gcovr.com), [lcov](https://github.com/linux-test-project/lcov)

Test coverage collection can be enabled using the `b_coverage` meson option
while building tests:

    $ meson setup -Dexec=false -Db_coverage=true build-tests

After running tests, coverage can be collected using the `coverage` target:

    ## First, run tests
    $ ninja -C build-tests test

    ## Then, collect coverage
    $ ninja -C build-tests coverage

## Installation

Once built, the project can be installed to the system by issuing they
`install` target:

    $ ninja -C build-exec install --skip-subprojects
