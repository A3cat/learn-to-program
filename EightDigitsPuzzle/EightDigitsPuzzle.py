#2023.12.7

import random
class EightDigitsPuzzle:
    '''���̺����̵Ļ�������'''
    def __init__(self, x = None):
        self.board = [1, 2, 3, 4, 5, 6, 7, 8]
        if not x or x == 9:
            self.board.append(' ')
            random.shuffle(self.board)
            for x,_ in enumerate(self.board):
                if _ == ' ':
                    self.empty = x
        else:
            self.board.insert(x - 1, ' ')
            self.empty = x - 1


    def move_up(self):
        '''���������ƶ�'''
        self.board[self.empty] = self.board[self.empty + 3]
        self.board[self.empty + 3] = ' '
        self.empty = self.empty + 3

    def move_down(self):
        '''���������ƶ�'''
        self.board[self.empty] = self.board[self.empty - 3]
        self.board[self.empty - 3] = ' '
        self.empty = self.empty - 3

    def move_left(self):
        '''���������ƶ�'''
        self.board[self.empty] = self.board[self.empty + 1]
        self.board[self.empty + 1] = ' '
        self.empty = self.empty + 1

    def move_right(self):
        '''���������ƶ�'''
        self.board[self.empty] = self.board[self.empty - 1]
        self.board[self.empty - 1] = ' '
        self.empty = self.empty - 1

    def to_str(self):
        '''��ӡ����'''
        n = 1
        for i in self.board:
            if n == 1:
                print('-------------')
                print('|',end = '')
            print(f' {i} |', end = '')
            if n == 3 or n == 6:
                print()
                print('+---+---+---+')
                print('|',end = '')
            n += 1
        print()

    def is_goal(self):
        if self.board == [1, 2, 3, 4, 5, 6, 7, 8, ' ']:
            return True
        return False

#��ʼ������
test = EightDigitsPuzzle()

while True:
    #��ӡ��ǰ����
    test.to_str()

    #�ж��Ƿ����Ŀ��
    if test.is_goal():
        print('Hello World!!!')
        break

    #�ƶ���WASD��ʾ�հ��ƶ��ķ���
    operation = input('Please input operation you wanted(W/A/S/D):').upper()
    if test.empty not in (6,7,8) and operation == 'S':
        test.move_up()
    elif test.empty not in (0,1,2) and operation == 'W':
        test.move_down()
    elif test.empty not in (0,3,6) and operation == 'A':
        test.move_right()
    elif test.empty not in (2,5,8) and operation == 'D':
        test.move_left()
