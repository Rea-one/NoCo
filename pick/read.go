package pick

import (
	"bufio"
	"os"
)

type Lines struct {
	lines []string
}

func (l *Lines) Read(filepath string) {
	file, err := os.Open(filepath)
	defer file.Close()
	if err != nil {
		panic(err)
	}
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		l.lines = append(l.lines, scanner.Text())
	}
	if err := scanner.Err(); err != nil {
		panic(err)
	}
}
