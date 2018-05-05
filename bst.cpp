
/* BST.h contains the declaration of class template BST.
 Basic operations:
 Constructor: Constructs an empty BST
 isEmpty:       Checks if a BST is empty
 contains:      Search a BST for an item
 add:         Adds a value into a BST
 remove:      Removes a value from a BST
 inorder:     Inorder traversal of a BST -- output the item values
 graph:       Output a grapical representation of a BST
 Private utility helper operations:
 search2:     Used by delete
 inorderAux:  Used by inorder
 graphAux:    Used by graph
 Other operations described in the exercises:
 destructor
 copy constructor
 assignment operator
 preorder, postorder, and level-by-level traversals
 level finder
 Note: Execution terminates if memory isn't available for a new BST node.
 ---------------------------------------------------------------------------*/

#include <iostream>


//--- Definition of constructor
template <typename ItemType>
BST<ItemType>::BST()
: myRoot(nullptr)
{}

template<class ItemType>
BST<ItemType>::~BST()
{
    destroyTree(myRoot);
}  // end destructor

template<class ItemType>
void BST<ItemType>::destroyTree(BinaryNode<ItemType> *subTreePtr)
{
    if (subTreePtr != nullptr)
    {
        destroyTree(subTreePtr->getLeftChildPtr());
        destroyTree(subTreePtr->getRightChildPtr());
        delete subTreePtr;
        subTreePtr = nullptr;
    }  // end if
}  // end destroyTree

//--- Definition of empty()
template <typename ItemType>
bool BST<ItemType>::isEmpty() const
{ return myRoot == nullptr; }

//--- Definition of contains()
template <typename ItemType>
bool BST<ItemType>::contains(const ItemType & anItem) const
{
	return search(anItem);
}

//--- Definition of search()
template <typename ItemType>
bool BST<ItemType>::search(const ItemType & anItem) const
{
    BinaryNode<ItemType> *locptr = myRoot;
    bool found = false;
    while (!found && locptr != nullptr)
    {
        if (anItem < locptr->getItem())       // descend left
            locptr = locptr->getLeftChildPtr();
        else if (locptr->getItem() < anItem)  // descend right
            locptr = locptr->getRightChildPtr();
        else                           // item found
            found = true;
    }
    return found;
}

//--- Definition of add()
template <typename ItemType>
bool BST<ItemType>::add(const ItemType & anItem)
{
    BinaryNode<ItemType>* locptr = myRoot;   // search pointer
    BinaryNode<ItemType>* parent = nullptr;        // pointer to parent of current node
    bool found = false;     // indicates if anItem already in BST
    while (!found && locptr != nullptr)
    {
        parent = locptr;
        if (anItem < locptr->getItem())       // descend left
            locptr = locptr->getLeftChildPtr();
        else if (locptr->getItem() < anItem)  // descend right
            locptr = locptr->getRightChildPtr();
        else                           // anItem found
            found = true;
    }
    if (!found)
    {                                 // construct node containing anItem
        locptr = new BinaryNode<ItemType>(anItem);
        if (parent == nullptr)               // empty tree
            myRoot = locptr;
        else if (anItem < parent->getItem() )  // insert to left of parent
            parent->setLeftChildPtr(locptr);
        else                           // insert to right of parent
            parent->setRightChildPtr(locptr);
    }
    return found;
}

//--- Definition of remove()
template <typename ItemType>
bool BST<ItemType>::remove(const ItemType & anItem)
{
    bool found;                      // signals if anItem is found
    BinaryNode<ItemType>* x;                            // points to node to be deleted
    BinaryNode<ItemType>* parent;                       //    "    " parent of x and xSucc
    search2(anItem, found, x, parent);
    
    if (!found)
    {
        return false;
    }
    //else
    if (x->getLeftChildPtr() != nullptr && x->getRightChildPtr() != nullptr)
    {                                // node has 2 children
        // Find x's inorder successor and its parent
        BinaryNode<ItemType> *xSucc = x->getRightChildPtr();
        parent = x;
        while (xSucc->getLeftChildPtr() != nullptr)       // descend left
        {
            parent = xSucc;
            xSucc = xSucc->getLeftChildPtr();
        }
        
        // Move contents of xSucc to x and change x
        // to point to successor, which will be removed.
        x->setItem(xSucc->getItem());
        x = xSucc;
    } // end if node has 2 children
    
    // Now proceed with case where node has 0 or 2 child
    BinaryNode<ItemType>* subtree = x->getLeftChildPtr();             // pointer to a subtree of x
    if (subtree == nullptr)
        subtree = x->getRightChildPtr();
    if (parent == nullptr)                  // root being removed
        myRoot = subtree;
    else if (parent->getLeftChildPtr() == x)       // left child of parent
        parent->setLeftChildPtr(subtree);
    else                              // right child of parent
        parent->setRightChildPtr(subtree);
    delete x;
    
    return true;
}

//--- Definition of inorder()
template <typename ItemType>
void BST<ItemType>::inorder(ostream & out) const
{
    inorderAux(out, myRoot);
}

//--- Definition of preorder()
template <typename ItemType>
void BST<ItemType>::preorder(ostream & out) const
{
    preorderAux(out, myRoot);
}

//--- Definition of postorder()
template <typename ItemType>
void BST<ItemType>::postorder(ostream & out) const
{
    postorderAux(out, myRoot);
}

//--- Definition of graph()
template <typename ItemType>
void BST<ItemType>::graph(ostream & out) const
{ graphAux(out, 0, myRoot); }

//--- Definition of search2()
template <typename ItemType>
void BST<ItemType>::search2(const ItemType & anItem, bool & found,
                            BinaryNode<ItemType>* & locptr,
                            BinaryNode<ItemType>* & parent) const
{
    locptr = myRoot;
    parent = nullptr;
    found = false;
    while (!found && locptr != nullptr)
    {
        if (anItem < locptr->getItem())       // descend left
        {
            parent = locptr;
            locptr = locptr->getLeftChildPtr();
        }
        else if (locptr->getItem() < anItem)  // descend right
        {
            parent = locptr;
            locptr = locptr->getRightChildPtr();
        }
        else                           // anItem found
            found = true;
    }
}

//--- Definition of inorderAux()
template <typename ItemType>
void BST<ItemType>::inorderAux(ostream & out,
                               BinaryNode<ItemType>* subtreeRoot) const
{
    if (subtreeRoot != nullptr)
    {
        inorderAux(out, subtreeRoot->getLeftChildPtr());    // L operation
        out << subtreeRoot->getItem() << "  ";      // V operation
        inorderAux(out, subtreeRoot->getRightChildPtr());   // R operation
    }
}

//--- Definition of preorderAux()
template <typename ItemType>
void BST<ItemType>::preorderAux(ostream & out,
                               BinaryNode<ItemType>* subtreeRoot) const
{
    if (subtreeRoot != nullptr)
    {
        preorderAux(out, subtreeRoot->getLeftChildPtr());    // L operation
        out << subtreeRoot->getItem() << "  ";      // V operation
        preorderAux(out, subtreeRoot->getRightChildPtr());   // R operation
    }
}

//--- Definition of postorderAux()
template <typename ItemType>
void BST<ItemType>::postorderAux(ostream & out,
                               BinaryNode<ItemType>* subtreeRoot) const
{
    if (subtreeRoot != nullptr)
    {
        postorderAux(out, subtreeRoot->getLeftChildPtr());    // L operation
        out << subtreeRoot->getItem() << "  ";      // V operation
        postorderAux(out, subtreeRoot->getRightChildPtr());   // R operation
    }
}

//--- Definition of graphAux()
#include <iomanip>

template <typename ItemType>
void BST<ItemType>::graphAux(ostream & out, int indent,
                             BinaryNode<ItemType>* subtreeRoot) const
{
    if (subtreeRoot != nullptr)
    {
        graphAux(out, indent + 8, subtreeRoot->getRightChildPtr());
        out << setw(indent) << " " << subtreeRoot->getItem() << endl;
        graphAux(out, indent + 8, subtreeRoot->getLeftChildPtr());
    }
}


