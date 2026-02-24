cc_library (
    name = "File",
    # where is my external libraries?
    deps = [
        "_File",
        "Filter"
    ],
    visibility = ["//src:__pkg__", "//test:__pkg__"]
)

cc_library (
    name = "_File",
    copts = ["-Iexternal/boost.filesystem+/include"],
    deps = ["@boost.filesystem"],
    srcs = ["File.cc"],
    hdrs = ["File.h"],
)

cc_library (
    name = "Filter",
    copts = ["-Iexternal/boost.filesystem+/include"],
    deps = ["@boost.filesystem"],
    srcs = ["Filter.cc"],
    hdrs = ["Filter.h"],
)
