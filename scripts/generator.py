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
import json
import clang.cindex
from pprint import pprint
from cpp_parser import parse_code


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
    generated_header_code = ''
    generated_source_code = ''

    parsed_code = parse_code(source_file)

    for key, class_details in parsed_code['classes'].items():
        if class_details['reflection_enabled']:
            line_number = str(class_details['reflection_line'])
            generated_header_code += '\n\n#ifdef __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
            generated_header_code += '#undef __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
            generated_header_code += '#endif // __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
            generated_header_code += '#define __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '() \\\n'
            generated_header_code += 'typedef ' + class_details['name'] + ' Self; \\\n'
            if len(class_details['parents']) > 0:
                for index, parent in enumerate(class_details['parents']):
                    generated_header_code += 'typedef ' + parent + ' Parent' + (str(index + 1) if index > 0 else '') + '; \\\n'
            else:
                generated_header_code += 'typedef void Parent; \\\n'
            generated_header_code += 'static inline const char* className() \\\n'
            generated_header_code += '{ \\\n'
            generated_header_code += '    return "'+ class_details['name'] +'"; \\\n'
            generated_header_code += '} \\\n'

            generated_header_code += 'template<typename ReflectionType> \\\n'
            generated_header_code += 'static inline ReflectionType& classReflection() \\\n'
            generated_header_code += '{ \\\n'
            generated_header_code += '    static ReflectionType clsReflection(__FILE__).setName(className()); \\\n'

            for member in class_details['members']:
                generated_header_code += f'    /* reflection code for {member["name"]}; */ \\\n'
            generated_header_code += '    return clsReflection; \\\n'
            generated_header_code += '} \n\n'


            # if len(class_details['template_arguments']) == 0:
            #     generated_source_code += "namespace\n{\n"
            #     generated_source_code += "Michka::TypeInfo ti = Michka::TypeInfo::create<" + class_details['qualified_name'] + '>(' + class_details['qualified_name'] + '::classFileName())\n'
            #     for attribute in class_details['attributes']:
            #         generated_source_code += ".setAttribute(\"" + attribute + "\", " + class_details['attributes'][attribute] + ")\n"
            #     generated_source_code += ";\n"
            #     generated_source_code += "}\n\n"
    return generated_header_code, generated_source_code


# ---------------------------------------------------------------------------- #
def generate(path, base_path, generated_path):
    generated_headers = []
    generated_sources = []
    for sub_path in os.listdir(path) if os.path.isdir(path) else [path]:
        folder_path = path if os.path.isdir(path) else os.path.dirname(path)
        absolute_path = folder_path + '/' + sub_path
        path_relative_to_base = absolute_path.replace(base_path + '/', '', 1)
        if os.path.isdir(absolute_path):
            if not os.path.exists(generated_path + '/' + path_relative_to_base):
                os.makedirs(generated_path + '/' + path_relative_to_base)
            sub_directory_generated_headers, sub_directory_generated_sources = generate(absolute_path, base_path, generated_path)
            generated_headers += sub_directory_generated_headers
            generated_sources += sub_directory_generated_sources
        elif sub_path.endswith('.h'):
            generated_header = os.path.splitext(path_relative_to_base)[0].replace('.', '_') + '.generated.h'
            generated_headers.append(generated_header)
            generated_header = generated_path + '/' + generated_header
            generated_source = os.path.splitext(path_relative_to_base)[0].replace('.', '_') + '.generated.cpp'
            generated_source = generated_path + '/' + generated_source
            generated_sources.append(generated_source.replace(generated_path + '/', ''))
            if not os.path.exists(generated_header) or os.path.getmtime(absolute_path) > os.path.getmtime(generated_header) or False:
                generated_header_code, generated_source_code = generate_source(absolute_path)
                # Header part
                file = open(generated_header, 'w')
                file.write(generator_comment)
                header_guard = '__MICHKA_GENERATED_' + generated_header.replace('/', '_').replace('.', '_').replace(':', '_').upper() + '__'
                file.write('#ifndef ' + header_guard + '\n')
                file.write('#define ' + header_guard + '\n\n')
                file.write('#include "' + path_relative_to_base + '"')
                file.write('\n\n#endif // ' + header_guard + '\n')
                file.write(generated_header_code)
                file.close()

                # Source part
                file = open(generated_source, 'w')
                file.write('// ' + absolute_path + '\n')
                file.write(generated_source_code)

                print('Generated source for "' + absolute_path + '"')

    return generated_headers, generated_sources


# ---------------------------------------------------------------------------- #
def generate_files():
    generated_path = None
    for path_argument in sys.argv[1:]:
        path_argument_splited = path_argument.split('=')
        if len(path_argument_splited) == 2:
            generated_headers, generated_sources = generate(path_argument_splited[0], path_argument_splited[0], path_argument_splited[1])
            generated_path = path_argument_splited[1]
            generated_source_codes = generator_comment

            for generated_header in generated_headers:
                generated_source_codes += '#include "' + generated_header + '"\n'

            generated_source_codes += "\n\n"

            for generated_source in generated_sources:
                generated_source_codes += file_get_contents(generated_path + '/' + generated_source, 'r') + '\n'

            file = open(generated_path + '/MichkaGenerator.generated.cpp', 'w')
            file.write(generated_source_codes)
            file.close()

            if not os.path.exists(generated_path + '/CMakeLists.txt') or False:
                cmake_file = open(generated_path + '/CMakeLists.txt', 'w')
                cmake_file.write(generator_comment.replace('//', '#'))
                cmake_file.write('set(\nSOURCES\n${SOURCES}\n')
                cmake_file.write('${CMAKE_CURRENT_SOURCE_DIR}/MichkaGenerator.generated.cpp\n')
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
# generate('src/Core/Math/Vector4.h', 'src', 'build/Generated/MichkaGenerated')
# generate_source('./tests/Classes/ReflectionClasses.h')
