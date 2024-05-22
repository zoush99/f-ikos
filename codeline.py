import os

def count_lines(file_path):
    total_lines = 0
    with open(file_path, 'r') as f:
        for line in f:
            total_lines += 1
    return total_lines

def count_lines_in_directory(directory):
    files_info = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.f90', '.f')):
                file_path = os.path.join(root, file)
                lines = count_lines(file_path)
                files_info.append((file_path, lines))
    return files_info

def save_to_txt(files_info, output_file):
    with open(output_file, 'w') as f:
        for file, lines in files_info:
            f.write(f"{file}: {lines}\n")

import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py directory_path")
        sys.exit(1)

    directory = sys.argv[1]
    output_dir = "output"
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    output_file = os.path.join(output_dir, "lines_count.txt")
    files_info = count_lines_in_directory(directory)
    save_to_txt(files_info, output_file)
    print("Lines count saved to", output_file)
