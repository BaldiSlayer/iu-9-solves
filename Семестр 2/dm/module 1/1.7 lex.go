package main

import "fmt"

type AVLNode struct {
	key    string
	value  int
	left   *AVLNode
	right  *AVLNode
	height int
}

type AVLTree struct {
	root *AVLNode
}

func NewAVLTree() *AVLTree {
	return &AVLTree{}
}

func getHeight(node *AVLNode) int {
	if node == nil {
		return 0
	}
	return node.height
}

func getBalanceFactor(node *AVLNode) int {
	if node == nil {
		return 0
	}
	return getHeight(node.left) - getHeight(node.right)
}

func rotateLeft(node *AVLNode) *AVLNode {
	rightChild := node.right
	node.right = rightChild.left
	rightChild.left = node
	node.height = 1 + max(getHeight(node.left), getHeight(node.right))
	rightChild.height = 1 + max(getHeight(rightChild.left), getHeight(rightChild.right))
	return rightChild
}

func rotateRight(node *AVLNode) *AVLNode {
	leftChild := node.left
	node.left = leftChild.right
	leftChild.right = node
	node.height = 1 + max(getHeight(node.left), getHeight(node.right))
	leftChild.height = 1 + max(getHeight(leftChild.left), getHeight(leftChild.right))
	return leftChild
}

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func insertHelper(node *AVLNode, key string, value int) *AVLNode {
	if node == nil {
		return &AVLNode{key: key, value: value, height: 1}
	}
	if key < node.key {
		node.left = insertHelper(node.left, key, value)
	} else if key > node.key {
		node.right = insertHelper(node.right, key, value)
	} else {
		node.value = value
		return node
	}
	node.height = 1 + max(getHeight(node.left), getHeight(node.right))
	balanceFactor := getBalanceFactor(node)
	if balanceFactor > 1 && key < node.left.key {
		return rotateRight(node)
	}
	if balanceFactor < -1 && key > node.right.key {
		return rotateLeft(node)
	}
	if balanceFactor > 1 && key > node.left.key {
		node.left = rotateLeft(node.left)
		return rotateRight(node)
	}
	if balanceFactor < -1 && key < node.right.key {
		node.right = rotateRight(node.right)
		return rotateLeft(node)
	}
	return node
}

func (tree *AVLTree) Insert(key string, value int) {
	tree.root = insertHelper(tree.root, key, value)
}

func lookupHelper(node *AVLNode, key string) (int, bool) {
	if node == nil {
		return 0, false
	}
	if key < node.key {
		return lookupHelper(node.left, key)
	} else if key > node.key {
		return lookupHelper(node.right, key)
	} else {
		return node.value, true
	}
}

func lex(sentence string, array AssocArray) []int {
	num := 1
	res := make([]int, 0)
	word := ""
	for i := 0; i <= len(sentence); i++ {
		if i == len(sentence) || sentence[i] == ' ' {
			if len(word) > 0 {
				k, exist := array.Lookup(word)
				if exist {
					res = append(res, k)
				} else {
					array.Assign(word, num)
					res = append(res, num)
					num++
				}

				word = ""
			}
		} else {
			word += string(sentence[i])
		}
	}
	return res
}

type AssocArray interface {
	Assign(s string, x int)
	Lookup(s string) (x int, exists bool)
}

func (tree *AVLTree) Assign(s string, x int) {
	tree.Insert(s, x)
}

func (tree *AVLTree) Lookup(key string) (int, bool) {
	return lookupHelper(tree.root, key)
}

func main() {
	var tree AVLTree
	sentence := "a b b a c d e e c d a"
	for _, x := range lex(sentence, &tree) {
		fmt.Printf("%d ", x)
	}
}
