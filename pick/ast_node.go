package pick

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
