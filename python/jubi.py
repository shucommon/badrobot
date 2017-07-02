# coding=utf-8
from bs4 import BeautifulSoup
import requests, re, time

request_headers = { 'Accept':'*/*',
                    'Host':'www.jubi.com',
                    'Referer':'https://www.jubi.com/',
                    'X-Requested-With':'XMLHttpRequest',
                    'User-Agent':'Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Mobile Safari/537.36' }

def crawler(url):
    start_time = time.time()
    response = requests.get(url, headers=request_headers)
    content = BeautifulSoup(response.text, 'lxml')
    print type(content)
    list_of_coins = content.

    print list_of_coins
    print 'time ' + str(time.time() - start_time)

'''

    roomPageSize = re.search('roomPageSize=(\d*)', content.script.text).group(1)
    for page in range(int(roomPageSize)):
        # update page
	query_string_param['currentPage'] = page + 1
	for li in content.find_all('li', class_='clearfix'):
            total_house += 1
	    roomid = li.get('roomid')
	    lat = li.get('lat')
	    lng = li.get('lng')
	    title = li.get('title')
	    pSpan = li.find('p', class_='hs-info-model clearfix')
	    model = pSpan.span
	    area = model.find_next('span')
	    direction = area.find_next('span')
	    pPrice = li.find('p', class_='hs-info-price')
            print('total_house: ' + str(total_house) +
                  ', roomid: ' + str(roomid) +
                  ', price: ' + pPrice.text +
                  ', lat: ' + str(lat) +
                  ', lng: ' + str(lng) +
                  ', title: ' + title +
                  ', model: ' +  model.text +
                  ', area: ' + area.text +
                  ', direction: ' +  direction.text)
    return total_house
'''
url = 'https://www.jubi.com/coin/allcoin?t=0.16059498079911336'
crawler(url)

coin = {
'rss' : "红贝壳",
'ans' : "小蚁股",
'blk' : "黑币",
'btc' : "比特币",
'bts' : "比特股",
'dnc' : "暗网币",
'doge' : "狗狗币",
'eac' : "地球币",
'etc' : "以太经典",
'eth' : "以太坊",
'fz' : "冰河币",
'game' : "游戏点",
'gooc' : "谷壳币",
'hlb' : "活力币",
'ifc' : "无限币",
'jbc' : "聚宝币",
'ktc' : "肯特币",
'lkc' : "幸运币",
'lsk' : "LISK",
'ltc' : "莱特币",
'max' : "最大币",
'met' : "美通币",
'mryc' : "美人鱼币",
'mtc' : "猴宝币",
'nxt' : "未来币",
'peb' : "普银",
'pgc' : "乐园通",
'plc' : "保罗币",
'ppc' : "点点币",
'qec' : "企鹅币",
'rio' : "里约币",
'skt' : "鲨之信",
'tfc' : "传送币",
'vrc' : "维理币",
'vtc' : "绿币",
'wdc' : "世界币",
'xas' : "阿希币",
'xpm' : "质数币",
'xrp' : "瑞波币",
'xsgs' : "雪山古树",
'ytc' : "一号币",
'zcc' : "招财币",
'zet' : "泽塔币"
}
