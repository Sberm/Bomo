cc_library (
    name = "Misc",
    deps = [
        "Config",
        "ShellComp"
    ],
    copts = [
        "-Isrc/lib",
        "--std=c++23"
    ],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "Config",
    srcs = ["Config.cc"],
    hdrs = ["Config.h"],
    copts = [
        "-Isrc/lib",
        "--std=c++23"
    ],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "ShellComp",
    srcs = ["ShellComp.cc"],
    hdrs = ["ShellComp.h"],
    copts = [
        "-Isrc/lib",
        "--std=c++23"
    ],
    visibility = ["//visibility:public"]
)
