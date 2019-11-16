/*
* node for a queue data structure
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

typedef struct tree_node_s {
	char * name;
	int children;
	struct tree_node_s * offspring[];
} tree_node_t;

tree_node_t * create_node(char * name);

void destroy_tree(tree_node_t * tree);

tree_node_t * find_node(tree_node_t * tree, char * name);

void print_tree(tree_node_t * tree, char * name);

tree_node_t * add_child(tree_node_t * tree, char * parent_name, char * child_name);
