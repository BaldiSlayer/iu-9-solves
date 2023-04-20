package main

import "fmt"

type Lexem struct {
	Tag
	Image string
}

type Tag int

const (
	ERROR  Tag = 1 << iota // Неправильная лексема
	NUMBER                 // Целое число
	VAR                    // Имя переменной
	PLUS                   // Знак +
	MINUS                  // Знак -
	MUL                    // Знак *
	DIV                    // Знак /
	LPAREN                 // Левая круглая скобка
	RPAREN                 // Правая круглая скобка
)

func add(word, digit *string, lexems chan Lexem) {
	if len(*word) > 0 {
		lexems <- Lexem{VAR, *word}
		*word = ""
	} else if len(*digit) > 0 {
		lexems <- Lexem{NUMBER, *digit}
		*digit = ""
	}
}

func lexer(expr string, lexems chan Lexem) {
	word := ""
	digit := ""
	for _, symbol := range expr {
		// fmt.Println(string(x))
		if symbol >= '0' && symbol <= '9' {
			if len(word) > 0 {
				word += string(symbol)
			} else {
				digit += string(symbol)
			}
		} else if (symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') {
			if len(digit) == 0 {
				word += string(symbol)
			}
		} else {
			add(&word, &digit, lexems)
			switch symbol {
			case '+':
				lexems <- Lexem{PLUS, "+"}
			case '-':
				lexems <- Lexem{MINUS, "-"}
			case '*':
				lexems <- Lexem{MUL, "*"}
			case '/':
				lexems <- Lexem{DIV, "/"}
			case '(':
				lexems <- Lexem{LPAREN, "("}
			case ')':
				lexems <- Lexem{RPAREN, ")"}
			case ' ':
			default:
				lexems <- Lexem{ERROR, string(symbol)}
			}
		}
	}
	add(&word, &digit, lexems)
	close(lexems)
}

func main() {
	sentence := "1+1+a+b"
	lexems := make(chan Lexem)
	go lexer(sentence, lexems)

	for x := range lexems {
		if x.Tag == ERROR {
			fmt.Print("error")
			return
		}
	}

}
