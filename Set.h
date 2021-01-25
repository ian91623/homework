#ifndef SET_H
#define SET_H

enum Color{ Red, Black };

// TreeNode class template definition
template< typename Kty >
class TreeNode
{
   template< typename K > friend class set;
private:
   TreeNode *left;   // left subtree, or smallest element if head
   TreeNode *parent; // parent, or root of tree if head
   TreeNode *right;  // right subtree, or largest element if head
   Color color;      // red or black, black if head
   bool isNil;       // true only if head (also nil) node
   Kty myval;
}; // end class template TreeNode

// set class template definition
template< typename Kty >
class set
{
public:
   set(); // Constructs an empty set object, with head node.

   ~set(); // Destroys the set object.

   // Extends the set container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const Kty &val );

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   unsigned int erase( const Kty &val );

private:
   TreeNode< Kty > *myHead; // pointer to head node
   unsigned int mySize;     // number of elements ( not include head node )

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< Kty > *node );

   // rebalance for insertion
   void reBalance( TreeNode< Kty > *node );

   // rotate right at g, where p = g->left and node = p->left
   void LLRotation( TreeNode< Kty > *p );

   // LR rotation; p = g->left and node = p->right
   void LRRotation( TreeNode< Kty > *node );

   // RL rotation; p = g->right and node = p->left
   void RLRotation( TreeNode< Kty > *node );

   // rotate left at g, where p = g->right and node = p->right
   void RRRotation( TreeNode< Kty > *p );

   // erase node provided that the degree of node is at most one
   void eraseDegreeOne( TreeNode< Kty > *node );

   // rebalance for deletion
   void fixUp( TreeNode< Kty > *N, TreeNode< Kty > *P );

   void twoTraversals(); // preorder traversal and inorder traversal

   void preorder( TreeNode< Kty > *node ); // preorder traversal

   void inorder( TreeNode< Kty > *node ); // inorder traversal
}; // end class template set

// Constructs an empty set object, with head node.
template< typename Kty >
set< Kty >::set()
   : myHead( new TreeNode< Kty > ),
     mySize( 0 )
{
   myHead->left = myHead;
   myHead->parent = myHead;
   myHead->right = myHead;
   myHead->color = Black;
   myHead->isNil = true;
}

// Destroys the set object.
template< typename Kty >
set< Kty >::~set()
{
   clear( myHead->parent );
   delete myHead;
}

// Extends the container by inserting a new element,
// effectively increasing the container size by one.
template< typename Kty >
void set< Kty >::insert( const Kty& val )
{
	TreeNode< Kty > **newNodeLocation = &myHead->parent;//指向[指向當前預定插入位置之指標]之指標
	TreeNode< Kty > *currentNode = myHead;//指向當前欲比較之節點之指標
	while(*newNodeLocation != myHead)// x != myHead 等價於 !x->isNil
	{
		currentNode = *newNodeLocation;
		if(val < currentNode->myval)
			newNodeLocation = &currentNode->left;//語法備註：currentNode->left 與 (*newNodeLocation)->left 等價
		else if(val > currentNode->myval)
			newNodeLocation = &currentNode->right;
		else
			return;
	}
	
	*newNodeLocation = new TreeNode< Kty >;
	(*newNodeLocation)->left = (*newNodeLocation)->right = myHead;
	(*newNodeLocation)->parent = currentNode;
	(*newNodeLocation)->color = Red;
	(*newNodeLocation)->isNil = false;
	(*newNodeLocation)->myval = val;

	if(currentNode == myHead)// x == myHead 等價於 x->isNil // 若新增元素為第一個元素，則myHead中除了parent之外，left與right皆需要指向該元素
		myHead->left = myHead->right = *newNodeLocation;
	else if(myHead->left == currentNode && newNodeLocation == &currentNode->left)// 若新增元素為最小，myHead->left需改變指向
		myHead->left = *newNodeLocation;
	else if(myHead->right == currentNode && newNodeLocation == &currentNode->right)// 若新增元素為最大，myHead->right需改變指向
		myHead->right = *newNodeLocation;

	reBalance(*newNodeLocation);

	mySize++;
}

// Removes from the set container a single element whose value is val
// This effectively reduces the container size by one, which are destroyed.
// Returns the number of elements erased.
template< typename Kty >
unsigned int set< Kty >::erase( const Kty &val )
{
	TreeNode< Kty > *target = myHead->parent;//指向當前預定刪除節點之指標
	while(val != target->myval)
	{
		if(target == myHead)
			return 0;// 目標數值不在set當中

		if(val < target->myval)
			target = target->left;
		else
			target = target->right;
	}

	if(target->left != myHead && target->right != myHead)
	{
		TreeNode< Kty > *realTarget = target->right;
		while(realTarget->left != myHead)
			realTarget = realTarget->left;
		target->myval = realTarget->myval;
		target = realTarget;
	}

	if(target == myHead->left && target != myHead->parent)//若刪除目標為最小元素，需改變myHead->left指向
		myHead->left = target->parent;
	if(target == myHead->right && target != myHead->parent)//若刪除目標為最大元素，需改變myHead->right指向
		myHead->right = target->parent;

	eraseDegreeOne(target);

	mySize--;

	return 1;

}

// Removes all elements from the set object (which are destroyed)
template< typename Kty >
void set< Kty >::clear( TreeNode< Kty > *node )
{
   if( !node->isNil ) // node is not an external node
   {
      clear( node->left );
      clear( node->right );
      delete node;
   }
}

// rebalance for insertion
template< typename Kty >
void set< Kty >::reBalance( TreeNode< Kty > *node )
{
	if(node->parent == myHead)
	{
		node->color = Black;
		return;
	}

	if(node->parent->color == Black)
		return;

	TreeNode< Kty > *p = node->parent;
	TreeNode< Kty > *g = p->parent;

	if(g->left->color == g->right->color)
	{
		g->left->color = g->right->color = Black;
		g->color = Red;
		reBalance(g);
	}
	else if(p == g->left && node == p->left)
	{
		g->color = Red;
		p->color = Black;
		LLRotation(p);
	}
	else if(p == g->left && node == p->right)
	{
		g->color = Red;
		node->color = Black;
		LRRotation(node);
	}
	else if(p == g->right && node == p->left)
	{
		g->color = Red;
		node->color = Black;
		RLRotation(node);
	}
	else if(p == g->right && node == p->right)
	{
		g->color = Red;
		p->color = Black;
		RRRotation(p);
	}
}

// rotate right at g, where p = g->left and node = p->left
template< typename Kty >
void set< Kty >::LLRotation( TreeNode< Kty > *p )
{
	TreeNode< Kty > *g = p->parent;	//grandparent節點
	TreeNode< Kty > *u = p->right;	//uncle節點
	TreeNode< Kty > *gg = g->parent;//grand-grandparent節點
	p->right = g;
	p->parent = gg;
	if(u != myHead)
		u->parent = g;
	g->left = u;
	g->parent = p;
	if(gg == myHead)
		gg->parent = p;
	else if(gg->right == g)
		gg->right = p;
	else
		gg->left = p;
}

// LR rotation; p = g->left and node = p->right
template< typename Kty >
void set< Kty >::LRRotation( TreeNode< Kty > *node )
{
	RRRotation(node);
	LLRotation(node);
}

// RL rotation; p = g->right and node = p->left
template< typename Kty >
void set< Kty >::RLRotation( TreeNode< Kty > *node )
{
	LLRotation(node);
	RRRotation(node);
}

// rotate left at g, where p = g->right and node = p->right
template< typename Kty >
void set< Kty >::RRRotation( TreeNode< Kty > *p )
{
	TreeNode< Kty > *g = p->parent;
	TreeNode< Kty > *u = p->left;
	TreeNode< Kty > *gg = g->parent;
	p->left = g;
	p->parent = gg;
	if(u != myHead)
		u->parent = g;
	g->right = u;
	g->parent = p;
	if(gg == myHead)
		gg->parent = p;
	else if(gg->right == g)
		gg->right = p;
	else
		gg->left = p;
}

// erase node provided that the degree of node is at most one
template< typename Kty >
void set< Kty >::eraseDegreeOne( TreeNode< Kty > *node )
{
	TreeNode< Kty > *childOfNode = (node->left->isNil ? node->right : node->left);
	TreeNode< Kty > *parentOfNode = node->parent;

	if(node == parentOfNode->left)
		parentOfNode->left = childOfNode;
	else
		parentOfNode->right = childOfNode;

	if(childOfNode != myHead)
		childOfNode->parent = parentOfNode;

	if(node->color == childOfNode->color && mySize != 1)//細節備註：size為1時會滿足雙黑case，但此時不能呼叫fixUp，必須排除。
		fixUp(childOfNode, parentOfNode);
	else if(childOfNode->color == Red)//細節備註：size為2時刪除root的case必定滿足此判斷式條件，進而使新的root變為黑色節點，不須額外為刪除root的case做額外判斷。
		childOfNode->color = Black;

	if(parentOfNode == myHead)//如果刪到root，要讓myHead->parent指向新的root
		myHead->parent = childOfNode;

	delete node;
}

// rebalance for deletion
template< typename Kty >
void set< Kty >::fixUp( TreeNode< Kty > *N, TreeNode< Kty > *P )
{
	if(P == myHead)//細節備註：如果當前fixUp的N已經是root(即P為myHead)則此時直接結束fixUp，由於此情況只會接續在Case5之後，此時的root必定為黑色節點，無須修正。
		return;
	TreeNode< Kty > *S = (N == P->left ? P->right : P->left);
	bool mirror = (N == P->left ? false : true);

	void (set< Kty >::*LL)(TreeNode< Kty >*);
	void (set< Kty >::*RR)(TreeNode< Kty >*);

	//以下敘述皆預設 N 位於 P->left 上，若N所在位置相反則所有陳述式、判斷式及旋轉方向相反
	if(mirror)
	{
		LL = &set< Kty >::RRRotation;
		RR = &set< Kty >::LLRotation;
	}
	else
	{
		LL = &set< Kty >::LLRotation;
		RR = &set< Kty >::RRRotation;
	}

	// Case1：S為紅色節點 // 此Case必須接續Case2、Case3、Case4其中之一繼續完成平衡
	if(S->color == Red)
	{
		S->color = Black;
		P->color = Red;
		(this->*RR)(S);
		S = (mirror ? P->left : P->right);
	}

	// Case3：S為黑色節點，同時S->right為黑色節點且S->left為紅色節點 // 鏡像(mirror為true)則左右相反 // 此Case必須接續Case2以完成平衡
	if(mirror && S->left->color == Black && S->right->color == Red || !mirror && S->right->color == Black && S->left->color == Red)
	{
		(this->*LL)(mirror ? S->right : S->left);
		S->color = Red;
		S->parent->color = Black;
		S = S->parent;
	}

	// Case2：S為黑色節點，同時S->right為紅色節點 // 鏡像(mirror為true)則左右相反
	if(mirror && S->left->color == Red || !mirror && S->right->color == Red)
	{
		std::swap(S->color, P->color);
		(this->*RR)(S);
		if(mirror)
			S->left->color = Black;
		else
			S->right->color = Black;
		return;
	}

	//Case4：P為紅色節點，S和其子節點皆為黑色節點
	if(P->color == Red)
	{
		S->color = Red;
		P->color = Black;
		return;
	}
	
	//Case5：P、S和其子節點皆為黑色
	else
	{
		S->color = Red;
		fixUp(P, P->parent);
	}
}

// preorder traversal and inorder traversal
template< typename Kty >
void set< Kty >::twoTraversals()
{
   cout << "Preorder sequence:\n";
   preorder( myHead->parent );

   cout << "\nInorder sequence:\n";
   inorder( myHead->parent );
   cout << endl;
}

// preorder traversal
template< typename Kty >
void set< Kty >::preorder( TreeNode< Kty > *node )
{
   if( node != myHead )
   {
      cout << setw( 5 ) << node->myval << ( node->color == Red ? "R" : "B" );
      preorder( node->left );
      preorder( node->right );
   }
}

// inorder traversal
template< typename Kty >
void set< Kty >::inorder( TreeNode< Kty > *node )
{
   if( node != myHead )
   {
      inorder( node->left );
      cout << setw( 5 ) << node->myval << ( node->color == Red ? "R" : "B" );
      inorder( node->right );
   }
}

#endif