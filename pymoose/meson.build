# Author: Subhasis Ray
# Date: Sun Jul  7 2024

pymoose_src = [
  'PyRun.cpp',
  'helper.cpp',
  'MooseVec.cpp',
  'Finfo.cpp',
  'pymoose.cpp',
]

python_inc = py.get_path('include')

nanobind_dir = py.get_path('purelib') / 'nanobind'
nanobind_src = [
  nanobind_dir / 'src' / 'nb_internals.cpp',
  nanobind_dir / 'src' / 'nb_func.cpp',
  nanobind_dir / 'src' / 'nb_type.cpp',
  nanobind_dir / 'src' / 'nb_enum.cpp',
  nanobind_dir / 'src' / 'nb_ndarray.cpp',
  nanobind_dir / 'src' / 'nb_static_property.cpp',
  nanobind_dir / 'src' / 'common.cpp',
  nanobind_dir / 'src' / 'error.cpp',
  nanobind_dir / 'src' / 'trampoline.cpp',
  nanobind_dir / 'src' / 'implicit.cpp',
]

inc_dirs = [
  python_inc,
  nanobind_dir / 'include',
]

pymoose_lib = static_library('pymoose', pymoose_src + nanobind_src,
  include_directories: inc_dirs,
  dependencies: fmt_dep,
  cpp_args: '-fno-strict-aliasing')
