package pick

import (
	"fmt"
)

type Pick struct {
}

// Pick 解析输入文本并生成AST
func (p *Pick) Pick(input []string) error {
	// 1. 词法分析
	p.Tokenize(input)

	// 2. 生成AST
	ast := &Ast{}
	err := ast.BuildAST(p.Tokens)
	if err != nil {
		return fmt.Errorf("failed to build AST: %v", err)
	}

	// 3. 这里可以添加后续处理步骤（如语义分析、解释执行等）

	return nil
}

// PickAndPrint 解析并打印结果
func (p *Pick) PickAndPrint(input []string) {
	err := p.Pick(input)
	if err != nil {
		fmt.Printf("Error: %v\n", err)
		return
	}

	// 打印解析结果
	fmt.Printf("Tokens: %v\n", p.Tokens)
	// 这里可以添加AST打印逻辑
}
