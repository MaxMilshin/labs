#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "point_list.h"

void savetext(struct intrusive_node* cur_node, void* data) {
  struct point* p = container_of(cur_node, struct point, node);
  fprintf((FILE*) data, "%d %d\n", p->x, p->y);
}

void savebin(struct intrusive_node* cur_node, void* data) {
  struct point* p = container_of(cur_node, struct point, node);
  fwrite(&(p->x), 3, 1, (FILE*) data);
  fwrite(&(p->y), 3, 1, (FILE*) data);
}

void print(struct intrusive_node* cur_node, void* data) {
  struct point* p = container_of(cur_node, struct point, node);
  printf((char*) data, p->x, p->y);
}

void plus_one(struct intrusive_node* cur_node, void* data) {
  (*((int *) data))++;
}

void apply(struct intrusive_list* list, void (*op)(struct intrusive_node* node, void* data), void* data) {
  struct intrusive_node* cur_node = list->head;
  while (cur_node) {
    op(cur_node, data);
    cur_node = cur_node->next;
  }
}

int main(int argc, char* argv[]) {
  struct intrusive_list list;
  init_list(&list);
  FILE* in_file = fopen(argv[2], "r");
  assert(in_file);
  while (!feof(in_file)) {
    int x, y;
    if (strcmp(argv[1], "loadtext") == 0)
      fscanf(in_file, "%d %d\n", &x, &y);
    if (strcmp(argv[1], "loadbin") == 0) {
      fread(&x, 3, 1, in_file);
      fread(&y, 3, 1, in_file);
    }
    add_point(&list, x, y);
  }
  fclose(in_file);
  reverse_list(&list);
  if (strcmp(argv[3], "savetext") == 0 || strcmp(argv[3], "savebin") == 0) {
    FILE* out_file = fopen(argv[4], "w");
    assert(out_file);
    if (strcmp(argv[3], "savetext") == 0)
      apply(&list, savetext, out_file);
    else
      apply(&list, savebin, out_file);
    fclose(out_file);
  }
  if (strcmp(argv[3], "print") == 0) { 
    apply(&list, print, argv[4]);
    printf("\n");
  }
  if (strcmp(argv[3], "count") == 0) {
    int count = 0;
    apply(&list, plus_one, &count);
    printf("%d\n", count);
  }
  remove_all_points(&list);
}
