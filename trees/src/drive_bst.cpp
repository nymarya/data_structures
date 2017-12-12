#include "../include/BST.hpp"

int main()
{
	ls::BinarySearchTree<int> bst;

	//Test insert
	bst.insert(50, 50);
	bst.insert(35, 35);
	bst.insert(70, 70);
	bst.insert(25, 25);
	bst.insert(65, 65);
	bst.insert(90, 90);
	bst.insert(40, 40);
	bst.insert(80, 80);
	bst.insert(30, 30);

	int i =0;
	bst.calculaAltura(bst.search(50, i));

	//Test traversals
	bst.level_trasversal();
	std::cout << std::endl;

	bst.pre_ordem_itr();

	//test successor
	auto suc = bst.successor(new ls::Node<int>(30, 30, nullptr, nullptr));
	assert(suc->key == 35);

	suc = bst.successor(new ls::Node<int>(50, 50, nullptr, nullptr));
	assert(suc->key == 65);

	//test predecessor
	int f = 0;
	auto node = bst.search(35, f);
	assert(node->key == 35);

	auto prec = bst.predecessor(node);
	assert(prec->key == 30);

	f=0;
	node = bst.search(40, f);
	assert(node->key == 40);

	prec = bst.predecessor(node);
	assert(prec->key == 35);

	f=0;
	node = bst.search(50, f);
	assert(node->key == 50);

	prec = bst.predecessor(node);
	assert(prec->key == 40);

	f=0;
	node = bst.search(30, f);
	assert(node->key == 30);

	prec = bst.predecessor(node);
	assert(prec->key == 25);

	bst.remove(prec);
	bst.level_trasversal();

	std::vector<int> els = {50, 30, 90, 80, 70, 60, 65, 35, 40, 25, 100, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19};

	ls::BinarySearchTree<int> nBST(els);
	auto n = nBST.getMaxHeight();
	assert(n == 5);
}