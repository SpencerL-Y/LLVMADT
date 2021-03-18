import os
import sys

DEFAULT_OUT_PATH = './'


class Translator:
    def __init__(self, in_file=None, o_path=None):
        self.out_path = o_path
        self.in_file = in_file
        self.file_name = self._get_file_name()

    def _get_file_name(self):
        return self.in_file.split('/')[-1]

    def translate(self, print_cfg=True):
        o_path = self.out_path + self.file_name
        command = "clang -O0 {} -fno-discard-value-names -emit-llvm -S -o {}_tmp.ll".format(self.in_file, o_path)
        print(command, os.system(command))
        command = "opt -mem2reg -instnamer {}_tmp.ll -o {}.bc".format(o_path, o_path)
        print(command, os.system(command))
        command = "llvm-dis {}.bc -o {}.ll".format(o_path, o_path)
        print(command, os.system(command))
        command = "rm -rf {}.bc".format(o_path)
        print(command, os.system(command))
        command = "rm -rf {}_tmp.ll".format(o_path)
        print(command, os.system(command))
        command = "cd {}".format(self.out_path)
        print(command, os.system(command))
        if print_cfg:
            command = "opt -dot-cfg {}.ll".format(self.file_name)
            print(command, os.system(command))
            command = "dot .main.dot -Tpng -o {}.png".format(self.file_name)
            print(command, os.system(command))
            command = "rm -rf .main.dot"
            print(command, os.system(command))


if __name__ == "__main__":
    in_path = sys.argv[1]
    out_path = DEFAULT_OUT_PATH
    if len(sys.argv) == 3:
        out_path = sys.argv[2]
    translator = Translator(in_path, out_path)
    translator.translate()
