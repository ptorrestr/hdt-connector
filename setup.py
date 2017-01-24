import os
import sys
import platform
from setuptools import setup
from setuptools.command.install import install
from distutils.command.build import build
import subprocess
from subprocess import call
from multiprocessing import cpu_count

try:
  hdt_cflags = os.environ['HDT_CFLAGS']
except KeyError:
  hdt_cflags = "/usr/include"
try:
  hdt_libs = os.environ['HDT_LIBS']
except KeyError:
  hdt_libs = "/usr/lib"
try:
  boost_root = os.environ['BOOST_ROOT']
except KeyError:
  boost_root = "/usr"
try:
  python_version = os.environ['PYTHON_VERSION']
except KeyError:
  python_version = str(sys.version_info.major) + "." + str(sys.version_info.minor)

BASEPATH = os.path.dirname(os.path.abspath(__file__))
HDTCONNECTOR_PATH = os.path.join(BASEPATH, 'libhdtconnector')

class build_hdtconnector(build):
  def run(self):
    # Run original build code
    build.run(self)

    # Configure HDTConnector
    build_path = os.path.abspath(self.build_temp)
    
    cmd_autogen = [
      './autogen.sh',
    ]

    cmd_configure = [
      './configure',
      'HDT_CFLAGS=' + hdt_cflags,
      'HDT_LIBS=' + hdt_libs,
      '--with-boost=' + boost_root,
      'PYTHON_VERSION=' + python_version,
      '--prefix=' + build_path,
    ]

    cmd_make = [
      '/bin/bash',
      '-c',
      'make && make install'
    ]

    library_extension = ".so"
    if platform.system() == "Darwin":
      library_extension = ".dylib" 

    cmd_symlink = [
      'ln',
      '-s',
      'libhdtconnector' + library_extension,
      'libhdtconnector.so'
    ]

    def autogen():
      print('*'*80)
      call(cmd_autogen, cwd=HDTCONNECTOR_PATH)
      print('*'*80)

    def configure():
      print('*'*80)
      call(cmd_configure, cwd=HDTCONNECTOR_PATH)
      print('*'*80)

    def compile():
      print('*'*80)
      call(cmd_make, cwd=HDTCONNECTOR_PATH)
      print('*'*80)

    def symlink():
      print('*'*80)
      call(cmd_symlink, cwd=build_path + "/lib")
      print('*'*80)

    def cat():
      print('*'*80)
      call(["ls -la "], cwd=HDTCONNECTOR_PATH)
      print('*'*80)

    self.execute(autogen, [], 'generating autotools')
    self.execute(configure, [], 'configuring hdtconnector')
    self.execute(cat, [], 'cat')
    self.execute(compile, [], 'compiling htdconnector')
    if platform.system() == "Darwin":
      self.execute(symlink, [], 'adding symlink for htdconnector')
    
    # Copy hdt to library build folder
    self.copy_tree(build_path + "/lib", self.build_lib + "/hdtconnector")

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
    print(self.build_lib)
    print(self.install_lib)
    self.copy_tree(self.build_lib, self.install_lib)

def readme():
  with open('README.md') as f:
    return f.read()

def version():
  out = subprocess.Popen(['git','describe','--tags'], stdout = subprocess.PIPE, universal_newlines = True)
  out.wait()
  if out.returncode == 0:
    m_version = out.stdout.read().strip()
    version = m_version.split("-")
    if len(version) > 0:
      print(version[0])
      return version[0]
  return "0.0.1" #default version

setup(
  name = 'hdtconnector',
  version = version(),
  description = 'HDT connector',
  long_description = readme(),
  classifiers = [
    'Programming Language :: Python :: 3.5',
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
  packages = ['hdtconnector'],
  test_suite = '',
)
    
