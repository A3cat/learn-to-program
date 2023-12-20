import requests
import bs4
import sys
class Downloader:
    '''笔趣阁小说下载，启动'''

    def __init__(self, server, target):
        self.server = server
        self.target = target
        # 章节名
        self.names = []
        # 章节URL
        self.chapter = []
        # 章节数
        self.nums = 0

    def download(self, path):
        '''依据章节下载'''
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
        '''爬取网站章节'''
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


#第一个爬虫，第一次尝试(小成功)
if __name__ == '__main__':
    server = 'https://www.biquge345.com'
    target = 'https://www.biquge345.com/book/3202/'
    down = Downloader(server, target)
    down.downpath()
    print("下载开始：")
    with open('E:/很纯很暧昧.txt', 'w') as novel:
        for i in range(down.nums):#循环遍历每个章节
            novel.write(f"{down.names[i]}\n")
            novel.write(down.download(down.chapter[i]))
            novel.write('\n')
            print(f'已下载：{float(i / down.nums):.3f}')
    print('下载完成')
