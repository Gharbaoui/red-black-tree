#include "main.hpp"

template <typename T>
bool	RB_color(node<T> *n)
{
	if (n)
		return n->color;
	return false;
}


template <typename T>
node<T>	*RB_get_parent(node<T> *n)
{
	if (n)
		return n->parent;
	return NULL;
}

template <typename T>
node<T>	*RB_get_grandp(node<T> *n)
{
	if (n)
		return RB_get_parent(n->parent);
	return NULL;
}

template <typename T>
node<T>	*RB_get_uncle(node<T> *n)
{
	node<T>	*p;
	node<T>	*gp;
	if (n)
	{
		gp = RB_get_grandp(n);
		if (gp)
		{
			if (gp->left == RB_get_parent(n)) // means unceel on right
				return gp->right;
			return gp->left;
		}
		return NULL;
	}
	return NULL;
}

template <typename  T>
node<T>	*RB_left_of(node<T> *n)
{
	if (n)
		return n->left;
	return NULL;
}

template <typename  T>
node<T>	*RB_right_of(node<T> *n)
{
	if (n)
		return n->right;
	return NULL;
}

template <typename T>
void    RB_put_in_my_place(node<T> *old_n, node<T> *new_n)
{
    if (old_n && old_n->parent)
    {
        if (old_n->parent->left == old_n)
            old_n->parent->left = new_n;
        else
            old_n->parent->left = new_n;
        new_n->parent = old_n->parent;
    }
}


template <typename T>
void    RB_put_in_my_place(node<T> *old_n)
{
    if (old_n && old_n->parent)
    {
        if (old_n->parent->left == old_n)
            old_n->parent->left = NULL;
        else
            old_n->parent->left = NULL;
    }
}








template <typename T>
node<T> *RB_get_sibling(node<T> *n)
{
    if (RB_left_of(n->parent) == n)
        return n->parent->right;
    return n->parent->left;
}

template <typename T>
node<T> *RB_get_nephew(node<T> *n)
{
    if (RB_left_of(n->parent) == n)
        return n->parent->right->right;
    return n->parent->left->left;
}

template <typename T>
node<T> *RB_get_niece(node<T> *n)
{
    if (RB_left_of(n->parent) == n)
        return n->parent->right->left;
    return n->parent->left->right;
}

template <typename T>
void    RB_rotate_sibling_to_par(node<T> *p, node<T> *sb, node<T> **root)
{
    if (RB_right_of(p) == sb)
        RB_left_rotation(p, root);
    else
        RB_right_rotation(p, root);
}

template <typename T>
void    RB_rotate_niece_to_sib(node<T> *s, node<T> *ni, node<T> **root)
{
    if (RB_left_of(s) == ni)
        RB_right_rotation(s, root);
    else
        RB_left_rotation(s, root);
}
