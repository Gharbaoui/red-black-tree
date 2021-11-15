#include "insert.cpp"

template <typename T>
void	RB_trav(node<T> *root)
{
	if (root->left)
		RB_trav(root->left);
	std::cout << root->item << " |" << root->color << "| ";
	if (root->right)
		RB_trav(root->right);
}

template <typename T>
node<T>	*find(node<T> *root,T v)
{
	if (root)
	{
		if (root->item > v)
			return find(root->left, v);
		else if (root->item == v)
			return root;
		else
			return find(root->right, v);
	}
	return NULL;
}


int main()
{
	int size;
	/*std::cout << "enter size: ";
	std::cin >> size;*/
	std::vector<int>	values{19 ,252 ,409 ,21 ,252 ,115 ,432 ,203 ,69 ,290 ,324 ,153 ,314 ,416 ,151 ,135 ,171 ,19 ,268 ,70};
	node<int>	*root = nullptr;

/*	srand(time(NULL));
	for (int i = 0; i < size; ++i)
	{
		values.push_back(rand() % 500);
		std::cout << values[i] << ", ";
	}*/
	std::cout << std::endl;
	for (int v : values)
		RB_insert(&root, v);

	RB_trav(root);
	std::cout << std::endl;


    for (int v : values)
    {
        if (v == 432)
            size = 0;
        RB_delete(find(root, v), &root);
		RB_insert(&root, v);
    }

    std::cout << "retry" << std::endl;
    std::cin >> size;

	RB_trav(root);
	std::cout << std::endl;
}
