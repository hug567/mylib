################################################################################
# 结构类型：单向链表
# python: python 3.6.3
################################################################################

# list node
class Node():
    def __init__(self, data):
        self.data = data
        self.next = None

# single link list
class List():
    def __init__(self, node = None):
        self.head = node

    def is_empty(self):
        return self.head == None

    def length(self):
        cur = self.head
        len = 0
        while cur != None:
            len += 1
            cur = cur.next
        return len

    def print(self):
        print("list: ", end='')
        cur = self.head
        while cur != None:
            print(cur.data, end=' ')
            cur = cur.next
        print()

    def add_to_head(self, data):
        node = Node(data)
        node.next = self.head
        self.head = node

    def add_to_tail(self, data):
        node = Node(data)
        if self.is_empty():
            self.head = node
        else:
            cur = self.head
            while cur.next != None:
                cur = cur.next
            cur.next = node

if __name__ == "__main__":
    l = List() # ctrate single link list

    l.add_to_tail(1)
    l.add_to_tail(2)
    l.add_to_tail(3)
    l.print()
    print("len = %d" % l.length())
    l.add_to_head(4)
    l.print()
    print("len = %d" % l.length())
