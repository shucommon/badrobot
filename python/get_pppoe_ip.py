from bs4 import BeautifulSoup
import requests, re, time

form_data = { 'latitudeFrom':3.52,
              'latitudeTo':53.33,
              'longitudeFrom':73.4,
              'longitudeTo':135.23,
              'gardenId':'',
              'zoom':12 }

request_headers = { 'Host':'192.168.1.1',
                    'Origin':'192.168.1.1'}

def crawler(url):
    response = requests.post(url, headers=request_headers)
    content = BeautifulSoup(response.text, 'lxml')
    total_house = 0
    print content

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
