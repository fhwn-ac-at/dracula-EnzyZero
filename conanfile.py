from conan import ConanFile
from conan.tools.cmake import cmake_layout

class DraculaInterpreter(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("gtest/1.16.0")
        self.requires("spdlog/1.15.1") 
        self.requires("fmt/11.1.3") 
        self.requires("argparse/3.2")
        #self.requires("ncurses/6.4")

    def build_requirements(self):
        self.tool_requires("cmake/3.25.3")

    def layout(self):
        cmake_layout(self)
