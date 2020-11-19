class Queue():
    def __init__(self):
        self.items = []
        self.front_index = 0
    
    def enqueue(self, val):
        self.items.append(val)

    def dequeue(self):
        if(self.front_index == len(self.items)):
            return None
        else:
            x = self.items[self.front_index]
            self.front_index += 1
            return x

if __name__ == '__main__':

    '''
        Queue의 기본 사용
    '''
    q = Queue()
    q.enqueue(3)
    q.enqueue(2)
    q.enqueue(1)
    for i in range(3):
        print(q.dequeue(), end=' ')

    '''
        Josephus Problem
    '''