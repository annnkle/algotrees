#include <iostream>
#include <tgmath.h>
#include <algorithm>

using namespace std;

struct Node{
int value;
Node* parent = NULL;
Node* childL = NULL;
Node* childR = NULL;
int height = 0;
int bf = 0;
};

Node* root = NULL;
Node* node_NULL = NULL;

Node* add(Node* &, Node* ,int);
void new_node(Node* &, Node* &, int);
void add_from_list(int, int);
Node* search(int, Node*);
Node* create_balanced_tree(Node*, int);
void rotate_right(Node*& temp);
void rotate_left(Node*& temp);

void delete_node(Node* );
void postorder_delete(Node* node);

int tree_height(Node*);
int node_balance_factor(Node*);
void tree_balance_factor(Node*);
void check_if_avl(Node*);

void print_tree(Node*);
Node* find_root(Node* );

void tree_from_array();
void tree_from_array_recursion(int[], int, int, int, Node* );

Node* find_smallest(Node*);

void traverse_inorder(Node* node);
void traverse_preorder(Node* node);


int n=0;
int main()
{
    while( 1 == 1)
    {

        cout<<"1.Add element"<<endl;
        cout<<"2.Delete element"<<endl;
        cout<<"3.Search for an element"<<endl;
        cout<<"4.Traverse tree"<<endl;
        cout<<"5.Delete tree post-order"<<endl;
        cout<<"6.Create tree from array"<<endl;
        cout<<"7.Show tree"<<endl;
        cout<<"8.Balance the tree"<<endl;
        int choice;
        cout<<"Choice: ";
        cin>>choice;
        int w;


        switch(choice){

            case 1:{
				cout<<"Enter value: ";
				cin>>w;
				cout<<endl;
				if(add(root, NULL, w) != NULL)
					n++;
				break;
            }

            case 2:{
				cout<<"Enter value for deletion: ";
				cin>>w;

				Node* deleted = search(w, root);

				if(deleted != NULL)
					cout << "Deleting node of value: " << deleted->value<<endl;

				delete_node(deleted);
				break;
            }

            case 3:{
				cout<<"Enter searched value: ";
				cin>>w;
				Node* searched = search(w, root);
				if(searched != NULL)
					cout << searched->value<<endl;
				break;
            }

            case 4:{
				cout<< "Inorder" << endl;
				traverse_inorder(root);
				cout<<"\b\b\b"<<"  "<<endl;
				cout << "Preorder" << endl;
				traverse_preorder(root);
				cout<<"\b\b\b"<<"  "<<endl;
				cout<<"\n";
				break;
            }

            case 5:{
				postorder_delete(root);
				break;
            }

            case 6:{
				tree_from_array();
				break;
            }

            case 7:{
				print_tree(root);
				break;
            }
            case 8:
				check_if_avl(root);
				break;
        }
    }
    return 0;
}
Node* add(Node* &temp,Node* parent, int w){
    if (root == NULL){
        //parent = NULL;
        new_node(temp, parent, w);
        root->height=0;
    }


    if(temp == NULL){
    new_node(temp, parent, w);
    return temp;
    }
    if(w<temp->value){
       parent = temp;
       temp->childL = add(temp->childL, parent,  w);}
    else if(w>temp->value){
        parent = temp;
        temp->childR = add(temp->childR, parent, w);}

    return temp;

}
void new_node(Node* &temp, Node* &parent, int w)
{

    temp = new Node;
    temp->value = w;
    temp->childL = NULL;
    temp->childR = NULL;
    temp->parent = parent;
    if(parent != NULL)
        temp->height = (parent->height)+1;
}


void add_from_list(int n, int list[]){
	int i;
	for(i = 0; i < n; i++){
		add(root, NULL, list[i]);
	}
}


Node* search(int w, Node* where_is_it){
    // No such node 
    if(where_is_it == NULL){
        cout << "No such node in the tree." << w << endl;
        return NULL;
    }
    if(w != where_is_it->value){
        cout<<where_is_it->value<<endl;

        if(where_is_it->childL == NULL && where_is_it->childR == NULL){
            cout<<"No node of this value in the tree."<<endl;
            return NULL;
        }

        if(w<where_is_it->value){
            cout<<"/"<<endl;
            where_is_it = search(w, where_is_it->childL);
        }
        if(w>where_is_it->value){
            cout<<"\\"<<endl;
            where_is_it = search(w, where_is_it->childR);
        }
    }


    return where_is_it;

}


void delete_node(Node* deleted){

    if(deleted == NULL){
        cout<<"No node of this value in the tree."<<endl;
        return;
    }
    //root
    if(deleted->parent == NULL){
            if( (root->childL == NULL)  && (root->childR == NULL) )
            {
                root = NULL;
                return;
            }

            if(root->childR != NULL)
            {
                Node *successor = find_smallest(deleted->childR);
                successor -> parent = NULL;
                successor -> childL = deleted -> childL;
                successor -> childR = deleted -> childR;
                (deleted -> childL) -> parent = successor;
                (deleted -> childR) -> parent = successor;
                root = successor;
                deleted = NULL;
            }

            else{
                root = deleted->childL;
                root->parent =NULL;
            }
      n--;
      return;
    }
    //lisc
    else if(deleted->childL == NULL && deleted->childR == NULL){

        //deleted on the left
        if(deleted == (deleted->parent)->childL){
            (deleted->parent)->childL = NULL;
        }
        //deleted on the right
        else if(deleted == (deleted->parent)->childR){
            (deleted->parent)->childR = NULL;
        }
        n--;
        return;
    }


    //basic node
    else{
        //only right child

        if(deleted->childL == NULL && deleted->childR != NULL){

            // deleted is a left child
            if(deleted == (deleted->parent)->childL){
                (deleted->parent)->childL = deleted -> childR;
                (deleted->childR)->parent = deleted->parent;
                 deleted = NULL;
            }

            // deleted is a right child
            else if(deleted == (deleted->parent)->childR){
                (deleted->parent)->childR = deleted -> childR;
                (deleted->childR)->parent = deleted->parent;
                 deleted = NULL;
            }
        }
		
        //just left
        else if(deleted->childL != NULL && deleted->childR == NULL){
				// deleted is a left child
                 if(deleted == (deleted->parent)->childL){
                    (deleted->parent) -> childL = deleted -> childL;
                    (deleted->childL) -> parent = deleted -> parent;
                    deleted = NULL;
                }

				// deleted is a right child
                else if(deleted == (deleted->parent)->childR){
                    (deleted->parent) -> childR = deleted -> childL;
                    (deleted->childL)->parent = deleted -> parent;
                    deleted = NULL;
                }
        }
		
        //both
        else if(deleted->childL != NULL && deleted->childR != NULL){
                Node *successor = find_smallest(deleted->childR);///

                // if successor is a left child, make parent not point at it anymore
                if( successor == successor->parent->childL )
                {
                    successor->parent->childL = NULL;
                    successor->childR = deleted ->childR;
                    (deleted->childR)->parent = successor;
                }

                // if successor is a right child,
                else if( successor == successor->parent->childR )
                {
					successor->parent = deleted->parent; //
					successor->childL = deleted ->childL;    //
					(deleted->childL)->parent = successor; //
                }
				
                // move parent's pointer to successor
                if(deleted == (deleted->parent)->childL)
                    (deleted->parent)->childL = successor;
                else if(deleted == (deleted->parent)->childR)
                    (deleted->parent)->childR = successor;
                deleted=NULL;
            }
        n--;
        return;
        }
}

Node* find_smallest(Node* which_node){
    Node *smallest = which_node;
    while(smallest->childL != NULL){
        smallest = smallest->childL;

    }
    return smallest;
}

Node* create_balanced_tree(Node* temp, int n){
//create trunk
    temp = root;
    while(temp!=NULL){

        root = find_root(temp);
        if(temp->childL != NULL){

            rotate_right(temp);
            temp = temp->parent;

            root = find_root(temp);

        }
        else{
            temp= temp->childR;
        }
    }


    cout << "TRUNK CREATED : " <<root->value << endl;
    print_tree(root);


    ///create balanced tree

    cout<<"CREATE A BALANCED TREE FROM TRUNK BY LEFT ROTATIONS"<<endl;

    int x = floor(log2(n+1));
    int m = pow(2, x) - 1;
    int i;

    temp = root;
    for(i = 0;i<(n-m);i++){

        cout << "BEFORE LEFT ROTATION"<<endl;
        print_tree(root);

        rotate_left(temp);
        root = find_root(temp);



        cout << "AFTER LEFT ROTATION"<<endl;
        print_tree(root);


        temp = temp->parent->childR;

    }
    temp = root;
    while(m>1){
        m/=2;

        temp = root;
        for(i = 0; i < m; i++){


            cout << "BEFORE LEFT ROTATION"<<endl;
            print_tree(root);

            rotate_left(temp);
            root = find_root(temp);



            cout << "AFTER LEFT ROTATION"<<endl;
            print_tree(root);

            temp = temp->parent->childR;
        }
    }


    cout<<"BALANCED TREE"<<endl;
    print_tree(root);
	
	return 0;
}

void rotate_right(Node*& temp)
{

    if(new_node != NULL)
    {
        Node* new_node = temp->childL;
        Node* temp_parent = temp->parent;
        Node* new_node_R_child = ((temp->childL)->childR);

        if(temp_parent != NULL)
        {
            if(temp == temp->parent->childL)
                temp_parent->childL = new_node;
            else if(temp == temp->parent->childR)
                temp_parent->childR = new_node;
        }
        temp->parent = new_node;
        new_node->parent = temp_parent;

        temp->childL = new_node_R_child;
        if(new_node_R_child != NULL)
            new_node_R_child->parent = temp;
        new_node->childR = temp;
    }
}


void rotate_left(Node*& temp)
{
    Node* new_node = temp->childR;

    if(new_node != NULL)
    {
        Node* temp_parent = temp->parent;
        Node* new_node_L_child = new_node->childL;

        if(temp_parent != NULL)
        {
            if(temp == temp->parent->childL)
                temp_parent->childL = new_node;
            else if(temp == temp->parent->childR)
                temp_parent->childR = new_node;
        }
        temp->parent = new_node;
        new_node->parent = temp_parent;
        temp->childR = new_node_L_child;
        if(new_node_L_child != NULL)
            new_node_L_child->parent = temp;
        new_node->childL = temp;
    }
}


int tree_height(Node* node)
{
    if( node == NULL )
    {
        return 0;
    }
    int left_subtree_height =  tree_height(node->childL);
    int right_subtree_height = tree_height(node->childR);
    return max(left_subtree_height, right_subtree_height) + 1;
}


int node_balance_factor(Node* node)
{
    return tree_height(node->childL) - tree_height(node->childR);
}



void tree_balance_factor(Node* tree_root)
{
    // determine balance factor for every tree node
    if(tree_root != NULL)
    {
        tree_root->bf = node_balance_factor(tree_root);
        tree_balance_factor(tree_root->childL);
        tree_balance_factor(tree_root->childR);
    }
}




void check_if_avl(Node* tree_root)
{
    if (tree_root != NULL)
    {
        tree_balance_factor(tree_root);
        if( (tree_root->bf != -1) && (tree_root->bf != 0) && (tree_root->bf != 1) )
        {
            create_balanced_tree(tree_root, n);
        }
        else
        {
            check_if_avl(tree_root->childL);
            check_if_avl(tree_root->childR);
        }
    }
}



void print_tree(Node* node)
{
    if(node != NULL)
    {

        cout << node->value<<endl;

        if(node->childL != NULL)
            cout << "/";
        if(node->childR != NULL)
            cout <<"\\";

        cout << "\n";


        if(node->childL != NULL)
            print_tree(node->childL);
        if(node->childR != NULL)
            print_tree(node->childR);
    }
    else
    {
        cout << "NULL" << endl;;
    }

}



Node* find_root(Node* node)
{
    if(node != NULL)
    {
        if(node->parent == NULL)
        {
            return node;
        }
        else
        {
            return find_root(node->parent);
        }
    }
	return NULL;
}


void postorder_delete(Node* node){
    if(node != NULL)
    {
        postorder_delete(node->childL);
        postorder_delete(node->childR);
        if(node->parent!=NULL){
            if(node==(node->parent)->childL){
                (node->parent)->childL = NULL;
            }
            else if(node==(node->parent)->childR){
                (node->parent)->childR = NULL;
            }
        }
        else{
            root = NULL;
        }
    }
}
void tree_from_array(){

    int i, x, m;
    cout<<"Enter the length of an array: ";
    cin>>m;
    int array[m];
    for(i = 0;i < m; i++){
        cout<<"Enter value of a node "<<i<<": ";
        cin>>x;
        array[i] = x;
    }

    std::sort(array, array + m);	

    int root_ind = (m-1) / 2;
    root = new Node;
    root->value = array[root_ind];
    tree_from_array_recursion(array, 0, m-1, root_ind,  root);

}

void tree_from_array_recursion(int array[], int p, int q, int parent_ind, Node* parent){


    if( (p < q) && (parent != NULL) ){



        int L_child_ind = (p + parent_ind) / 2;


        if( (L_child_ind >= p) && (L_child_ind < parent_ind) )
        {
            // create L child
            add(root, parent, array[L_child_ind]);
        }

        int R_child_ind = ceil((float)(parent_ind + q)/2);


        if( (R_child_ind <= q) && (R_child_ind > parent_ind) )
        {
           // create R child
            add(root, parent, array[R_child_ind]);
        }

        // recursion
        tree_from_array_recursion(array, p, parent_ind-1, L_child_ind, parent->childL);
        tree_from_array_recursion(array, parent_ind+1, q, R_child_ind, parent->childR);

    }
}

void traverse_inorder(Node* node)
{
    if(node != NULL)
    {
        traverse_inorder(node->childL);
        cout<<node->value<<" -> ";
        traverse_inorder(node->childR);
    }

}

void traverse_preorder(Node* node)
{
    if(node != NULL)
    {
        cout<<node->value<<" -> ";
        traverse_preorder(node->childL);
        traverse_preorder(node->childR);
    }

}
