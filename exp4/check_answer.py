# -*- coding: utf-8 -*-

def load_file(file_path):
    with open(file_path, 'r') as f:
        return f.readlines()

def compare_str(line1, line2):
    str1, str2 = line1.strip(), line2.strip()
    return str1 == str2

def compare(result_path, compare_path):
    result_lines = load_file(result_path)
    compare_lines = load_file(compare_path)
    if len(result_lines) != len(compare_lines):
        print("check failed with unequal lines")
        print("origin lines:", len(result_lines))
        print("compare lines: ", len(compare_lines))
        return
    for line1, line2 in zip(result_lines, compare_lines):
        if not compare_str(line1, line2):
            print("check failed...")
            print("origin output is:", line1)
            print("compare output is: ", line2)
            return
    print("check passed")

if __name__ == '__main__':
    result_path = './exp7_out.txt'
    compare_path = './myexp7_out.txt'
    compare(result_path, compare_path)
