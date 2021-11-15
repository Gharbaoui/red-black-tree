#include "main.hpp"
#include "node_op.cpp"
#include "RB-delete.cpp"


template <typename T>
void	RB_left_rotation(node<T> *gp, node<T> **root)
{
	node<T>	*tmp;

	tmp = gp->right;
	gp->right = tmp->left;
	if (gp->right)
		gp->right->parent = gp;
	tmp->left = gp;
	if (gp->parent)
	{
		if (gp->parent->left == gp)
			gp->parent->left = tmp;
		else
			gp->parent->right = tmp;
	}
	else
		*root = tmp;
	tmp->parent = gp->parent;
	gp->parent = tmp;
}

template <typename T>
void	RB_right_rotation(node<T> *gp, node<T> **root)
{
	node<T>	*tmp;

	tmp = gp->left;
	gp->left = tmp->right;
	if (gp->left)
		gp->left->parent = gp;
	tmp->right = gp;
	if (gp->parent) {
		if (gp->parent->right == gp)
			gp->parent->right = tmp;
		else
			gp->parent->left = tmp;
	}else
		*root = tmp;
	tmp->parent = gp->parent;
	gp->parent = tmp;
}

template <typename T>
void	RB_insert_help(node<T> *root, node<T> *n)
{
	if (n->item >= root->item)
	{
		if (root->right)
			RB_insert_help(root->right, n);
		else
		{
			root->right = n;
			n->parent = root;
		}
	}
	else
	{
		if (root->left)
			RB_insert_help(root->left, n);
		else
		{
			root->left = n;
			n->parent = root;
		}
	}
}

template <typename T>
void	RB_solve_violation(node<T> *n, node<T> **root)
{
	node<T>	*tmp;
	node<T>	*uncl;
	node<T>	*p;

	tmp = n;
	while (tmp && tmp != *root && (p = RB_get_parent(tmp))  && RB_color(p))
	{
		uncl = RB_get_uncle(tmp);
		if (RB_color(uncl))
		{
			uncl->color = false;
			p->color = false;
			p->parent->color = true;
			tmp = RB_get_grandp(tmp);
		}
		else // means uncel is black
		{
			if (p == RB_right_of(RB_get_parent(p))) // right case
			{
				if (tmp == RB_left_of(p))
				{ 
					// parent is on right of gp
					// child is on left of parent
					// so i will rotate relative to parent to right side
					// after this rotation they will get aligned
					RB_right_rotation(p, root);
					p = tmp;
				}
				p->color = false;
				p->parent->color = true;
				RB_left_rotation(p->parent, root);
			}
			else
			{
				if (tmp == RB_right_of(p)){
					RB_left_rotation(p, root);
					p = tmp;
				}
				p->color = false;
				p->parent->color = true;
				RB_right_rotation(p->parent, root);
			}
			break ;
		}
	}
	(*root)->color = false;
}



template <typename T>
node<T>	*RB_insert(node<T> **root, T val)
{
	node<T>	*new_node = new node<T>(val);
	if (*root)
	{
		RB_insert_help(*root, new_node);
		if (RB_color(new_node->parent))
			RB_solve_violation(new_node, root);
	}
	else
	{
		new_node->color = false;
		new_node->parent = nullptr;
		*root = new_node;
	}
	return new_node;
}


template <typename T>
int	RB_black_height(node<T> *root)
{
	int lh, rh;
	if (!root)
		return 1;
	else{
		lh = RB_black_height(root->left);
		rh = RB_black_height(root->right);
		if (lh != rh)
			return -10000; // to represent error
		else
		{
			return lh + !root->color;
		}
	}
}


template <typename T>
int	RB_bh(node<T> *root)
{
	int h;

	h = RB_black_height(root);
	if (!root->color)
		return --h;
	return h;
}
