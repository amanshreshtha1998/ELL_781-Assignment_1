int nodesCount =0;
int ext_min(HEAP * m) {
	
	if( m->min == NULL)
		printf("Your Heap Is Empty");
	else
	{
		NODE *c =NULL;
		NODE *temp, *rgt;
		temp=  m->min;
		rgt = temp;
		//adding the child nodes to the root list//
		if( temp->child !=NULL)
		 { 
		  
		            c = temp->child; 
		            do { 
		                rgt = c->right; 
		                ( m->min->left)->right = c; 
		                c->left =  m->min->left;
		                m->min->left = c;
		                c->right = m->min; 
		                 
		                 //extracting the min value//
		                if (c->key <  m->min->key) 
		                	 m->min = c; 
		                c->parent = NULL; 
		                c = rgt; 
		            } while (rgt != temp->child); 
		    } 
		//extracting the Min Node//
    (temp->right)->left = temp->left; 
    (temp->left)->right = temp->right; 
    m->min = temp->right; 
	if (temp == temp->right && temp->child == NULL) //if min is the only node//
		 m->min = NULL; 
    else { 
    	 m->min = temp->right;  //rearrange the tree//
	      Consolidate(); 
	      } 
		        nodesCount--; 
	 } 
} 
