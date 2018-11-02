/*
Michael Mroczka
CIS 3501
Professor Elenbogen
Code: Who Died - Program 2
Last updated: 10:51pm 02/18/15 to add all these nifty comments in
Purpose/Problem: To build a program that can dynamically build a hertiage tree
and then sort the tree into a premogentiure tree structure. This quickly allows
access to finding the next monarch of the throne and will also quickly calculate
the number of test cases asked and output the number of people that need to die in
order for a named heir to be crowned king.
Input: The first line should be an integer (p) indicating the number of CHILDREN that shall be
added to the tree. The second line should contain two strings and one char each separated by spaces. 
The first string (n) indicates the name of the parent of the following child. The second string (t)
indicates the name of the child. The third input (s) indicates the sex of child (t). These three pieces
of input are repeated (p) times until the tree has been built. Then, the user is to input an integer (q) 
indicating the number of following test cases. Finally, the user is to input (q) names to test for number
of deaths necessary to be the crowned king.
Output: The output is a NON-Sorted tree showing the chronological births of the monarchs child and children's 
children. Each generation is progressed by 5 spaces to show depth. Then a newline is outputted. Finally, for
however many queries were made, each query will give one integer per line indicating the number of deaths required
for the queried person to become king.
*/

#include <iostream>
#include <algorithm> //used for swap function even though VS2013 doesn't require it for that, you said to include it
#include <string>
#include <vector>
using namespace std;

struct TNode{
    string name;
    char sex;
    vector<TNode *> kids;
    TNode(string n = "defaultName", char s = 'm'){
        name = n;
        sex = s;
    }
};
class RoyalTree{
public:
    RoyalTree(TNode * rt = nullptr){root = rt;}//default constructor
    RoyalTree(RoyalTree & rhs){ //copy constructor that may or may not actually work
        if (root == nullptr)
            rhs.root = nullptr;
        copyRoyalTree(root, rhs.root);
    }
    void copyRoyalTree(TNode * orig, TNode* & copy){ //this actually copies the class
        if (orig == nullptr)
            copy = nullptr;
        else{
            copy = new TNode;
            copy->name = orig->name;
            copy->sex = orig->sex;
            for (size_t i = 0; i < orig->kids.size(); i++){
                TNode * addChildren = orig->kids[i];
                copy->kids.push_back(addChildren);
                copyRoyalTree(orig->kids[i], copy->kids[i]);
            }
        }
    }
    void insert(string parent, string child, char sex);
    int numToDie(string name);
    void sortBySex();
    void print();
private:
    TNode * root;
    void insert(TNode* &ptr, string parent, string child, char sex);
    int numToDie(TNode* ptr, string name, int & assassinationsNecessary, bool & located);
    void sortBySex(TNode* &ptr);
    void print(TNode * ptr, int spaces = 0);
};
void RoyalTree::insert(string parent, string child, char sex){
    /*
    ????name?? : insert()
        purpose: this is an alias function, and it just calls the insert function and passes the correct
                 parameters and does the brunt of the work
        pre????: assumes function has been called and root doesn't equal nullptr
        post?? : assumes tree is built from properly and parent was found in the tree
    */
    insert(root, parent, child, sex);
}
void RoyalTree::insert(TNode* &ptr, string parent, string child, char sex){
    /*                                     
    ????name?? : insert(TNode *, parent, child, sex)
        purpose: this function traverses the tree until it finds a match for the parent and
                 then adds the TNode element as the parents child
        pre????: assumes function has been called and root doesn't equal nullptr
        post?? : assumes tree is built from properly and parent was found in the tree
    */
    if (ptr == nullptr){
        ptr = new TNode;
        ptr->name = parent;
        ptr->kids.push_back(new TNode(child, sex));
    }
    else if (ptr->name == parent)
        ptr->kids.push_back(new TNode(child, sex));
    else{
        if (!ptr->kids.empty()){
            for (size_t i = 0; i < ptr->kids.size(); i++)
                insert(ptr->kids[i], parent, child, sex);
        }
    }
}
/*
//didn't end up needing this function...
TNode* RoyalTree::find(TNode * head, string parentToFind){
    TNode * currentParent;
    if (head == nullptr){
        cout << "something's fucked up if you see this" << endl;
        return nullptr;
    }
    //look at all of the kids, if they don't match, call the 
    else if (head->name == parentToFind){
        return head;
    }
    //      else if (head->kids.empty())
    //      return  nullptr;
    else if (head->kids.empty())
        return nullptr;
    else{
        for (int i = 0; i < head->kids.size(); i++){
            currentParent = find(head->kids[i], parentToFind);
            if (currentParent != nullptr) // && currentParent->name == parentToFind???
                return currentParent;
            if (currentParent == nullptr || currentParent->kids.empty())
                return nullptr;
        }// for
    } // end of else
}// end of find
*/
int RoyalTree::numToDie(string name){
    /*
    ????name?? : numToDie()
        purpose: this is an alias function, and it just calls the numToDie function and passes the correct
                 parameters and does the brunt of the work, it also default sets bool to false and int n to 0
        pre????: assumes function has been called and root doesn't equal nullptr
        post?? : assumes tree is built properly and name exists in the tree
    */

    bool start = false;
    int n = 0;
    return numToDie(root, name, n, start);
}
int RoyalTree::numToDie(TNode* ptr, string name, int & assassinationsNecessary, bool & located){
    /*
    ????name?? : numToDie()
        purpose: this function performs a PRE-ORDER traversal through the tree object and 
                 returns the number of people necessary to die for the said person to become heir
        pre????: assumes function has been called and root doesn't equal nullptr, also assumes boolean is
                 set to false as default int is 0
        post?? : assumes tree is built properly
        */
    int noMatch = 0;
    if (ptr->name == name){
        located = true;
        return 0;
    }
    else if (ptr->kids.empty()){
        return 0;
    }
    else{
        for (size_t i = 0; i < ptr->kids.size() && located == false; i++){
            noMatch += 1 + numToDie(ptr->kids[i], name, assassinationsNecessary, located);
        } //end of for loop
        assassinationsNecessary += noMatch;
        return noMatch;
    }//end else
}//ense numToDie
void RoyalTree::sortBySex(){
    /*
    ????name?? : sortBySex()
        purpose: this is an alias function, and it just calls the sortBySex function and passes the correct
        parameters and does the brunt of the work
        pre????: assumes function has been called and root doesn't equal nullptr
        post?? : assumes tree is built properly and destroys the tree, so you better not need to print it anymore
    */
    sortBySex(root);
}
void RoyalTree::sortBySex(TNode* &ptr){
    /*
    ????name?? : sortBySex(TNode *)
        purpose: this function takes a full tree and sorts it using the 1701 premogeniture rules of law
        pre????: assumes function has been called and root doesn't equal nullptr also assumes ptr can be changed
        post?? : assumes tree is built properly and destroys the tree, so you better not need to print it anymore as
                 you are passing by reference the ptr root
        */

    if (ptr == nullptr)
        cout << "\ntree is empty\n"; //this should never be seen
    else if (!ptr->kids.empty()){  // provided that kids vector isn't empty
        for (size_t i = 0; i < ptr->kids.size() - 1; i++){ // go through the vector...
            for (size_t j = 0; j < ptr->kids.size() - 1; j++){
                if (ptr->kids[j]->sex < ptr->kids[j+1]->sex) //... and sort the kids by sex m before f
                    swap(ptr->kids[j], ptr->kids[j+1]); // ... swap all required
            }
        }
        for (size_t i = 0; i < ptr->kids.size(); i++) // then if any of the kids have kids...
            sortBySex(ptr->kids[i]); //... call the swap function for them as well
    }
}
void RoyalTree::print(){
    /*
    ????name?? : print()
        purpose: this is an alias function, and it just calls the print function and passes the correct
                 parameters and does the brunt of the work
        pre????: assumes function has been called and root doesn't equal nullptr
        post?? : assumes tree is built properly and has children
    */
    print(root);
}
void RoyalTree::print(TNode * ptr, int spaces){
    /*
    ????name?? : print(TNode *, int)
        purpose: this function prints n Tnodes names. Each generation is advanced by 5 spaces
                 so that the program can similuate depth and provide quick refernce to children and grandchildren
        pre????: assumes function has been called and root doesn't equal nullptr, also assumes there IS a tree to print
        post?? : nothing as this doesn't do anything to the tree
    */
    if (ptr != nullptr){ // provided that it isn't end of tree...
        for (int i = 0; i < spaces; i++) // print as many spaces...
            cout << " "; // that are necessary
        cout << ptr->name << " " << ptr->sex << endl; //then print name
        spaces += 5;
        if (!ptr->kids.empty()){
            for (size_t i = 0; i < ptr->kids.size(); i++){
                print(ptr->kids[i], spaces);
            } //end for-loop print recursion
        }//end if statement checking that kids are empty
    }//end of if statement 
}
int main(){
    RoyalTree monarch;
    int numOfBirths, numOfQueries;
    char sex;
    string parent, child, newMonarch;
    
    cin >> numOfBirths;
    
    for (int i = 0; i < numOfBirths; i++){
        cin >> parent;
        cin >> child;
        cin >> sex;
        monarch.insert(parent, child, sex);
        //monarch.print(); used for debugging purposes
    }
    monarch.print();
    cout << endl;
    monarch.sortBySex();
    cin >> numOfQueries;
    for (int i = 0; i < numOfQueries; i++){
        cin >> newMonarch;
        cout << monarch.numToDie(newMonarch) << endl;
    }
    
    return 0;
}

