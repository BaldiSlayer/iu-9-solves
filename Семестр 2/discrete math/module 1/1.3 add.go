package main

import (
	"fmt"
)

func max(a, b int) int {
	if a > b {
		return a
	}
	return b
}

func add(a, b []int32, p int) []int32 {
	var max_len = max(len(a), len(b))
	ans := []int32{}
	var next int32 = 0
	for i := 0; (i < max_len) || (next != 0); i++ {
		var fst int32 = 0

		if len(a) > i {
			fst = a[i]
		}

		var scd int32 = 0
		if len(b) > i {
			scd = b[i]
		}

		ans = append(ans, (fst+scd+next)%int32(p))
		next = (fst + scd + next) / int32(p)
	}
	return ans
}

func main() {
	var a []int32 = []int32{7}
	var b []int32 = []int32{1, 1}
	var asd []int32 = add(a, b, 8)

	for i := 0; i < len(asd); i++ {
		fmt.Print(asd[i])
	}
}
