import requests
import bs4
import sys
class Downloader:
    '''��Ȥ��С˵���أ�����'''

    def __init__(self, server, target):
        self.server = server
        self.target = target
        # �½���
        self.names = []
        # �½�URL
        self.chapter = []
        # �½���
        self.nums = 0

    def download(self, path):
        '''�����½�����'''
        response = requests.get(path)
        response.encoding = 'utf-8'
        html = response.text
        bf_html = bs4.BeautifulSoup(html, features="lxml")
        texts = bf_html.find_all('div', id='txt', class_='txt')
        return texts[0].text.replace('\xa0' * 2, '\n')

# if __name__ == '__main__':
#     target = 'https://www.biquge345.com/chapter/3202/0446621.html'
#     edge = requests.get(target)
#     edge.encoding = 'utf-8'
#     html = edge.text
#     bf_html = bs4.BeautifulSoup(html, features="lxml")
#     texts = bf_html.find_all('div', id = 'txt', class_ = 'txt')
#     print(texts[0].text.replace('\xa0' * 2, '\n'))

    def downpath(self):
        '''��ȡ��վ�½�'''
        response = requests.get(target)
        response.encoding = 'utf-8'
        ul = response.text
        bf_ul = bs4.BeautifulSoup(ul).find_all('ul', class_='info')
        a = bs4.BeautifulSoup(str(bf_ul[0]))
        a_bf = a.find_all('a')
        for each in a_bf:
            self.names.append(each.string)
            self.chapter.append(self.server + each.get('href'))
            self.nums += 1

# if __name__ == '__main__':
#     server = 'https://www.biquge345.com'
#     target = 'https://www.biquge345.com/book/3202/'
#     response = requests.get(target)
#     response.encoding = 'utf-8'
#     ul = response.text
#     bf_ul = bs4.BeautifulSoup(ul).find_all('ul', class_='info')
#     a = bs4.BeautifulSoup(str(bf_ul[0]))
#     a_bf = a.find_all('a')
#     for each in a_bf:
#         print(each.string, server + each.get('href'))


#��һ�����棬��һ�γ���(С�ɹ�)
if __name__ == '__main__':
    server = 'https://www.biquge345.com'
    target = 'https://www.biquge345.com/book/3202/'
    down = Downloader(server, target)
    down.downpath()
    print("���ؿ�ʼ��")
    with open('E:/�ܴ�������.txt', 'w') as novel:
        for i in range(down.nums):#ѭ������ÿ���½�
            novel.write(f"{down.names[i]}\n")
            novel.write(down.download(down.chapter[i]))
            novel.write('\n')
            print(f'�����أ�{float(i / down.nums):.3f}')
    print('�������')
