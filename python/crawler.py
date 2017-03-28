from bs4 import BeautifulSoup
import requests, re, time

form_data = { 'latitudeFrom':3.52,
              'latitudeTo':53.33,
              'longitudeFrom':73.4,
              'longitudeTo':135.23,
              'gardenId':'',
              'zoom':12 }

#form_data = { 'latitudeFrom':0,
#              'latitudeTo':90,
#              'longitudeFrom':0,
#              'longitudeTo':180,
#              'gardenId':'',
#              'zoom':12 }

request_headers = { 'Host':'shanghai.qfang.com',
                    'Origin':'http://shanghai.qfang.com',
                    'Referer':'http://shanghai.qfang.com/map/sale',
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

def crawler(url):
    response = requests.post(url, data=form_data, headers=request_headers, params=query_string_param)
    content = BeautifulSoup(response.text, 'lxml')
    total_house = 0

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

#url = 'http://shanghai.qfang.com/map/sale/roomList'
city_list = { 'shanghai':0,
              'beijing':0,
              'shenzhen':0}

for city in city_list:
    url = 'http://' + city + '.qfang.com/map/sale/roomList'
    request_headers['Host'] = city + '.qfang.com'
    request_headers['Origin'] = 'http://' + city + '.qfang.com'
    request_headers['Referer'] = 'http://' + city + '.qfang.com/map/sale'
    print 'Now craw ' + city
    total_house = crawler(url)
    city_list[city] = total_house

print city_list
