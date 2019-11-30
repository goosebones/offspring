/*
* node to represent entry in family tree
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

typedef struct tree_node_s {
	char * name;
	int children;
	int offSize;
	struct tree_node_s ** offspring;
} tree_node_t;

tree_node_t * create_node(char * name);

void destroy_tree(tree_node_t * tree);

void print_offspring_line(tree_node_t * tree);

tree_node_t * find_node(tree_node_t * tree, char * name);

void print_tree(tree_node_t * tree, char * name);

tree_node_t * add_child(tree_node_t * tree, char * parent_name, char * child_name);

int get_tree_size(tree_node_t * tree);

int get_tree_height(tree_node_t * tree);
