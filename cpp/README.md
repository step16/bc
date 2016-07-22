# C++ Version

C++ can be quite tricky to compile when there's multiple
files/objects involved. So we're using [Bazel](http://www.bazel.io/)
(the open source version of Google's internal build tool to build.

Either

1. [download and install Bazel](http://www.bazel.io/docs/install.html)

or

2. Use the [class VM](https://docs.google.com/document/d/19xACeeHjvuDsMYrXtZuEoA8z2PFth51-vqQYkYTVDdY/edit) to run Bazel.

  * The latest version has been updated to include Bazel if you
    want to download it now.

  * You can use
    [VitualBox](https://www.virtualbox.org/wiki/Downloads) on
    Mac OS X too!

* To run tests

    bazel test :addressbook-test

* To run benchmarks

    bazel run :addressbook-bench

* You can run with compiler optimization by running

    bazel run -c opt :addressbook-bench

