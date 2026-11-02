load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library (
    name = "Output",
    deps = [
        "Format",
        "Mode",
        "Result"
    ],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "Format",
    srcs = ["Format.cc"],
    hdrs = ["Format.h"],
    copts = [
        "-Isrc/lib",
        "--std=c++23",
    ],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "Mode",
    srcs = ["Mode.cc"],
    hdrs = ["Mode.h"],
    copts = [
        "-Isrc/lib",
        "--std=c++23",
    ],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "Result",
    srcs = ["Result.cc"],
    hdrs = ["Result.h"],
    copts = [
        "-Isrc/lib",
        "--std=c++23",
        "-Iexternal/boost.filesystem+/include",
    ],
    deps = [
        "@boost.filesystem",
        "Format",
        "//src/lib/Misc:Util",
    ],
    visibility = ["//visibility:public"]
)
