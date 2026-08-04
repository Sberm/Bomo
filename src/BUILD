cc_binary (
    name = "bm",
	srcs = ['main.cc'],
    copts = ['-Iexternal/boost.program_options+/include', '-std="c++23"', '-Isrc/lib'],
    deps = [
        "//src/lib/Misc:Misc",
        "//src/lib/Match:Match",
        "//src/lib/File:File",
        "//src/lib/Thread:Thread",
        "//src/lib/Output:Output",
        # TODO: are these two needed?
        "@boost.filesystem",
        "@boost.program_options",
        "@re2"
    ]
)
