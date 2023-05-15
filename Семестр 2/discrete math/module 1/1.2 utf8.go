package main

func decode(utf8 []byte) []rune {
	utf32 := make([]rune, 0, len(utf8))
	for iter := 0; iter < len(utf8); iter++ {
		switch {
		case utf8[iter]/128 == 0:
			utf32 = append(utf32, rune(utf8[iter]))
			continue
		case len(utf8) >= 2 && utf8[iter]/32 == 6 && utf8[iter+1]/64 == 2:
			utf32 = append(utf32, rune(utf8[iter])%32<<6+rune(utf8[iter+1])%64)
			iter++
			continue
		case len(utf8) >= 3 && utf8[iter]/16 == 14 && utf8[iter+1]/64 == 2 && utf8[iter+2]/64 == 2:
			utf32 = append(utf32, rune(utf8[iter])%(1<<4)<<12+rune(utf8[iter+1])%(1<<6)<<6+rune(utf8[iter+2])%(1<<6))
			iter += 2
			continue
		case len(utf8) >= 4 && utf8[iter]/8 == 30 && utf8[iter+1]/64 == 2 && utf8[iter+2]/64 == 2 && utf8[iter+3]/64 == 2:
			utf32 = append(utf32, rune(utf8[iter])%(1<<3)<<18+rune(utf8[iter+1])%(1<<6)<<12+rune(utf8[iter+2])%(1<<6)<<6+rune(utf8[iter+3])%(1<<6))
			iter += 3
			continue
		}
	}
	return utf32
}

func encode(utf32 []rune) []byte {
	utf8 := make([]byte, 0, len(utf32)*4)
	for _, elemOfRunes := range utf32 {
		if elemOfRunes>>7 == 0 {
			utf8 = append(utf8, byte(elemOfRunes))
			continue
		}

		if elemOfRunes>>11 == 0 {
			utf8 = append(utf8, byte(3<<6+elemOfRunes>>6), byte(1<<7+elemOfRunes%(1<<6)))
			continue
		}

		if elemOfRunes>>16 == 0 {
			utf8 = append(utf8,
				byte(7<<5+elemOfRunes>>12),
				byte(128+elemOfRunes>>6%(1<<6)),
				byte(128+elemOfRunes%(1<<6)))
			continue
		}

		utf8 = append(utf8,
			byte(15<<4+elemOfRunes>>18),
			byte(128+elemOfRunes>>12%64),
			byte(128+elemOfRunes/64%64),
			byte(128+elemOfRunes%64))
	}
	return utf8
}

func main() {
}
