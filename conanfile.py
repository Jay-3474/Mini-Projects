#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake


class HelloConan(ConanFile):
    name = "hello"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package"
    requires = ()
    # requires = ("json-c/0.17", "jsoncpp/1.9.5", "nlohmann_json/3.11.2")

    def build(self):
        cmake = CMake(self)
        cmake.verbose = True
        cmake.configure()
        cmake.build()
        cmake.test(output_on_failure=True)
        cmake.install()
