cc_library (
    name = "File",
    # where is my external libraries?
    deps = [
        "_File",
        "Filter"
    ],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "_File",
    copts = ["-Iexternal/boost.filesystem+/include", "--std=c++23"],
    deps = ["@boost.filesystem"],
    srcs = ["File.cc"],
    hdrs = ["File.h"],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "Filter",
    copts = ["-Iexternal/boost.filesystem+/include", "-Iexternal/re2+", "--std=c++23"],
    deps = ["@boost.filesystem", "@re2"],
    srcs = ["Filter.cc"],
    hdrs = ["Filter.h"],
    visibility = ["//visibility:public"]
)
