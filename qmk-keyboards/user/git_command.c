#include "quantum.h"
#include "antonstrand.h"
#include "git_command.h"

// Open both `git` and `https` projects in github.
// \ is alt + shift + 7 on a swedish mac keymap. A combination sendstring doesn't seem to support. That's the reason behind SS_LSFT("|").
char project_root[83] = "https://github.$(git config remote.origin.url | cut -f2 -d. | sed 's/:/" SS_LSFT("|") "//')";
char branch[42]       = "$(git symbolic-ref --quiet --short HEAD )";
char directory[31]    = "$(git rev-parse --show-prefix)";

void open_new_github_pr(void) {
    char command[180];
    sprintf(command, "open %s/pull/new/%s/%s\n", project_root, branch, directory);
    send_string(command);
}

void push_new_branch(void) {
    char command[65];
    sprintf(command, "git push -u origin %s\n", branch);
    send_string(command);
}

void open_branch_in_github(void) {
    char command[176];
    sprintf(command, "open %s/tree/%s/%s\n", project_root, branch, directory);
    send_string(command);
}

void open_in_github(void) {
    char command[92];
    sprintf(command, "open %s\n", project_root);
    send_string(command);
}
