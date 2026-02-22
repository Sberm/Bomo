cc_binary(
    name = "FileTest",
    srcs = ["FileTest.cc"],
    copts = [
        "-Isrc/lib",
        "-Iexternal/boost.filesystem+/include"
    ],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//src/lib/File:File",
        "@boost.filesystem"
    ]
)
