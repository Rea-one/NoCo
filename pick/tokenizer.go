package pick

import (
	"unicode"
)

// 获取字符的类别
func getCategory(r rune) string {
	if unicode.IsLetter(r) || unicode.IsDigit(r) {
		return "digit or letter"
	}
	if unicode.IsPunct(r) {
		return "punct"
	}
	if unicode.IsSpace(r) {
		return "space"
	}
	return "other"
}

type Tokenizer struct {
	Tokens []string
}

func (tar *Tokenizer) Tokenize(text []string) {
	var now string = ""
	var prevCategory string = ""

	for _, line := range text {
		for _, word := range line {
			currCategory := getCategory(word)

			// 当前字符为空格，处理 token
			if currCategory == "space" {
				if now != "" {
					tar.Tokens = append(tar.Tokens, now)
					now = ""
				}
				prevCategory = "space"
				continue
			}

			// 类型发生跳变时，保存之前的 token
			if prevCategory != "" && currCategory != prevCategory {
				if now != "" {
					tar.Tokens = append(tar.Tokens, now)
					now = ""
				}
			}

			now += string(word)
			prevCategory = currCategory
		}
	}

	// 处理最后剩余的 token
	if now != "" {
		tar.Tokens = append(tar.Tokens, now)
	}
}
