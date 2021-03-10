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

import sys
import os
import re
import json
import pprint
import CppHeaderParser


generator_comment = '// Generated automatically by Michka (https://github.com/amir9480/michka).\n// Please DO NOT Modify this file.\n\n'


# ---------------------------------------------------------------------------- #
def file_get_contents(path, flags):
    if os.path.exists(path):
        f = open(path, flags)
        output = f.read()
        f.close()
        return output
    return None


# ---------------------------------------------------------------------------- #
def generate_source(source_file):
    source = file_get_contents(source_file, 'r')
    generated_header_code = ''
    generated_source_code = ''
    michka_class_define_regex = r'((class|struct)[^{:;/]+(:\s*([^{;/]+))?{([\s\S]+?))MICHKA_(CLASS|STRUCT|CLASS_WITH_NAME|STRUCT_WITH_NAME)?\((.+)\)\;'

    for match in re.finditer(michka_class_define_regex, source, re.MULTILINE):
        line_number = len(source[:match.span()[0] + len(match[1])].splitlines())
        class_parent_source = match[4]
        generated_header_code += '\n\n#ifdef __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
        generated_header_code += '#undef __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
        generated_header_code += '#endif // __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
        generated_header_code += '#define __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '() \\\n'
        if class_parent_source:
            class_parent_source = re.sub(r'(^|[^\w])public([^\w])', '', class_parent_source, flags=re.MULTILINE)
            class_parents = enumerate(re.finditer(r'[A-z0-9_]+(<([^<>]|(<([^<>]|<([^<>]|<([^<>])*>)*>)*>))*>)?', class_parent_source, re.MULTILINE))
            for index, class_parent in class_parents:
                generated_header_code += 'typedef ' + class_parent[0] + ' Parent' + (str(index + 1) if index > 0 else '') + ';'
        else:
            generated_header_code += 'typedef void Parent;'
    return generated_header_code, generated_source_code


# ---------------------------------------------------------------------------- #
def generate(path, base_path, generated_path):
    generated_sources = []
    for sub_path in os.listdir(path):
        full_path = (path + '/' + sub_path).replace(base_path + '/', '', 1)
        if os.path.isdir(path + '/' + sub_path):
            if not os.path.exists(generated_path + '/' + full_path):
                os.makedirs(generated_path + '/' + full_path)
            generated_sources = generated_sources + generate(path + '/' + sub_path, base_path, generated_path)
        elif sub_path.endswith('.h'):
            generated_header = os.path.splitext(full_path)[0].replace('.', '_') + '.generated.h'
            generated_header = generated_path + '/' + generated_header
            generated_source = os.path.splitext(full_path)[0].replace('.', '_') + '.generated.cpp'
            generated_source = generated_path + '/' + generated_source
            generated_sources.append(generated_source.replace(generated_path + '/', ''))
            if not os.path.exists(generated_header) or os.path.getmtime(path + '/' + sub_path) > os.path.getmtime(generated_header) or False:
                generated_header_code, generated_source_code = generate_source(path + '/' + sub_path)
                # Header part
                file = open(generated_header, 'w')
                file.write(generator_comment)
                header_guard = '__MICHKA_GENERATED_' + generated_header.replace('/', '_').replace('.', '_').replace(':', '_').upper() + '__'
                file.write('#ifndef ' + header_guard + '\n')
                file.write('#define ' + header_guard + '\n\n')
                file.write(generated_header_code)
                file.write('\n\n#endif // ' + header_guard + '\n')
                file.close()

                # Source part
                file = open(generated_source, 'w')
                file.write(generator_comment)
                file.write('// ' + header_guard + '\n')
                file.write(generated_source_code)

                print('Generated source for "' + path + '/' + sub_path + '"')

    return generated_sources


# ---------------------------------------------------------------------------- #
def generate_files():
    generated_path = None
    for path_argument in sys.argv[1:]:
        path_argument_splited = path_argument.split('=')
        if len(path_argument_splited) == 2:
            generated_sources = generate(path_argument_splited[0], path_argument_splited[0], path_argument_splited[1])
            generated_path = path_argument_splited[1]
            cmake_file = open(generated_path + '/CMakeLists.txt', 'w')
            cmake_file.write(generator_comment.replace('//', '#'))
            cmake_file.write('set(\nSOURCES\n${SOURCES}\n')
            for generated_source in generated_sources:
                cmake_file.write('${CMAKE_CURRENT_SOURCE_DIR}/' + generated_source.replace('./', '') + '\n')
            cmake_file.write('\nPARENT_SCOPE\n)\n')
            cmake_file.close()


# ---------------------------------------------------------------------------- #
def main():
    if len(sys.argv) < 3:
        raise Exception('Wrong arguments.')
    generate_files()


# ---------------------------------------------------------------------------- #
main()
