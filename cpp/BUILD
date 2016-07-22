# -*- mode: python -*-
# This is a bazel build file (not actually a python file)
cc_test(
    name="addressbook-test",
    srcs=["addressbook-test.cc"],
    deps=[":addressbook",
          "@gtest//:main",
    ],
    copts = ["-Iexternal/gtest/include"],
)

cc_library(
    name="addressbook",
    srcs=["addressbook.cc", "addressbook-impl.cc"],
    hdrs=["addressbook.h", "addressbook-impl.h"],
)

cc_binary(
    name="addressbook-bench",
    srcs=["addressbook-bench.cc"],
    deps=[
        ":addressbook",
        "@benchmark//:benchmark"
    ],
    copts = ["-Iexternal/benchmark/include"]
)
