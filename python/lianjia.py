# coding=utf-8
import requests
from bs4 import BeautifulSoup

url = 'http://soa.dooioo.com/api/v4/online/house/ershoufang/listMapResult?access_token=7poanTTBCymmgE0FOn1oKp&client=pc&cityCode=sh&siteType=quyu&type=district&dataId=sh&showType=list&limit_count=2000'

request_headers = { 'Accept':'*/*',
                    'Host':'soa.dooioo.com',
                    'Origin':'http://sh.lianjia.com',
                    'Referer':'http://sh.lianjia.com/ditu?siteType=quyu&dataId=sh&type=city&d=d1',
                    'User-Agent':'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36' }

query_string_param = {
        'access_token':'7poanTTBCymmgE0FOn1oKp',
        'client':'pc',
        'cityCode':'sh',
        'siteType':'quyu',
        'type':'district',
        'dataId':'sh',
        'showType':'list',
        'limit_count':2000}

total_house = 0
def crawler(url):
    source_code = requests.get(url)
    soup = BeautifulSoup(source_code.text, 'lxml')
    ul = soup.find('ul', {'id':'house-lst', 'class':'house-lst'})
    #for li in ul.find_next('li')
    for li in ul.findAll('li'):
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

page = 1
while page <= 4100:
    url = 'http://sh.lianjia.com/ershoufang/d' + str(page)
    print url
    crawler(url)
    page += 1

# get total info
#source_code = requests.get(url, headers=request_headers, params=query_string_param)
#soup = BeautifulSoup(source_code.text, 'lxml')
#print soup
