from __future__ import division, absolute_import, print_function
from ctypes import RTLD_GLOBAL
import sys

##TODO: Improve the import of the library

def dl_import(import_expr):
    """Import module according to import_expr, but with RTLD_GLOBAL enabled."""
    # we need to get the locals and globals of the _calling_ function. Thus, we
    # need to go deeper into the call stack
    call_frame = sys._getframe(1)
    local_dict = call_frame.f_locals
    global_dict = call_frame.f_globals

    # RTLD_GLOBAL needs to be set in dlopen() if we want typeinfo and friends to
    # work properly across DSO boundaries. See http://gcc.gnu.org/faq.html#dso

    orig_dlopen_flags = sys.getdlopenflags()
    sys.setdlopenflags(RTLD_GLOBAL)

    try:
        exec(import_expr, local_dict, global_dict)
    finally:
        sys.setdlopenflags(orig_dlopen_flags)  # reset it to normal case to
                                               # avoid unnecessary symbol
                                               # collision

#dl_import("from . import libhdtconnector as core")
