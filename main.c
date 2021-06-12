#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "./heap.h"

#define JIM_IMPLEMENTATION
#include "jim.h"

typedef struct Node Node;

struct Node {
    char x;
    Node *left;
    Node *right;
};

Node *generate_tree(size_t level_cur, size_t level_max)
{
    if (level_cur < level_max) {
        Node *root = heap_alloc(sizeof(*root));
        assert((char) level_cur - 'a' <= 'z');
        root->x = level_cur + 'a';
        root->left = generate_tree(level_cur + 1, level_max);
        root->right = generate_tree(level_cur + 1, level_max);
        return root;
    } else {
        return NULL;
    }
}

void print_tree(Node *root, Jim *jim)
{
    if (root != NULL) {
        jim_object_begin(jim);

        jim_member_key(jim, "value");
        jim_string_sized(jim, &root->x, 1);

        jim_member_key(jim, "left");
        print_tree(root->left, jim);

        jim_member_key(jim, "right");
        print_tree(root->right, jim);

        jim_object_end(jim);
    } else {
        jim_null(jim);
    }
}

#define N 10

void *ptrs[N] = {0};

int main()
{
    Node *root = generate_tree(0, 3);

    Jim jim = {
        .sink = stdout,
        .write = (Jim_Write) fwrite,
    };

    print_tree(root, &jim);

    printf("------------------------------\n");

    size_t heap_ptrs_count = 0;
    for (size_t i = 0; i < alloced_chunks.count; ++i) {
        for (size_t j = 0; j < alloced_chunks.chunks[i].size; ++j) {
            uintptr_t *p = (uintptr_t*) alloced_chunks.chunks[i].start[j];
            if (heap <= p && p < heap + HEAP_CAP_WORDS) {
                printf("DETECTED HEAP POINTER: %p\n", (void*) p);
                heap_ptrs_count += 1;
            }
        }
    }

    printf("Detected %zu heap pointers\n", heap_ptrs_count);

    return 0;
}
