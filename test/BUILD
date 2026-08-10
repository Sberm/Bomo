cc_test(
    name = "FormatTest",
    srcs = ["FormatTest.cc"],
    copts = [
        "-Isrc/lib"
    ],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//src/lib/Output:Format"
    ]
)

cc_test(
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

cc_test(
    name = "RegexTest",
    srcs = ["RegexTest.cc"],
    copts = [
        "-Isrc/lib",
        "-Iexternal/boost.filesystem+/include"
    ],
    data = ["A_Pale_View_of_Hills.txt"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//src/lib/Match:Match",
        "@boost.filesystem"
    ]
)

cc_test(
    name = "BoyerMooreTest",
    srcs = ["BoyerMooreTest.cc"],
    copts = [
        "-Isrc/lib",
        "--std=c++23",
        "-Iexternal/boost.filesystem+/include"
    ],
    data = ["A_Pale_View_of_Hills.txt"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//src/lib/Match:Match",
        "//src/lib/File:File",
        "@boost.filesystem"
    ]
)
