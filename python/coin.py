# coding=utf-8
import requests
from bs4 import BeautifulSoup

total_house = 0
def crawler(url):
    source_code = requests.get(url)
    soup = BeautifulSoup(source_code.text, 'lxml')
    #print soup.prettify()
    ul = soup.find('ul', {'id':'price_today_ul', 'class':'price_today_ul'})
    print ul
    #for li in ul.find_next('li')
'''    for li in ul.findAll('li'):
        info = li.find('div', {'class':'info-panel'})
        header_info = info.find('a', {'name':'selectDetail'})
        href = "http://sh.lianjia.com/" + header_info.get('href')
        title = header_info.get('title')
        roomkey = header_info.get('key')

        col_1 = info.find('div', {'class':'col-1'})
        where = col_1.find('div', {'class':'where'})
        model = where.span.find_next('span')
        size = model.find_next('span')

        col_3 = info.find('div', {'class':'col-3'})
        price = col_3.find('div', {'class':'price'}).span.text

        global total_house
        total_house += 1
        print('total_house: ' + str(total_house) +
              ', roomkey: ' + str(roomkey) +
              ', price: ' + price + u'万' +
              ', model: ' + model.text +
              ', size: ' + size.text +
              ', title: ' + title)
'''
url = 'http://www.jubi.com'
print url
crawler(url)

