# coding=utf-8
import requests
from bs4 import BeautifulSoup

url = 'https://www.google.com'

# get total info
source_code = requests.get(url, verify=False)
soup = BeautifulSoup(source_code.text, 'lxml')
'''
print soup.prettify()
print soup.title
print soup.title.name
print soup.title.string
print soup.title.parent.name
print soup.p
print soup.p['style']
print soup.a
for link in soup.find_all('a'):
    print link.get('href')
'''
print soup.get_text()
