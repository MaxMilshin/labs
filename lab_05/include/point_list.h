#include "clist.h"

#ifndef POINT_LIST_H
#define POINT_LIST_H

struct point {
	int x, y;
	struct intrusive_node node;
};

void add_point(struct intrusive_list* list, int x, int y);

void remove_point(struct intrusive_list* list, int x, int y);

void remove_all_points(struct intrusive_list* list);

void show_all_points(struct intrusive_list* list);

void release_all_nodes(struct intrusive_node* cur_node);

#endif
