import random

_c_soruce_template = '''
#include <{c_header_file_name}>
#include <stdint.h>

const {number_type} {table_name}[{num_numbers}] = {{
{numbers}
}};
'''[1:-1]

_c_header_template = '''
#ifndef {include_guard}
#define {include_guard}
#include <stdint.h>
#define NUMBER_OF_{table_name}_ELEMENTS ({num_numbers})
#ifdef __cplusplus
extern "C" {{
#endif
extern const {number_type} {table_name}[{num_numbers}];
#ifdef __cplusplus
}}
#endif
#endif /* {include_guard} */
'''[1:-1]

if __name__ == "__main__":
    _type_list = {
        "char", "unisgned char", "signed char",
        "short", "unisgned short", "signed short",
        "int", "unisgned int", "signed int",
        "long", "unisgned long", "signed long",
        "long long", "unisgned long long", "signed long long",
        "int8_t", "uint8_t",
        "int16_t", "uint16_t",
        "int32_t", "uint32_t",
        "int64_t", "uint64_t"
    }
    
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("-n", "--number_of_random_number", type=int, default=10)
    parser.add_argument("-l", "--lower_limit_of_random_number", type=int, default=0)
    parser.add_argument("-u", "--upper_limit_of_random_number", type=int, default=9)
    parser.add_argument("-s", "--seed", type=int, default=0)
    parser.add_argument("--table_name", type=str, default="random_numbers")
    parser.add_argument("-t", "--type", type=str, default="int", choices=_type_list)
    args = parser.parse_args()
    
    lower = args.lower_limit_of_random_number
    upper = args.upper_limit_of_random_number
    num_numbers = args.number_of_random_number
    table_name = args.table_name
    c_header_file_name = f"{table_name}.h"
    c_source_file_name = f"{table_name}.c"
    number_type = args.type
    include_guard = f"{c_header_file_name.upper().replace('.', '_')}_INCLUDED"
    
    random.seed(args.seed)
    numbers = [str(random.randint(lower, upper)) for _ in range(num_numbers)]
    numbers_text = "\t" + ",\n\t".join(numbers)

    c_header_text = _c_header_template.format(
        include_guard = include_guard,
        number_type = number_type,
        table_name = table_name,
        num_numbers = num_numbers
    )
    c_soruce_text = _c_soruce_template.format(
        c_header_file_name = c_header_file_name,
        number_type = number_type,
        table_name = table_name,
        num_numbers = num_numbers,
        numbers = numbers_text
    )
    with open(c_header_file_name, "wt") as c_header_file:
        c_header_file.write(c_header_text)
    with open(c_source_file_name, "wt") as c_source_file:
        c_source_file.write(c_soruce_text)
    
