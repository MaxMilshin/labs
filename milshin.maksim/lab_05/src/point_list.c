#include "clist.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

struct point {
    int x, y;
    struct intrusive_node node;
};

void add_point(struct intrusive_list* list, int x, int y) {
    struct point* p = malloc(sizeof(struct point));
    assert(p);
    p->x = x;
    p->y = y;
    add_node(list, &p->node);
    return;
}

void remove_point(struct intrusive_list* list, int x, int y) {
    struct intrusive_node* cur_node = list->head;
    while (cur_node) {
        struct intrusive_node* next_node = cur_node->next;
        struct point* p = container_of(cur_node, struct point, node);
        if (p->x == x && p->y == y) { 
            remove_node(list, cur_node);
            free(p);
        }
        cur_node = next_node;
    }
}

void remove_all_points(struct intrusive_list* list) {
    struct intrusive_node* cur_node = list->head;
    while (cur_node) {
         struct intrusive_node* next_node = cur_node->next;
         remove_node(list, cur_node);
         struct point* p = container_of(cur_node, struct point, node);
         free(p);
         cur_node = next_node;
    }
}

void show_all_points(struct intrusive_list* list) {
    struct intrusive_node* cur_node = list->head;
    while (cur_node) {
        struct point* p = container_of(cur_node, struct point, node);
        printf("(%d %d) ", p->x, p->y);
        cur_node = cur_node->next;
    }
    printf("\n");
}

void release_all_nodes(struct intrusive_node* cur_node){
    if (cur_node) {
        release_all_nodes(cur_node->next);
        struct point* p = container_of(cur_node, struct point, node);
        free(p);
    }
}

/* int main() {
    struct intrusive_list list;
    init_list(&list);
    char command[10];
    int x, y;
    while (true) {
        scanf("%9s", command);
        if (strcmp(command, "add") == 0) {
            scanf("%d %d", &x, &y);
            add_point(&list, x, y);
        }
        else if (strcmp(command, "rm") == 0) {
            scanf("%d %d", &x, &y);
            remove_point(&list, x, y);
        }
        else if (strcmp(command, "print") == 0) 
            show_all_points(&list);
        else if (strcmp(command, "rma") == 0)
            remove_all_points(&list);
        else if (strcmp(command, "len") == 0)
            printf("%d\n", get_length(&list));
        else if (strcmp(command, "exit") == 0)
            break;
        else 
            printf("Unknown command\n");
    }
    release_all_nodes(list.head);
} */
