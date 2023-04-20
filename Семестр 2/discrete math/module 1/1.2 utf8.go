package main

import "fmt"

func encode(utf32 []rune) []byte {
	var utf8Bytes []byte

	for _, r := range utf32 {
		if r <= 0x7F {
			// Single-byte UTF-8 character
			utf8Bytes = append(utf8Bytes, byte(r))
		} else if r <= 0x7FF {
			// Two-byte UTF-8 character
			utf8Bytes = append(utf8Bytes, byte(0xC0|(r>>6)))
			utf8Bytes = append(utf8Bytes, byte(0x80|(r&0x3F)))
		} else if r <= 0xFFFF {
			// Three-byte UTF-8 character
			utf8Bytes = append(utf8Bytes, byte(0xE0|(r>>12)))
			utf8Bytes = append(utf8Bytes, byte(0x80|((r>>6)&0x3F)))
			utf8Bytes = append(utf8Bytes, byte(0x80|(r&0x3F)))
		} else if r <= 0x10FFFF {
			// Four-byte UTF-8 character
			utf8Bytes = append(utf8Bytes, byte(0xF0|(r>>18)))
			utf8Bytes = append(utf8Bytes, byte(0x80|((r>>12)&0x3F)))
			utf8Bytes = append(utf8Bytes, byte(0x80|((r>>6)&0x3F)))
			utf8Bytes = append(utf8Bytes, byte(0x80|(r&0x3F)))
		}
	}

	return utf8Bytes
}

func decode(utf8 []byte) []rune {
	var utf32Runes []rune

	for i := 0; i < len(utf8); {
		b1 := utf8[i]
		var r rune

		switch {
		case b1 <= 0x7F:
			// Single-byte UTF-8 character
			r = rune(b1)
			i += 1
		case b1&0xE0 == 0xC0 && i+1 < len(utf8):
			// Two-byte UTF-8 character
			b2 := utf8[i+1]
			r = rune(((b1 & 0x1F) << 6) | (b2 & 0x3F))
			i += 2
		case b1&0xF0 == 0xE0 && i+2 < len(utf8):
			// Three-byte UTF-8 character
			b2 := utf8[i+1]
			b3 := utf8[i+2]
			r = rune(((b1 & 0x0F) << 12) | ((b2 & 0x3F) << 6) | (b3 & 0x3F))
			i += 3
		case b1&0xF8 == 0xF0 && i+3 < len(utf8):
			// Four-byte UTF-8 character
			b2 := utf8[i+1]
			b3 := utf8[i+2]
			b4 := utf8[i+3]
			r = rune(((b1 & 0x07) << 18) | ((b2 & 0x3F) << 12) | ((b3 & 0x3F) << 6) | (b4 & 0x3F))
			i += 4
		default:
			// Invalid UTF-8 byte sequence
			// Replace with Unicode replacement character U+FFFD
			r = rune(0xFFFD)
			i += 1
		}

		utf32Runes = append(utf32Runes, r)
	}

	return utf32Runes
}

func main() {
	fmt.Printf("%s", string(decode(encode([]rune("I hate some shit")))))
}
