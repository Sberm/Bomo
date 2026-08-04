# Bomo

Bomo is a fast pattern matcher

Bomo uses C++20

Build
```sh
bazel build //src:bm
```

Testing
```sh
bazel run //test:FileTest
bazel run //test:RegexTest
```

Debug
```sh
bazel build -c dbg //test:BoyerMooreTest
lldb bazel-bin/test/BoyerMooreTest
```

XCode things:

```sh
# error message
This most likely indicates that Xcode version 26.1.1.17B100 is not available on the host machine.

# add option
--repo_env=DEVELOPER_DIR=/Applications/Xcode.app/Contents/Developer
```
