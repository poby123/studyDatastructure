class Node():
    def __init__(self, key=None):
        self.key = key
        self.next = None
    
    def __str__(self):
        return str(self.key)

class SinglyLinkedList():
    
    # 빈 리스트
    def __init__(self):
        self.head = None
        self.size = 0

    # head 앞에 노드 추가. -> 추가한 노드가 head가 된다.
    def pushFront(self, key):
        new_node = Node(key)
        new_node.next = self.head
        self.head = new_node
        self.size += 1
    
    # tail 다음에 노드 추가.
    def pushBack(self, key):
        new_node = Node(key)
        
        if(len(self) == 0): # 노드가 없으면 그냥 head 노드로 지정한다.
            self.head = new_node
        else:
            tail = self.head
            while(tail.next != None):
                tail = tail.next
            tail.next = new_node # tail 노드의 다음 노드로 지정한다.
        self.size += 1

    # head를 삭제
    def popFront(self):
        if(len(self) == 0):
            return None
        else:
            x = self.head
            key = x.key
            self.head = x.next
            self.size -= 1
            del x
            return key

    # tail 삭제
    def popBack(self):
        if(len(self) == 0):
            return None
        elif(len(self) == 1):
            key = self.head.key
            self.head = None
            self.size -= 1
            return key
        else:
            prev, tail = None, self.head
            while(tail.next != None):
                prev = tail
                tail = tail.next
            prev.next = tail.next
            key = tail.key
            del tail
            self.size -= 1
            return key

    def __len__(self):
        return self.size