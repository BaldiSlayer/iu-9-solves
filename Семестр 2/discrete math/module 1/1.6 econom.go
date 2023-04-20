package main

import "fmt"

func econom(memoize *map[string]bool, s string) int {
	if len(s) == 1 || (*memoize)[s] {
		return 0
	}

	balance := 0
	sepInd := 2
	for i := 2; i < len(s)-1; i++ {
		if s[i] == '(' {
			balance++
		}
		if s[i] == ')' {
			balance--
		}

		if balance == 0 {
			sepInd = i + 1
			break
		}
	}

	(*memoize)[s] = true
	return econom(memoize, s[2:sepInd]) + econom(memoize, s[sepInd:len(s)-1]) + 1
}

func main() {
	var s string
	fmt.Scanln(&s)
	var memoize = make(map[string]bool)
	fmt.Println(econom(&memoize, s))
}
