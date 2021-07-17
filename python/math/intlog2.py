def intlog2_math(v):
    return int(numpy.floor(numpy.log2(v)))

def intlog2_linsearch(v):
    bit_mask = 0x80000000
    for i in range(31, -1, -1):
        if 0 < (v & bit_mask):
            break
        else:
            bit_mask = bit_mask >> 1
    return i

def intlog2_binsearch(v):
    if 0 < (v & 0xffff0000):
        if 0 < (v & 0xff000000):
            if 0 < (v & 0xf0000000):
                if 0 < (v & 0xc0000000):
                    if 0 < (v & 0x80000000):
                        return 31
                    else: # 0x40000000
                        return 30
                else: # 0x30000000
                    if 0 < (v & 0x20000000):
                        return 29
                    else: # 0x10000000
                        return 28
            else: # 0x0f000000
                if 0 < (v & 0x0c000000):
                    if 0 < (v & 0x08000000):
                        return 27
                    else: # 0x04000000
                        return 26
                else: # 0x03000000
                    if 0 < (v & 0x02000000):
                        return 25
                    else: # 0x01000000
                        return 24
        else: # 0x00ff0000
            if 0 < (v & 0x00f00000):
                if 0 < (v & 0x00c00000):
                    if 0 < (v & 0x00800000):
                        return 23
                    else: # 0x00400000
                        return 22
                else: # 0x00300000
                    if 0 < (v & 0x00200000):
                        return 21
                    else: # 0x00100000
                        return 20
            else: # 0x000f0000
                if 0 < (v & 0x000c0000):
                    if 0 < (v & 0x00080000):
                        return 19
                    else: # 0x00040000
                        return 18
                else: # 0x00030000
                    if 0 < (v & 0x00020000):
                        return 17
                    else: # 0x00010000
                        return 16
    else: # 0x0000ffff
        if 0 < (v & 0x0000ff00):
            if 0 < (v & 0x0000f000):
                if 0 < (v & 0x0000c000):
                    if 0 < (v & 0x00008000):
                        return 15
                    else: # 0x00004000
                        return 14
                else: # 0x00003000
                    if 0 < (v & 0x00002000):
                        return 13
                    else: # 0x00001000
                        return 12
            else: # 0x00000f00
                if 0 < (v & 0x00000c00):
                    if 0 < (v & 0x00000800):
                        return 11
                    else: # 0x00000400
                        return 10
                else: # 0x00000300
                    if 0 < (v & 0x00000200):
                        return 9
                    else: # 0x00000100
                        return 8
        else: # 0x000000ff
            if 0 < (v & 0x000000f0):
                if 0 < (v & 0x000000c0):
                    if 0 < (v & 0x00000080):
                        return 7
                    else: # 0x00000040
                        return 6
                else: # 0x00000030
                    if 0 < (v & 0x00000020):
                        return 5
                    else: # 0x00000010
                        return 4
            else: # 0x0000000f
                if 0 < (v & 0x0000000c):
                    if 0 < (v & 0x00000008):
                        return 3
                    else: # 0x00000004
                        return 2
                else: # 0x00000003
                    if 0 < (v & 0x00000002):
                        return 1
                    else: # 0x00000001
                        return 0

import numpy
bit8_table = [0 if v == 0 else intlog2_math(v) for v in range(256)]
def intlog2_8bit_table(v):
    if 0 < (v & 0xffff0000):
        if 0 < (v & 0xff000000):
            return bit8_table[v >> 24] + 24
        else: # 0x00ff0000
            return bit8_table[v >> 16] + 16
    else: # 0x0000ffff
        if 0 < (v & 0x0000ff00):
            return bit8_table[v >> 8] + 8
        else: # 0x000000ff
            return bit8_table[v]

bit16_table = [0 if v == 0 else intlog2_math(v) for v in range(65536)]
def intlog2_16bit_table(v):
    if 0 < (v & 0xffff0000):
        return bit16_table[v >> 16] + 16
    else: # 0x0000ffff
        return bit16_table[v]

def intlog2_py_string(v):
    return len(bin(v)) - 2

def intlog2_py_bit_length(v):
    return v.bit_length()

if __name__ == "__main__":
    import time
    n = 1000000
    def _time(target_function):
        st = time.time()
        _ = [target_function(v) for v in range(1, n)]
        et = time.time() - st
        return (target_function.__name__, et, _)

    results = []
    results.append(_time(intlog2_math))
    results.append(_time(intlog2_linsearch))
    results.append(_time(intlog2_binsearch))
    results.append(_time(intlog2_8bit_table))
    results.append(_time(intlog2_16bit_table))
    results.append(_time(intlog2_py_string))
    results.append(_time(intlog2_py_bit_length))

    for v in results:
        print(f"|{v[0]:20}|{v[1]:8.6f}|")
