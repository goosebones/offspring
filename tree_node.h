/*
* node to represent entry in family tree
*
* @author Gunther Kroth   gdk6217@rit.edu
*/

/* tree node data structure*/
typedef struct tree_node_s {
	char * name;
	int children;
	int offSize;
	struct tree_node_s ** offspring;
} tree_node_t;

/*
* create a new tree_node_t
* node is allocated in memory
*
* @param name  name of person
* @return pointer to allocated tree_node
*/
tree_node_t * create_node(char * name);

/*
* destroy a node and all of its offspring
* node and all nodex below it are freed from memory
*
* @param tree  starting point in tree to destroy
*/
void destroy_tree(tree_node_t * tree);

/*
* print a formatted string of a node and its offspring
*
* @param tree  tree_node to print
*/
void print_offspring_line(tree_node_t * tree);

/*
* find a person in a tree
* performs a BFS on tree
*
* @param tree  tree to search in
* @param name  name of person to search for
* @return pointer to node of found person, if located in tree
*/
tree_node_t * find_node(tree_node_t * tree, char * name);

/*
* print a tree
* performs a BFS on tree and prints along the way
* used pring_offspring_line() as a helper
*
* @param tree  target tree to print
* @param name  person to start at in tree
*/
void print_tree(tree_node_t * tree, char * name);

/*
* add a child to a parent in the tree
*
* @param tree  tree to add a child in
* @param parent_name  name of parent to add child to
* @param child_name  name of child to be added
* @return pointer to newly created node for child_name
*/
tree_node_t * add_child(tree_node_t * tree, char * parent_name, char * child_name);

/*
* get the number of people in a tree
*
* @param tree  starting node to search from in tree
* @return number of people below starting position in tree
*/
int get_tree_size(tree_node_t * tree);

/*
* get the maximum height of a tree
*
* @param tree  starting node to seach from in tree
* @return greatest height below starting position in tree
*/
int get_tree_height(tree_node_t * tree);
