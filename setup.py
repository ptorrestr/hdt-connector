import os
from setuptools import setup
from setuptools.command.install import install
from distutils.command.build import build
from subprocess import call
from multiprocessing import cpu_count

hdt_include_path = "/home/pablo/workspace/c++/hdt-cpp/hdt-lib/include"
hdt_libs_path = "/home/pablo/workspace/c++/hdt-cpp/hdt-lib"
boost_include_path = "/opt/usr/local/boost-1.56.0/include"
boost_libs_path = "/opt/usr/local/boost-1.56.0/lib"

BASEPATH = os.path.dirname(os.path.abspath(__file__))
HDTCONNECTOR_PATH = os.path.join(BASEPATH, 'hdt-connector')

class build_hdtconnector(build):
  def run(self):
    # Run original build code
    build.run(self)

    # Configure HDTConnector
    build_path = os.path.abspath(self.build_temp)
    cmd_configure = [
      './configure',
      'HDT_CFLAGS=-I' + hdt_include_path,
      'HDT_LIBS=-L' + hdt_libs_path,
      'boost_CFLAGS=-I' + boost_include_path,
      'boost_LIBS=-L' + boost_libs_path,
      '--prefix=' + build_path
    ]

    cmd_make = [
      '/bin/bash',
      '-c',
      'make && make install'
    ]
    target_files = [os.path.join(build_path, 'bin/hdtconnector.so')]

    def configure():
      print('*'*80)
      call(cmd_configure, cwd=HDTCONNECTOR_PATH)
      print('*'*80)

    def compile():
      print('*'*80)
      call(cmd_make, cwd=HDTCONNECTOR_PATH)
      print('*'*80)

    self.execute(configure, [], 'configuring hdtconnector')
    self.execute(compile, [], 'compiling htdconnector')
    
    # Copy hdt to library build folder
    self.copy_tree(build_path + "/bin", self.build_lib + "/hdtconnector")

class install_hdtconnector(install):
  def initialize_options(self):
    install.initialize_options(self)
    self.build_scripts = None

  def finalize_options(self):
    install.finalize_options(self)
    self.set_undefined_options('build', ('build_scripts', 'build_scripts'))

  def run(self):
    # Run original install
    install.run(self)

    # Install HDT connector
    print("Installing hdtconnector")
    self.copy_tree(self.build_lib, self.install_lib)

def readme():
  with open('README.md') as f:
    return f.read()

setup(
  name = 'hdtconnector',
  version = '1.0',
  description = 'HDT connector for DBpedia',
  long_description = readme(),
  classifiers = [
    'Programming Language :: Python :: 3.4',
    'Programming Language :: C++',
  ],
  url = 'http://github.com/ptorrestr/hdt-connector',
  author = 'Pablo Torres',
  author_email = 'pablo.torres.t@gmail.com',
  license = 'GNU',
  zip_safe = False,
  cmdclass = {
    'build' : build_hdtconnector,
    'install' : install_hdtconnector,
  },
  packages = ['hdt','hdt.tests','hdtconnector'],
  install_requires = [
    'pyaml >= 13.12.0',
  ],
  test_suite = 'hdt.tests',
)
    
