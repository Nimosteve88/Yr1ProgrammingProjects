#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>

struct TreeNode;
struct EdgeNode;
 
typedef std::string tree_t;
 
struct EdgeNode{
    tree_t val;
    TreeNode* subtree;
    EdgeNode* next;
};
 
struct TreeNode{
    tree_t val;
    EdgeNode* subtree_l;
};


class A3Tree{
 
// there will be other code here
public:
    A3Tree(const std::vector<std::vector<std::string>> data){ //construction of the tree
        std::vector<TreeNode*> treenodelist;
        const std:: vector<std::string> rootlist = data[0]; 
        int x = rootlist.size()-2;  

        treenodelist.push_back(build_tree_root(rootlist[rootlist.size()-1])); 

        while(x >= 0){ 
            TreeNode*t1 = build_tree_root(rootlist[x]);
            if(x==rootlist.size()-2){ 
                for(int i=1; i< data.size(); i++){ 
                    if(inEdgeNode(t1->subtree_l, data[i][x]) == false){
                        TreeNode* tmp = createCopyOfTreeNode(treenodelist[treenodelist.size()-1]); 
                        (t1->subtree_l) = cons_edge_node(tmp,data[i][x],t1->subtree_l);
                }
            }
            treenodelist.push_back(t1);
            }else{ 
                for(int i=1; i< data.size(); i++){
                    if(inEdgeNode(t1->subtree_l, data[i][x]) == false){
                    
                        TreeNode* tmp = createCopyOfTreeNode(treenodelist[treenodelist.size()-1]);
                        (t1->subtree_l) = cons_edge_node(tmp,data[i][x],t1->subtree_l);
                }
            }
                treenodelist.push_back(t1);
            }
            x -= 1;
        } 

        t = treenodelist[treenodelist.size()-1]; 
        
        

        // Now assigning the different qualities
        for(int i=1; i< data.size(); i++){ 
            std:: vector <std:: string> conditions = data[i];
            const std:: string c = conditions[(conditions.size())-1]; 
            std:: vector <TreeNode*> subtreelist; 
            x = 0;
            while(x < conditions.size()-1){ 
                 if(x==0){
                    TreeNode* subnode = find_subnode(conditions[x],t);
                    if(subnode != nullptr){
                        subtreelist.push_back(subnode);
                    }
                 }else{
                    TreeNode* subnode = find_subnode(conditions[x], subtreelist[(subtreelist.size())-1]);
                    subtreelist.push_back(subnode);
                 }
                 x += 1;
            }
            subtreelist[(subtreelist.size())-1]->val = c;
        }

      std:: string nonfeature = rootlist[(rootlist.size())-1];
      delete_node(nonfeature, t, true); 
      
      
      int y = rootlist.size()-2;
      while(y >= 0){
        delete_node(rootlist[y], t, false);
        y -= 1;
      }

        
        
    }

    //Destructor function
    ~A3Tree(){
        deallocateTree(t);
    }
    //Deallocation functions
    void deallocateTree(TreeNode* node) {
    if (node != nullptr) {
        deallocateEdgeList(node->subtree_l);
        delete node;
        }
    }

    void deallocateEdgeList(EdgeNode* edge) {
        if (edge != nullptr) {
            deallocateEdgeList(edge->next);
            deallocateTree(edge->subtree);
            delete edge;
        }
    }
    
    // Copies the content of a Treenode and its Edgenodes into a new memory address
    TreeNode* createCopyOfTreeNode(const TreeNode* node) {
    if (node == nullptr) {
        return nullptr;
    }

    TreeNode* newNode = allocate_tree_node(node->val);

    if (node->subtree_l != nullptr) {
        EdgeNode* currentEdgeNode = node->subtree_l;
        EdgeNode* copiedEdgeNode = cons_edge_node(createCopyOfTreeNode(currentEdgeNode->subtree), currentEdgeNode->val, nullptr);
        newNode->subtree_l = copiedEdgeNode;

        currentEdgeNode = currentEdgeNode->next;
        while (currentEdgeNode != nullptr) {
            copiedEdgeNode->next = cons_edge_node(createCopyOfTreeNode(currentEdgeNode->subtree), currentEdgeNode->val, nullptr);
            copiedEdgeNode = copiedEdgeNode->next;
            currentEdgeNode = currentEdgeNode->next;
        }
    }

    return newNode;
}

    //Finds and returns the memory address of the subtree belonging to the edgenode of value e
    TreeNode* find_subnode(tree_t e, TreeNode* t){
    /// e = EdgeNode Value           t = TreeNode containing the EdgeNode we're searching for
    ///This function is expected the return the subtree node of the corresponding edgenode
    EdgeNode* edgelist = t->subtree_l;
    
    while(edgelist!=nullptr){
            if((edgelist->val) == e){
                return edgelist->subtree;
            }
            edgelist = edgelist ->next;
        }
    return nullptr;
    
    }

    // Checks if an Edgenode of value e already exists within the linked list of Edgenodes
    bool inEdgeNode(EdgeNode* l, tree_t e){ // checks if the edgenode isn't already present
        bool counter = false;
        EdgeNode* list = l;
        while(list!=nullptr){
            if((list->val) == e){
                counter = true;
            }
            list = list ->next;
        }
        return counter;
    }
    
    //deletes any Treenode that has the value e
    void delete_node(tree_t e,TreeNode*& t, bool nonfeature){ 
    if(t != nullptr){
        EdgeNode* it = t->subtree_l;
        while(it != nullptr){
            if(nonfeature == true){
                delete_node(e ,it->subtree, true);
            }else{
                delete_node(e, it->subtree, false);
            }
            it = it->next;
        }
        if(t->val == e){
          if(nonfeature == true){
            delete t;
            t = nullptr;
            }else{
            if(subtreecount(t) == 0){
                delete t;
                t = nullptr;
            }
            
        } 
        }
        }
    }


    TreeNode* allocate_tree_node(tree_t e){
        TreeNode* tmp = new TreeNode;
        tmp->val = e;
        tmp->subtree_l = nullptr;
        return tmp;
        }
 
    EdgeNode* cons_edge_node(TreeNode* t, tree_t value,EdgeNode* subtree_l){
        EdgeNode* tmp = new EdgeNode;
        tmp->val = value;
        tmp->subtree = t;
        tmp->next = subtree_l;
        return tmp;
    }
    
    
 
    TreeNode* build_tree_root(tree_t e){
        return allocate_tree_node(e);
    }

    //Query function will repeatedly return the memory address of the subtree belonging to each condition and in the end the last subtree (the condition we're looking
    // for) will be returned
    tree_t query(std::vector<std::string> info){
        
        std:: vector <TreeNode*> subtreelist; 
        int x = 0;
        while(x < info.size()){ 
            if(x==0){
                TreeNode* subnode = find_subnode(info[x],t);
                if(subnode != NULL){
                    subtreelist.push_back(subnode);
                    }
                }else{
                    TreeNode* subnode = find_subnode(info[x], subtreelist[(subtreelist.size())-1]);
                    subtreelist.push_back(subnode);
                 }
                 x += 1;
            } 
            return subtreelist[(subtreelist.size())-1]->val;
    }

    //Count
    int node_count(){
        int nodes = count_nodes(t);
        return nodes;
    }

    int count_nodes(const TreeNode* t){
    if(t ==nullptr){
        return 0;
    }
    else if(subtreecount(t) == 1){ 
      return 1;
    }
    else{
        int node_count = 1;
        EdgeNode* it = t->subtree_l;
        while(it != nullptr){
            node_count += count_nodes(it->subtree);
            it = it->next;
        }
        return node_count;
    }
}
    // Counts the number of the subtrees the Treenode t contains. I mainly used this to eliminate scenarios like rain->yes->good
    int subtreecount(const TreeNode* t){
      int num = 0;
      EdgeNode* it = t->subtree_l;
      while(it != nullptr){
        if(it->subtree != nullptr){
          num += 1;
        }
        it = it->next;
      }
      return num;
    }
    

/// this function returns the number of leaf nodes in the tree (whose root is) t
/// (see also example of expected output below)
  int leaf_node_count(){
    return count_leaf_nodes(t);
  }   
  
  int count_leaf_nodes(TreeNode* t){
    if(t==nullptr){
        return 0;
    }
    if(t->subtree_l == nullptr){
        return 1;
    }
    int leaf_count = 0; 
    EdgeNode* it = t->subtree_l;
    while(it != nullptr){
        leaf_count += count_leaf_nodes(it->subtree);
        it = it->next;
        }

    return leaf_count;
}
private:
 
    TreeNode* t;
};


int main(){
 
    std::vector<std::vector<std::string>> input1
    {
        {"temperature", "rain", "wind", "quality"},
        {"high", "yes", "light", "acceptable"},
        {"low", "yes", "light", "acceptable"},
        {"low", "no", "moderate", "good"},
        {"high", "yes", "strong", "poor"},
        {"high", "yes", "moderate", "acceptable"},
        {"high", "no", "moderate", "good"},
        {"low", "yes", "strong", "poor"},
        {"high", "no", "light", "good"},
        {"low", "yes", "moderate", "poor"},
        {"high", "no", "strong", "poor"}
    };
 
    std::vector<std::vector<std::string>> input2
    {
        {"Feature_3", "feature2", "feature", "feature0", "not_a_feature"},
        {"a13480", "10", "a13480", "a", "1"},
        {"B_34203", "9", "1343432", "a", "a2"},
        {"a13480", "8", "57657", "a", "3"},
        {"B_34203", "6", "4523", "a", "some_value"},
        {"a13480", "5", "4523", "a", "1"}
    };
 
    A3Tree t1(input1);
    A3Tree t2(input2);
 
    std::vector<std::string> q;
 
    q = {"B_34203", "9", "1343432", "a"};
    std::cout << t2.query(q) << std::endl;
    // this should print: a2
    std:: cout << t2.node_count() << std:: endl;
    // this should print: 8
    std:: cout << t2.leaf_node_count() << std:: endl;
    // this should print: 5
    
    
    q =  {"high", "yes", "moderate"};
    std::cout << t1.query(q) << std::endl;
    // this should print: acceptable
    std:: cout << t1.node_count() << std:: endl;
    // this should print 16
    std:: cout << t1.leaf_node_count() << std:: endl;
    // this should print 10
}