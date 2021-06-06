load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_cc//cc:defs.bzl", "cc_test")


cc_library(
    name = "array",
    srcs = ["array.hpp"],
    visibility = ["//visibility:public"],
)

cc_test (
    name = "test_array",
    srcs = ["test_array.cpp"],
    deps = ["@com_google_googletest//:gtest_main", "array"],
)

