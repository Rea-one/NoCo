package init

import (
	"encoding/json"
	"os"
)

type Prewords struct {
	Keyword map[string]string `json:"keyword"`
	Type    map[string]string `json:"type"`
	Value   map[string]string `json:"value"`
}

func NewPrewords() *Prewords {
	return &Prewords{}
}

func NewPres() *Prewords {
	the := NewPrewords()
	the.Read("../proto/prewords.json")
	return the
}

func (tar *Prewords) Read(filepath string) error {
	// 打开文件
	file, err := os.Open(filepath)
	if err != nil {
		return err
	}
	defer file.Close()

	// 解码 JSON 数据
	decoder := json.NewDecoder(file)
	if err := decoder.Decode(tar); err != nil {
		return err
	}

	return nil
}
