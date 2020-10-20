import subprocess as sp
import os
import sys

def fetch_files(base_path, extension):
    files = []
    args = []
    args.append("powershell")
    args.append("Get-ChildItem")
    args.append("-Path")
    args.append(base_path)
    args.append("-Filter")
    args.append("*."+extension)
    args.append("-Recurse")
    args.append("-File")
    args.append("-Name")
    files_to_lint = sp.run(args=args,universal_newlines = True,capture_output=True, text=True)
    files_to_lint = files_to_lint.stdout.splitlines()
    for file in files_to_lint:
        files.append(base_path+"/"+file)
    return files

def fetch_all_file_to_lint(base_path):
    files_to_lint = []
    files_to_lint.extend(fetch_files(base_path,"cpp"))
    files_to_lint.extend(fetch_files(base_path,"hpp"))
    return files_to_lint

def lint_files(files,script_path):
    args=[]
    args.append("powershell")
    args.append("python")
    args.append(script_path+"/clang-format.py")
    args.append("--style")
    args.append("microsoft")
    args.extend(files)
    clang_output = sp.run(args=args,universal_newlines = True,capture_output=True, text=True);
    print(clang_output.stdout)
    return clang_output.returncode

def main():
    files = fetch_all_file_to_lint("../src/Engine")
    return lint_files(files,"./Linting")

if __name__ == "__main__":
    ret = main()
    sys.exit(ret)
