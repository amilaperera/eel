from __future__ import print_function
import argparse
import sys

def config(target, generator):
    if genertor == 'makefiles':
        gen_cmd = '"Unix Makefiles"'
    elif generator == 'cdt':
        gen_cmd == '"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_MAKE_ARGUMENTS=-j8'
    else:
        raise Exception('Unsupported generator')


def main():
    parser = argparse.ArgumentParser(description='eel configuration')

    parser.add_argument('-t', '--target', required=True, help='target environment')
    parser.add_argument('-g', '--generator', required=True, help='cmake generators')
    args = parser.parse_args()
    print(args.target)
    print(args.generator)


if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print('Error: ', end='')
        print('{}'.format(e))
        sys.exit(1)

