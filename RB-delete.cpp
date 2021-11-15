#include "main.hpp"
#include <unistd.h>
template <typename T>
node<T>	*RB_succssor(node<T> *n)
{
	node<T>	*tmp;
	tmp = NULL;
	if (n)
	{
		if (n->right)
		{
			tmp = n->right;
			while (tmp->left)
				tmp = tmp->left;
		}
		else if (n->parent)
		{
			tmp = n->parent;
			if (n == RB_left_of(tmp))
				return tmp;
			while (tmp == RB_right_of(tmp->parent))
				tmp = tmp->parent;
			tmp = tmp->parent;
		}
	}
	return tmp;
}


template <typename T>
node<T>	*RB_predessoccor(node<T> *n)
{
	node<T>	*tmp;

	tmp = NULL;
	if (n)
	{
		if (n->left)
		{
			tmp = n->left;
			while (tmp->right)
				tmp = tmp->right;
		}else if (n->parent)
		{
			tmp = n->parent;
			if (n == RB_right_of(tmp))
				return tmp;
			while (tmp == RB_left_of(tmp->parent))
				tmp = tmp->parent;
			tmp = tmp->parent;
		}
	}
	return tmp;
}

template <typename T>
node<T>	*BST_delete(node<T> *n, node<T> **root)
{
	node<T> *tmp;

	if (n->right)
	{
		tmp = RB_succssor(n);
        RB_swap(n, tmp, root);
        return BST_delete(n, root);
	}
	else if (n->left)
	{
	    tmp = RB_predessoccor(n);
        RB_swap(n, tmp, root);
        return BST_delete(n, root);
	}else
        return n;
}

template <typename T>
void    swap_children(node<T> *a, node<T> *b)
{
    node<T> *bs;
    node<T> *as;

    as = a->left;
    bs = b->left;

    b->left = as;
    if (as)
        as->parent = b;
    a->left = bs;
    if (bs)
        bs->parent = a;

    as = a->right;
    bs = b->right;

    b->right = as;
    if (as)
        as->parent = b;
    a->right = bs;
    if (bs)
        bs->parent = a;

}


template <typename T>
void    swap_parent(node<T> *a, node<T> *b, node<T> **root)
{
    // b will always have parent
    node<T> *ap;

    ap = a->parent;
    a->parent = b->parent;
    if (b->parent->left == b)
        a->parent->left = a;
    else
        a->parent->right = a;
    b->parent = ap;
    if (ap)
    {
        if (ap->left == a)
            ap->left = b;
        else
            ap->right = b;
    }
    else
        *root = b;
}

template <typename T>
void	RB_swap(node<T> *a, node<T> *b, node<T> **root)
{
    swap_children(a, b);
    if (b->parent)
        swap_parent(a, b, root);
    else
        swap_parent(b, a, root);
    std::swap(b->color, a->color);
}

template <typename T>
void    RB_delete_help(node<T> *n, node<T> **root)
{
    node<T> *sb, *neph, *niece;
    node<T> *tmp;

    tmp = n;

    while (1) {
        if (!tmp->parent)
            break ;
        else if (tmp->color)
            break ;
        else
        {
            neph = RB_get_nephew(tmp);
            niece = RB_get_niece(tmp);
            sb = RB_get_sibling(tmp);
            
            if (!RB_color(sb)) {
                if (RB_color(neph))
                {
                    std::cout << "nepew is red" << std::endl;
                    read(0, NULL, 1);
                    sb->color = tmp->parent->color;
                    tmp->parent->color = false;
                    neph->color = false;
                    RB_rotate_sibling_to_par(tmp->parent, sb, root);
                    break ;
                }
                else if (RB_color(niece))
                {
                    std::cout << "nepew is red" << std::endl;
                    read(0, NULL, 1);
                    niece->color = false;
                    sb->color = true;
                    RB_rotate_niece_to_sib(sb, niece, root);
                }
                else
                {
                    std::cout << "sb black niece black neph black" << std::endl;
                    read(0, NULL, 1);
                    sb->color = true;
                    tmp = tmp->parent;
                }
            }
            else
            {
                std::cout << "red sibling" << std::endl;
                read(0, NULL, 1);
                tmp->parent->color = true;
                sb->color = false;
                RB_rotate_sibling_to_par(tmp->parent, sb, root);
            }
        }
    }
    RB_put_in_my_place(n);

    (*root)->color = false;
}




template <typename T>
void	RB_delete(node<T> *n, node<T> **root)
{
    node<T> *tmp;

    tmp = BST_delete(n, root);
    RB_delete_help(n, root);

}
