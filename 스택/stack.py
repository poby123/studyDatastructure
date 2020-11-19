class Stack:
    def __init__(self):
        self.items = []

    def push(self, val):
        self.items.append(val)

    def pop(self, msg=None):
        try:
            return self.items.pop()
        except IndexError:
            if(msg):
                print(msg)
            else:
                print("Stack is empty")

    def top(self):
        try:
            return self.items[-1]
        except IndexError:
            print("Stack is empty")

    def __len__(self): # len() 으로 호출하면 stack의 item 수를 반환한다.  
        return len(self.items)

if __name__ == "__main__":
    s = Stack()

    '''
        스택 예1 괄호맞추기
    '''
    ex1 = "(()())()"
    for one in ex1:
        if(one == '('):
            s.push(one)
        else:
            s.pop("( 괄호가 부족합니다.")
    
    if(len(s)>0):
        print(') 괄호가 부족합니다.')
    
    '''
        스택 예2-1 : Infix to Postfix
    '''
    infix = '3*(2+5)*4'
    postfix = []
    opStack = Stack()

    for item in infix:
        if(item.isdigit()):
            postfix.append(item)
        elif(item == '('):
            opStack.push(item)
        elif(item == ')'):
            while(len(opStack) > 0 and opStack.top() != '('):
                postfix.append(opStack.pop())
            opStack.pop()
        elif(item in '+-'):
            while(len(opStack) > 0 and opStack.top() in '+-*/'):
                postfix.append(opStack.pop())
            opStack.push(item)
        elif(item in '*/'):
            while(len(opStack) > 0 and opStack.top() in '*/'):
                postfix.append(opStack.pop())
            opStack.push(item)
    
    # rest operator pop
    while(len(opStack) > 0):
        postfix.append(opStack.pop())
    
    # print postfix
    for i in postfix:
        print(i, end=' ')
    
    '''
        스택 예2-2 : Postfix 계산
    '''
    res = Stack()
    for item in postfix:
        if(item.isdigit()):
            res.push(int(item))
        elif(item == '+'):
            a = res.pop()
            b = res.pop()
            res.push(a + b)
        elif(item == '-'):
            a = res.pop()
            b = res.pop()
            res.push(a - b)
        elif(item == '*'):
            a = res.pop()
            b = res.pop()
            res.push(a * b)
        elif(item == '/'):
            a = res.pop()
            b = res.pop()
            res.push(a / b)
    print()
    print('result = ' , res.pop())
        