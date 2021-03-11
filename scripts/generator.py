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
import clang.cindex


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
def parse_code(source_file):
    out = {
        'classes': {}
    }
    idx = clang.cindex.Index.create()
    try:
        tu = idx.parse(source_file, args='-xc++ --std=c++17 --no-standard-includes -fsyntax-only -nobuiltininc'.split())
    except Exception as e:
        print(e)
        return out

    for c in tu.cursor.walk_preorder():
        if c.kind in [clang.cindex.CursorKind.STRUCT_DECL, clang.cindex.CursorKind.CLASS_DECL] and c.spelling != 'MICHKA_API':
            parents = []
            for cc in c.get_children():
                if cc.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER:
                    parents.append(cc.get_definition().spelling)
            out['classes'][c.spelling] = {
                'name': c.spelling,
                'parents': parents
            }
    return out


# ---------------------------------------------------------------------------- #
def generate_source(source_file):
    source = file_get_contents(source_file, 'r')
    generated_header_code = ''
    generated_source_code = ''
    michka_class_define_regex = r'((class|struct)[^{:;/]+(:\s*([^{;/]+))?{([\s\S]+?))(MICHKA_(CLASS|STRUCT|CLASS_WITH_NAME|STRUCT_WITH_NAME))\((([^()]|\(([^()]|\(([^()]|\(([^()])*\))*\))*\))*)\)\;'
    michka_class_define_params_regex = r',?\s*([^\(,]*(\(([^()]|\(([^()])*\))*\))?)'

    parsed_code = parse_code(source_file)

    for match in re.finditer(michka_class_define_regex, source, re.MULTILINE):
        line_number = len(source[:match.span()[0] + len(match[1])].splitlines())
        generated_header_code += '\n\n#ifdef __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
        generated_header_code += '#undef __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
        generated_header_code += '#endif // __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
        generated_header_code += '#define __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '() \\\n'

        macro_params = re.findall(michka_class_define_params_regex, match[8])
        class_name = re.sub(r'(MICHKA_ARGUMENT\()?([^)<]+)(<.+>)?(\))?', r'\2', macro_params[0][0])
        for key, class_details in parsed_code['classes'].items():
            if class_details['name'] == class_name:
                if len(class_details['parents']) > 0:
                    for index, parent in enumerate(class_details['parents']):
                        generated_header_code += 'typedef ' + parent + ' Parent' + (str(index + 1) if index > 0 else '') + ';'
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
    if len(sys.argv) < 2:
        raise Exception('Wrong arguments.')
    clang.cindex.Config.set_library_path('C:/Program Files/LLVM/bin')
    generate_files()


# ---------------------------------------------------------------------------- #
main()
# print(generate_source('./tests/Classes/ReflectionClasses.h'))
