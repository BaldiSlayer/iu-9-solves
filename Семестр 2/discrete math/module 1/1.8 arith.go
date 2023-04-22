package main

import (
	"fmt"
	"os"
	"strconv"
)

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

type parser struct {
	lexems    []Lexem
	currIndex int
	variables map[string]int
}

func newParser(lexems []Lexem) *parser {
	return &parser{
		lexems:    lexems,
		currIndex: 0,
		variables: make(map[string]int),
	}
}

func (p *parser) parse() (int, error) {
	result, err := p.parseE()
	if err != nil {
		return 0, err
	}
	if p.currIndex != len(p.lexems) {
		return 0, fmt.Errorf("Syntax error")
	}
	return result, nil
}

func (p *parser) parseE() (int, error) {
	left, err := p.parseT()
	if err != nil {
		return 0, err
	}
	for {
		switch p.currToken().Tag {
		case PLUS:
			p.nextToken()
			right, err := p.parseT()
			if err != nil {
				return 0, err
			}
			left += right
		case MINUS:
			p.nextToken()
			right, err := p.parseT()
			if err != nil {
				return 0, err
			}
			left -= right
		default:
			return left, nil
		}
	}
}

func (p *parser) parseT() (int, error) {
	left, err := p.parseF()
	if err != nil {
		return 0, err
	}
	for {
		switch p.currToken().Tag {
		case MUL:
			p.nextToken()
			right, err := p.parseF()
			if err != nil {
				return 0, err
			}
			left *= right
		case DIV:
			p.nextToken()
			right, err := p.parseF()
			if err != nil {
				return 0, err
			}
			if right == 0 {
				return 0, fmt.Errorf("Division by zero")
			}
			left /= right
		default:
			return left, nil
		}
	}
}

func (p *parser) parseF() (int, error) {
	switch p.currToken().Tag {
	case NUMBER:
		value, _ := strconv.Atoi(p.currToken().Image)
		p.nextToken()
		return value, nil
	case VAR:
		name := p.currToken().Image
		p.nextToken()
		if value, ok := p.variables[name]; ok {
			return value, nil
		}
		fmt.Printf("Enter value of variable %s: ", name)
		var input string
		fmt.Scanln(&input)
		value, err := strconv.Atoi(input)
		if err != nil {
			return 0, fmt.Errorf("Invalid value for variable %s", name)
		}
		p.variables[name] = value
		return value, nil
	case LPAREN:
		p.nextToken()
		value, err := p.parseE()
		if err != nil {
			return 0, err
		}
		if p.currToken().Tag != RPAREN {
			return 0, fmt.Errorf("Missing right parenthesis")
		}
		p.nextToken()
		return value, nil
	case MINUS:
		p.nextToken()
		value, err := p.parseF()
		if err != nil {
			return 0, err
		}
		return -value, nil
	default:
		return 0, fmt.Errorf("Syntax error")
	}
}

func (p *parser) nextToken() {
	if p.currIndex < len(p.lexems) {
		p.currIndex++
	}
}

func (p *parser) currToken() Lexem {
	if p.currIndex < len(p.lexems) {
		return p.lexems[p.currIndex]
	}
	return Lexem{}
}

func main() {

	expr := "-x * (x+10) * (128/x-5)"
	//expr := string(os.Args[1])
	lexems := make(chan Lexem)
	go lexer(expr, lexems)

	parser := newParser([]Lexem{})
	for lexem := range lexems {
		if lexem.Tag == ERROR {
			fmt.Println("error")
			os.Exit(1)
		}
		parser.lexems = append(parser.lexems, lexem)
	}

	result, err := parser.parse()
	if err != nil {
		fmt.Println("error")
		os.Exit(1)
	}
	fmt.Println(result)
}
