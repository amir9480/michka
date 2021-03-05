import sys
import os
import re
import json
import pprint
import CppHeaderParser


generator_comment = '// Generated automatically by Michka (https://github.com/amir9480/michka).\n// Please DO NOT Modify this file.\n\n'

def file_get_contents(path, flags):
    if os.path.exists(path):
        f = open(path, flags)
        output = f.read()
        f.close()
        return output
    return None


def generate_source(source_file):
    out = ''
    source = file_get_contents(source_file, 'r')
    michka_class_define_regex = r'((class|struct)[^{:;/]+(:\s*([^{;/]+))?{([\s\S]+?))MICHKA_(CLASS|STRUCT|CLASS_WITH_NAME|STRUCT_WITH_NAME)?\((.+)\)\;'

    for match in re.finditer(michka_class_define_regex, source, re.MULTILINE):
        line_number = len(source[:match.span()[0] + len(match[1])].splitlines())
        class_parent_source = match[4]
        out += '\n#ifndef __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '\n'
        out += '#define __MICHKA_STRUCT_GENERATED_BODY_' + str(line_number) + '() \\\n'
        if class_parent_source:
            class_parent_source = re.sub(r'(^|[^\w])public([^\w])', '', class_parent_source, flags=re.MULTILINE)
            class_parents = enumerate(re.finditer(r'[A-z0-9_]+(<([^<>]|(<([^<>]|<([^<>]|<([^<>])*>)*>)*>))*>)?', class_parent_source, re.MULTILINE))
            for index, class_parent in class_parents:
                out += 'typedef ' + class_parent[0] + ' Parent' + (str(index + 1) if index > 0 else '') + ';'
        else:
            out += 'typedef void Parent;'
        out += '\n#endif\n'
    out += '\n\n// A simple generated code.'
    return out


def generate(path):
    generated_files = []
    for sub_path in os.listdir(path):
        full_path = (path + '/' + sub_path).replace(sys.argv[1] + '/', '', 1)
        if os.path.isdir(path + '/' + sub_path):
            if not os.path.exists(sys.argv[2] + '/' + full_path):
                os.makedirs(sys.argv[2] + '/' + full_path)
            generated_files = generated_files + generate(path + '/' + sub_path)
        elif sub_path.endswith('.h'):
            generated_file = os.path.splitext(full_path)[0].replace('.', '_') + '.generated.h'
            generated_files.append(generated_file)
            generated_file = sys.argv[2] + '/' + generated_file
            if not os.path.exists(generated_file) or os.path.getmtime(path + '/' + sub_path) > os.path.getmtime(generated_file) or False:
                file = open(generated_file, 'w')
                file.write(generator_comment)
                header_guard = '__MICHKA_GENERATED_' + generated_file.replace('/', '_').replace('.', '_').upper() + '__'
                file.write('#ifndef ' + header_guard + '\n')
                file.write('#define ' + header_guard + '\n\n')
                if full_path.endswith('.h'):
                    file.write('// #include "' + full_path + '"\n')
                file.write(generate_source(path + '/' + sub_path))
                file.write('\n\n#endif // ' + header_guard + '\n')
                file.close()
                print('Generated source for "' + path + '/' + sub_path + '"')

    return generated_files


def generate_files():
    generated_sources = generate(sys.argv[1])
    # cmake_file = open(sys.argv[2] + '/CMakeLists.txt', 'w')
    # cmake_file.write(generator_comment.replace('//', '#'))
    # cmake_file.write('set(\nSOURCES\n${SOURCES}\n')
    # for generated_source in generated_sources:
    #     cmake_file.write('${CMAKE_CURRENT_SOURCE_DIR}/' + generated_source + ')\n')
    # cmake_file.write('\nPARENT_SCOPE\n)\n')
    # cmake_file.close()


def main():
    if len(sys.argv) != 3:
        raise Exception('Wrong arguments.')
    if not os.path.exists(sys.argv[2]):
        os.makedirs(sys.argv[2])
    generate_files()


main()
# print(generate_source(sys.argv[1] + '/Core/Container/Rect.h'))
