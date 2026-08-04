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
    copts = ["-Iexternal/boost.filesystem+/include"],
    deps = ["@boost.filesystem"],
    srcs = ["File.cc"],
    hdrs = ["File.h"],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "Filter",
    copts = ["-Iexternal/boost.filesystem+/include"],
    deps = ["@boost.filesystem"],
    srcs = ["Filter.cc"],
    hdrs = ["Filter.h"],
    visibility = ["//visibility:public"]
)
