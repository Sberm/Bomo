cc_library (
    name = "Match",
    deps = ["Engine", "BoyerMoore" ],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "Engine",
    srcs = ["Engine.cc"],
    copts = ["-Iexternal/re2+", "-Iexternal/boost.filesystem+/include", "-Isrc/lib", "--std=c++23"],
    deps = ["@re2", "@boost.filesystem", "//src/lib/Output:Output", "//src/lib/File:File"],
    hdrs = ["Engine.h"],
    visibility = ["//visibility:public"]
)

cc_library (
    name = "BoyerMoore",
    srcs = ["BoyerMoore.cc"],
    copts = ["-Isrc/lib", "--std=c++23"],
    deps = ["//src/lib/Output:Result"],
    hdrs = ["BoyerMoore.h"],
    visibility = ["//visibility:public"]
)
