load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "array",
    srcs = ["array.hpp"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "array_test",
    deps = [":array"],
    srcs = ["main.cpp"],
    visibility = ["//visibility:public"],
)
