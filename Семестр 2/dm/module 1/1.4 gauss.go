package main

import (
	"fmt"
	"math"
)

type Fraction struct {
	n int
	d int
}

func Divide(f1 Fraction, f2 Fraction) Fraction {
	return Reduce(Fraction{f1.n * f2.d, f1.d * f2.n})
}

func Multiply(f1 Fraction, f2 Fraction) Fraction {
	return Reduce(Fraction{f1.n * f2.n, f1.d * f2.d})
}

func Add(f1 Fraction, f2 Fraction) Fraction {
	return Reduce(Fraction{f1.n*f2.d + f2.n*f1.d, f1.d * f2.d})
}

func Subtract(f1 Fraction, f2 Fraction) Fraction {
	return Reduce(Fraction{f1.n*f2.d - f2.n*f1.d, f1.d * f2.d})
}

func Reduce(f Fraction) Fraction {
	gcd := Gcd(f.n, f.d)
	f.n /= gcd
	f.d /= gcd
	return f
}

func Greater(f1 Fraction, f2 Fraction) bool {
	return int(math.Abs(float64(f1.n)))*f2.d > int(math.Abs(float64(f2.n)))*f1.d
}

func Gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func checkCramer(n int, a [][]Fraction, b []Fraction) bool {
	if len(a) != n || len(a[0]) != n || len(b) != n {
		return false
	}

	m := make([][]Fraction, n)
	for i := range m {
		m[i] = make([]Fraction, n+1)
		copy(m[i], a[i])
		m[i][n] = b[i]
	}

	rankA := gaussianElimination(n, n+1, m)
	rankAugmented := gaussianElimination(n, n, a)

	return rankA == rankAugmented && rankA == n
}

func gaussianElimination(n, m int, a [][]Fraction) int {
	rank := 0
	for row := 0; row < n; row++ {
		pivot := row
		for i := row + 1; i < n; i++ {
			if Greater(a[i][row], a[pivot][row]) {
				pivot = i
			}
		}
		if pivot != row {
			a[row], a[pivot] = a[pivot], a[row]
		}
		for i := row + 1; i < n; i++ {
			coef := Divide(a[i][row], a[row][row])
			for j := row; j < m; j++ {
				a[i][j] = Subtract(a[i][j], Multiply(coef, a[row][j]))
			}
		}
		rank++
	}
	return rank
}

func Gauss(a [][]Fraction, b []Fraction) (x []Fraction, success bool) {
	n := len(b)
	x = make([]Fraction, n)

	arr2 := make([][]Fraction, len(a))
	for i := range a {
		arr2[i] = make([]Fraction, len(a[i]))
		copy(arr2[i], a[i])
	}

	brr2 := make([]Fraction, len(b))
	copy(brr2, b)
	if !checkCramer(n, arr2, brr2) {
		fmt.Println("a")
		return x, false
	}

	for k := 0; k < n-1; k++ {
		for i := k + 1; i < n; i++ {
			if a[i][k].n != 0 {
				lambda := Divide(a[i][k], a[k][k])
				for j := k + 1; j < n; j++ {
					a[i][j] = Subtract(a[i][j], Multiply(lambda, a[k][j]))
				}
				b[i] = Subtract(b[i], Multiply(lambda, b[k]))
			}
		}
	}
	for i := n - 1; i >= 0; i-- {
		sum := b[i]
		for j := i + 1; j < n; j++ {
			sum = Subtract(sum, Multiply(a[i][j], x[j]))
		}
		x[i] = Divide(sum, a[i][i])
	}
	return x, true
}

func main() {
	var n int
	fmt.Scan(&n)

	a := make([][]Fraction, n)
	for i := range a {
		a[i] = make([]Fraction, n)
		for j := range a[i] {
			a[i][j] = Fraction{0, 1}
		}
	}

	b := make([]Fraction, n)
	for i := 0; i < n; i++ {
		b[i] = Fraction{0, 1}
	}

	temp := 0
	for i := 0; i < n; i++ {
		for j := 0; j < n+1; j++ {
			fmt.Scan(&temp)
			if j == n {
				b[i].n = temp
			} else {
				a[i][j].n = temp
			}
		}
	}
	x, success := Gauss(a, b)
	if success {
		for _, val := range x {
			fmt.Printf("%d/%d\n", val.n, val.d)
		}
	} else {
		fmt.Println("No solution")
	}
}
