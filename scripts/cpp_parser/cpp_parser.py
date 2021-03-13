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

import re
from clang.cindex import *
from pprint import pprint


# ---------------------------------------------------------------------------- #
def qualified_name(c):
    if c is None or c.kind == CursorKind.TRANSLATION_UNIT:
        return ''
    else:
        qn = qualified_name(c.semantic_parent)
        return (qn + '::' if qn != '' else '') + c.spelling


# ---------------------------------------------------------------------------- #
def get_namespace(c):
    if c is None or c.kind == CursorKind.TRANSLATION_UNIT:
        return None
    elif c.kind == CursorKind.NAMESPACE:
        parent_namespace = get_namespace(c.semantic_parent)
        return {
            'name': c.spelling,
            'qualified_name': (parent_namespace['qualified_name'] + '::' if parent_namespace else '') + c.spelling,
            'parent': parent_namespace
        }
    return get_namespace(c.semantic_parent)


# ---------------------------------------------------------------------------- #
def parse_attributes(annotate):
    attributes = {}
    attributes_regex = r"([^,=]+)(=([^,\(]+(\(([^()]|\(([^()])*\))*\))?))?"
    for match in re.findall(attributes_regex, annotate):
        attributes[match[0]] = match[2] if match[2] else 'nullptr'
    return attributes


# ---------------------------------------------------------------------------- #
def parse_code(source_file):
    out = {
        'classes': {},
        'using_namespaces': []
    }
    idx = Index.create()
    try:
        tu = idx.parse(
            source_file,
            options=TranslationUnit.PARSE_DETAILED_PROCESSING_RECORD,
            args='-xc++ --std=c++17 -DMICHKA_PARSER --no-standard-includes --include-directory=./src'.split()
        )
    except Exception as e:
        print(e)
        return out

    for c in tu.cursor.walk_preorder():
        if str(c.location.file).replace('\\', '/') == source_file and c.kind in [CursorKind.STRUCT_DECL, CursorKind.CLASS_DECL, CursorKind.CLASS_TEMPLATE] and c.is_definition():
            # print(str(c.kind) + ' = ' + c.spelling, c.is_definition())
            reflection_enabled = False
            reflection_line = 1
            parents = []
            template_arguments = []
            attributes = {}
            for cc in c.get_children():
                if cc.kind == CursorKind.CXX_BASE_SPECIFIER:
                    parents.append(cc.get_definition().spelling)
                elif cc.kind == CursorKind.TEMPLATE_TYPE_PARAMETER:
                    template_arguments.append(cc.spelling)
                elif cc.spelling == 'MichkaReflectionEnabled':
                    reflection_enabled = True
                    for ccc in cc.get_children():
                        if ccc.kind == CursorKind.ANNOTATE_ATTR:
                            reflection_line = ccc.location.line
                            attributes = parse_attributes(ccc.spelling)

            template_arguments_string = '<' + ', '.join(template_arguments) + '>' if len(template_arguments) > 0 else ''
            out['classes'][c.spelling + template_arguments_string] = {
                'name': c.spelling + template_arguments_string,
                'line': int(c.location.line),
                'pure_name': c.spelling,
                'qualified_name': qualified_name(c) + template_arguments_string,
                'parents': parents,
                'namespace': get_namespace(c),
                'template_arguments': template_arguments,
                'reflection_enabled': reflection_enabled,
                'reflection_line': reflection_line,
                'attributes': attributes
            }

        if c.kind == CursorKind.USING_DIRECTIVE:
            for cc in c.get_children():
                if cc.kind == CursorKind.NAMESPACE_REF:
                    out['using_namespaces'].append(cc.spelling)

    # print(out)
    return out
