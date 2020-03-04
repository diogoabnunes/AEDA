# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
private:
    stack<T> stacki;
    stack<T> stackMIN;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

template <class T> 
bool StackExt<T>::empty() const
{
    return stacki.empty();
}

template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    *novo = stacki.top();
    return *novo;
}

template <class T> 
void StackExt<T>::pop() {
    stacki.pop();
    stackMIN.pop();
}

template <class T> 
void StackExt<T>::push(const T & val)
{
    if (stacki.empty())
    {
        stacki.push(val);
        stackMIN.push(val);
    }
    else
    {
        if (val < stackMIN.top())
        {
            stacki.push(val);
            stackMIN.push(val);
        }
        else
        {
            stacki.push(val);
            stackMIN.push(stackMIN.top());
        }
    }
}

template <class T> 
T& StackExt<T>::findMin()
{
    T* novo = new T();
    *novo = stackMIN.top();
    return *novo;
}

