package main

import "fmt"

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

type Array map[string]int

func (a Array) Assign(s string, x int) {
	a[s] = x
}

func (a Array) Lookup(s string) (x int, exists bool) {
	x = a[s]
	exists = x != 0
	return
}

func main() {
	sentence := "alpha x1 beta alpha x1 y"
	for _, x := range lex(sentence, Array(make(map[string]int))) {
		fmt.Printf("%d ", x)
	}
}
