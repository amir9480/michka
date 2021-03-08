# ------------------------------------------------------------------------------- #
#                                     Michka                                      #
# ------------------------------------------------------------------------------- #
#                                  MIT License                                    #
#                                                                                 #
# Copyright (c) 2020-2021 amir alizadeh.                                          #
#                                                                                 #
# Permission is hereby granted, free of charge, to any person obtaining a copy    #
# of this software and associated documentation files (the "Software"), to deal   #
# in the Software without restriction, including without limitation the rights    #
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       #
# copies of the Software, and to permit persons to whom the Software is           #
# furnished to do so, subject to the following conditions:                        #
#                                                                                 #
# The above copyright notice and this permission notice shall be included in all  #
# copies or substantial portions of the Software.                                 #
#                                                                                 #
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      #
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        #
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     #
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          #
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   #
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   #
# SOFTWARE.                                                                       #
# ------------------------------------------------------------------------------- #

import subprocess
import sys
import os


# ---------------------------------------------------------------------------- #
def build_google_test(build_type):
    if build_type == 'Debug':
        if not os.path.exists('thirdparty/build/googletest/lib/Debug/gtestd.lib'):
            subprocess.run('cmake ./thirdparty/googletest -Bthirdparty/build/googletest -Dgtest_force_shared_crt=On -T host=x64 -A x64')
            subprocess.run('cmake --build thirdparty/build/googletest --config Debug')
    else:
        if not os.path.exists('thirdparty/build/googletest/lib/Release/gtest.lib'):
            subprocess.run('cmake ./thirdparty/googletest -Bthirdparty/build/googletest -Dgtest_force_shared_crt=On -T host=x64 -A x64')
            subprocess.run('cmake --build thirdparty/build/googletest --config Release')


# ---------------------------------------------------------------------------- #
def main():
    build_type = sys.argv[1] if len(sys.argv) >= 2 else 'Debug'
    build_google_test(build_type)


# ---------------------------------------------------------------------------- #
main()
