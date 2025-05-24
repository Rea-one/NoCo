package pick

import (
	"fmt"
)

type Ast struct {
	Root Node // 根节点
}

// Node AST节点基础接口
type Node interface {
	node()
}

// Statement 语句节点接口
type Statement interface {
	Node
	statement()
}

// Expression 表达式节点接口
type Expression interface {
	Node
	expression()
}

// Program 程序根节点
type Program struct {
	Statements []Statement
}

// BinaryExpression 二元表达式节点
type BinaryExpression struct {
	Left     Expression
	Operator string
	Right    Expression
}

// Identifier 标识符节点
type Identifier struct {
	Value string
}

// IntegerLiteral 整数字面量节点
type IntegerLiteral struct {
	Value int64
}

// BuildAST 从token流构建AST
func (a *Ast) BuildAST(tokens []string) error {
	parser := &parser{tokens: tokens}
	program := parser.parseProgram()
	if len(parser.errors) > 0 {
		return fmt.Errorf("parse errors: %v", parser.errors)
	}
	a.Root = program
	return nil
}

// parser AST解析器
type parser struct {
	tokens  []string
	pos     int
	errors  []string
}

// parseProgram 解析程序根节点
func (p *parser) parseProgram() *Program {
	statements := []Statement{}

	for p.pos < len(p.tokens) {
		stmt := p.parseStatement()
		if stmt != nil {
			statements = append(statements, stmt)
		}
	}

	return &Program{Statements: statements}
}

// parseStatement 解析语句节点（简化版）
func (p *parser) parseStatement() Statement {
	// 这里可以扩展更多语句类型
	expr := p.parseExpression()
	if expr == nil {
		p.errors = append(p.errors, "expected expression")
		return nil
	}
	return expr // 简化处理，表达式直接作为语句
}

// parseExpression 解析表达式（简化版）
func (p *parser) parseExpression() Expression {
	// 处理整数字面量
	if num, ok := isInteger(p.tokens[p.pos]); ok {
		p.pos++
		return &IntegerLiteral{Value: num}
	}

	// 处理标识符
	if isIdentifier(p.tokens[p.pos]) {
		ident := &Identifier{Value: p.tokens[p.pos]}
		p.pos++
		// 检查是否是二元运算
		if p.pos < len(p.tokens) && isOperator(p.tokens[p.pos]) {
			op := p.tokens[p.pos]
			p.pos++
			right := p.parseExpression()
			if right == nil {
				p.errors = append(p.errors, "expected right operand")
				return nil
			}
			return &BinaryExpression{
				Left:     ident,
				Operator: op,
				Right:    right,
			}
		}
		return ident
	}

	return nil
}

// 辅助函数：判断是否为整数
func isInteger(s string) (int64, bool) {
	var n int64
	_, err := fmt.Sscanf(s, "%d", &n)
	return n, err == nil
}

// 辅助函数：判断是否为标识符
func isIdentifier(s string) bool {
	if len(s) == 0 {
		return false
	}
	return (s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z') || s[0] == '_'
}

// 辅助函数：判断是否为运算符
func isOperator(s string) bool {
	return s == "+" || s == "-" || s == "*" || s == "/" || s == "=="
}