load("@rules_cc//cc:defs.bzl", "cc_library")
load("@rules_cc//cc:defs.bzl", "cc_test")
load("//:variables.bzl", "COPTS")
load("//:variables.bzl", "LOPTS")

cc_library(
    name = "array",
    srcs = ["array.hpp"],
    visibility = ["//visibility:public"],
    copts = COPTS,
    linkopts = LOPTS,
)

cc_test (
    name = "test_array",
    srcs = ["test_array.cpp"],
    deps = ["@com_google_googletest//:gtest_main", "array"],
    copts = COPTS,
    linkopts = LOPTS,
)

