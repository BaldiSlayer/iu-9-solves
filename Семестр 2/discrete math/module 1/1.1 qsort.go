package main

import (
	"fmt"
)

var a []int

func less1(i, j int) bool {
	return a[i] < a[j]
}

func swap1(i, j int) {
	a[i], a[j] = a[j], a[i]
}

func sorting(left, right int,
	less func(i, j int) bool,
	swap func(i, j int)) {

	if right-left <= 1 {
		return
	}

	pivot := left
	m := left + 1
	for i := left + 1; i < right; i++ {
		if less(i, pivot) {
			swap(i, m)
			m++
		}
	}

	swap(left, m-1)
	sorting(left, m, less, swap)
	sorting(m, right, less, swap)
}

func qsort(n int,
	less func(i, j int) bool,
	swap func(i, j int)) {
	sorting(0, n, less, swap)
}

func main() {
	n := 0
	fmt.Scanln(&n)
	a = make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
	}
	qsort(len(a), less1, swap1)
	for i := 0; i < n; i++ {
		fmt.Print(a[i])
		fmt.Print(" ")
	}
}
