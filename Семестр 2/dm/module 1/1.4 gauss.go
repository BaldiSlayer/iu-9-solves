package main

import (
	"fmt"
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
	if f.d < 0 {
		f.n *= -1
		f.d *= -1
	}
	return f
}

func Gcd(a, b int) int {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

func CheckSolutions(a [][]Fraction, b []Fraction) bool {
	// Check if the number of equations matches the number of variables
	if len(a) != len(a[0]) {
		return false
	}

	// Calculate the determinant of the matrix A
	det := Determinant(a)
	if det.n == 0 {
		if det.d == 1 {
			return false
		}
		return true
	}

	// Calculate the determinant of each matrix obtained by replacing one column of A by b
	for j := 0; j < len(a[0]); j++ {
		aCopy := make([][]Fraction, len(a))
		for i := 0; i < len(a); i++ {
			aCopy[i] = make([]Fraction, len(a[0]))
			copy(aCopy[i], a[i])
		}
		for i := 0; i < len(a); i++ {
			aCopy[i][j] = b[i]
		}
		detCopy := Determinant(aCopy)
		if detCopy.n == 0 {
			if detCopy.d == 1 {
				return false
			}
		} else {
			return true
		}
	}

	return false
}

// Determinant calculates the determinant of a matrix given as fractions
func Determinant(a [][]Fraction) Fraction {
	if len(a) == 1 {
		return a[0][0]
	}

	det := Fraction{0, 1}
	sign := 1

	for j := 0; j < len(a[0]); j++ {
		aCopy := make([][]Fraction, len(a)-1)
		for i := 0; i < len(a)-1; i++ {
			aCopy[i] = make([]Fraction, len(a[0])-1)
		}
		for i := 1; i < len(a); i++ {
			for k := 0; k < len(a[0]); k++ {
				if k < j {
					aCopy[i-1][k] = a[i][k]
				} else if k > j {
					aCopy[i-1][k-1] = a[i][k]
				}
			}
		}
		coef := Multiply(Fraction{sign * a[0][j].n, a[0][j].d}, Determinant(aCopy))
		det = Add(det, coef)
		sign = -sign
	}

	return det
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
	if !CheckSolutions(arr2, brr2) {
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
