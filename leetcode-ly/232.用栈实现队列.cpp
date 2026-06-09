/*
 * @lc app=leetcode.cn id=232 lang=cpp
 *
 * [232] 用栈实现队列
 */
#include <iostream>
// @lc code=start
#include <stack>
using namespace std;
class MyQueue
{
private:
    // 进
    stack<int> mystack1;
    // 出
    stack<int> mystack2;

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        while (!mystack2.empty())
        {
            mystack1.push(mystack2.top());
            mystack2.pop();
        }
        mystack1.push(x);

        while (!mystack1.empty())
        {
            mystack2.push(mystack1.top());
            mystack1.pop();
        }
    }

    int pop()
    {
        int value = mystack2.top();
        mystack2.pop();
        return value;
    }

    int peek()
    {
        return mystack2.top();
    }

    bool empty()
    {
        return mystack2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
// @lc code=end
int main(int argc, char const *argv[])
{
    MyQueue queue;
    queue.push(2);
    queue.push(3);
    queue.push(5);
    while (!queue.empty())
    {
        cout << queue.peek() << endl;
        queue.pop();
        /* code */
    }

    return 0;
}
