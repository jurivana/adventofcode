#pragma once

#include "util.h"

struct File {
    std::string name;
    int size;
};

struct Dir {
    std::string name;
    Dir* superdir;
    std::map<std::string, Dir*> subdirs;
    std::map<std::string, File*> files;
    int size;
};

Dir* retrieve_filesystem(std::vector<std::string> terminal_output) {
    Dir* root = new Dir();
    root->name = "/";
    root->superdir = nullptr;
    Dir* curr_dir = nullptr;
    for (int i = 0; i < terminal_output.size(); i++) {
        // std::cout << "---- " << terminal_output[i] << std::endl;
        if (terminal_output[i].at(0) != '$') {
            std::cout << "ERROR: Expected $" << std::endl;
            return nullptr;
        }
        std::string command = terminal_output[i].substr(2, 2);
        terminal_output[i].erase(0, 5);
        if (command == "cd") {
            if (terminal_output[i] == "/") {
                curr_dir = root;
            } else if (terminal_output[i] == "..") {
                if (curr_dir->superdir == nullptr) {
                    std::cout << "ERROR: No superdir" << std::endl;
                    return nullptr;
                }
                curr_dir = curr_dir->superdir;
            } else {
                if (curr_dir->subdirs.find(terminal_output[i]) == curr_dir->subdirs.end()) {
                    std::cout << "ERROR: No subdir \"" << terminal_output[i] << "\"" << std::endl;
                    return nullptr;
                }
                curr_dir = curr_dir->subdirs[terminal_output[i]];
            }
        } else if (command == "ls") {
            for (i = i + 1; i < terminal_output.size() && terminal_output[i].at(0) != '$'; i++) {
                // std::cout << "ls:  " << terminal_output[i] << std::endl;
                if (terminal_output[i].substr(0, 3) == "dir") {
                    terminal_output[i].erase(0, 4);
                    Dir* dir = new Dir();
                    dir->name = terminal_output[i];
                    dir->superdir = curr_dir;
                    curr_dir->subdirs.insert({terminal_output[i], dir});
                } else {
                    File* file = new File();
                    int pos = terminal_output[i].find(" ");
                    file->size = std::stoi(terminal_output[i].substr(0, pos));
                    terminal_output[i].erase(0, pos + 1);
                    file->name = terminal_output[i];
                    curr_dir->files.insert({terminal_output[i], file});
                }
            }
            if (i < terminal_output.size()) {
                i--;
            }
        } else {
            std::cout << "ERROR: Unknown command \"" << command << "\"" << std::endl;
            return nullptr;
        }
    }
    return root;
}

void print_dir(Dir* dir, int depth = 0) {
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
    }
    std::cout << dir->name << " " << dir->size << std::endl;
    for (auto [_, file] : dir->files) {
        for (int i = 0; i < depth + 1; i++) {
            std::cout << "  ";
        }
        std::cout << file->name << " " << file->size << std::endl;
    }
    for (auto [_, subdir] : dir->subdirs) {
        print_dir(subdir, depth + 1);
    }
}

void calculate_dir_sizes(Dir* dir) {
    int sum = 0;
    for (auto [_, file] : dir->files) {
        sum += file->size;
    }
    for (auto [_, subdir] : dir->subdirs) {
        calculate_dir_sizes(subdir);
        sum += subdir->size;
    }
    dir->size = sum;
}

int sum_leq_100000(Dir* dir) {
    int sum = 0;
    if (dir->size <= 100000) {
        sum += dir->size;
    }
    for (auto [_, subdir] : dir->subdirs) {
        sum += sum_leq_100000(subdir);
    }
    return sum;
}

int min_geq_x(Dir* dir, int x) {
    int min = std::numeric_limits<int>::max();
    if (dir->size >= x && dir->size < min) {
        min = dir->size;
    }
    for (auto [_, subdir] : dir->subdirs) {
        int submin = min_geq_x(subdir, x);
        if (submin < min) {
            min = submin;
        }
    }
    return min;
}

void aoc07() {
    Dir* root = retrieve_filesystem(read("../input/07.txt"));
    calculate_dir_sizes(root);
    // print_dir(root);
    std::cout << sum_leq_100000(root) << std::endl;

    std::cout << min_geq_x(root, root->size - (70000000 - 30000000)) << std::endl;
}
