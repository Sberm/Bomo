load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary (
    name = "bm",
    srcs = ['main.cc'],
    copts = [
        '-Iexternal/boost.program_options+/include',
        '--std=c++23',
        '-Isrc/lib',
    ],
    deps = [
        "//src/lib/Match:Match",
        "//src/lib/Output:Output",
        "@boost.program_options",
    ]
)
