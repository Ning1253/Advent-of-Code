#include <stdio.h>  // For output, file I/O
#include <stdlib.h> // For memory alloc (malloc), exit()
#include <string.h> // For string copy, length, comparison

int totalsize = 0, minsize = 0x7fffffff, target = 0;

// Directory: Has a size, parent, and children - 
//  size will be later accounting for children in dirsize. 
typedef struct Dir {
    int size, childnum;
    struct Dir *parent, *children;
} Dir;

// Recursively calculate directory size by adding file size + sub-directory sizes. 
int dirsize(Dir *cwd) {
    for (int i = 0; i < cwd->childnum; i++) {
        cwd->size += dirsize(&cwd->children[i]);
    }

    return cwd->size;
}

// Recursively iterate through directories, checking all of them for the Part 1 and 2 conditions. 
void recurs(Dir cur) {
    if (cur.size <= 100000) totalsize += cur.size;
    if (cur.size >= target && cur.size < minsize) minsize = cur.size;

    for (int i = 0; i < cur.childnum; i++) 
        recurs(cur.children[i]);
}


int main() {
    FILE *fp = fopen("input.txt", "r");
    char buffer[50]; // Buffer for reading lines from the file. 

    // Root directory, set cwd to working directory. 
    Dir home = {0, 0, NULL, NULL};
    Dir *cwd = &home;

    // Skip first line which does what I just did above. 
    if (!fgets(buffer, 50, fp)) exit(1);

    // Loop to go through file. 
    while (fgets(buffer, 50, fp)) {
        // If "$ ls"
        if (buffer[2] == 'l') {
            if (!cwd->children) { // If cwd children have not yet been set...
                int counter = 0;

                while (fgets(buffer, 50, fp)) {
                    if (buffer[0] == '$') break;
                    else if (buffer[0] == 'd') counter += 1; // count the number of lines containing directory names.
                    else cwd->size += atoi(buffer); // Add filesize to directory's filesize
                }

                cwd->children = calloc(counter, sizeof(Dir)); //  enough memory to the children array for the directory. 
            }
        }

        // If "$ cd"
        if (buffer[2] == 'c') {
            // If "$ cd .." go to parent
            if (buffer[5] == '.') cwd = cwd->parent;
            // Else go to the next child directory. 
            else {
                cwd->children[cwd->childnum] = (Dir){0, 0, cwd, NULL};
                cwd = &cwd->children[cwd->childnum++];
            }
        }
    }

    dirsize(&home); // Recursively generate directory sizes by summing subdirectories and filesize
    target = home.size - 40000000;
    recurs(home); // Recursively calculate required info for homesize. 

    // Print output. 
    printf("%d\n", totalsize);
    printf("%d\n", minsize);
}