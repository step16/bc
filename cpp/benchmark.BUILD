cc_library(
    name = "benchmark",
    srcs = glob(
        ["src/*.cc"],
				exclude = ["src/re_posix.cc"],
    ),
    hdrs = glob([
        "include/**/*.h",
        "src/*.h"
    ]),
    copts = ["-Iexternal/benchmark/include","-DHAVE_STD_REGEX"],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"],
)
