#pragma once

namespace engine {
	void PrintMessage();
}
 
//不能这么写,说明:: 被称为作用域解析运算符。它的逻辑
// 是：你只能引用一个已经存在的名字空间。而这里正在定义
//所以不存在
//void engine::PrintMessage();

