import json
from country_code import get_country_code
from pygal.maps.world import World
from pygal.style import RotateStyle, LightColorizedStyle

filename = 'population_data.json'
with open(filename) as f:
    pop_data = json.load(f)

cc_populations = {}
for pop_dict in pop_data:
    if pop_dict['Year'] == '2010':
        country_name = pop_dict['Country Name']
        population = int(float(pop_dict['Value']))
        code = get_country_code(country_name)
        if code:
            cc_populations[code] = population

cc1, cc2, cc3 = {}, {}, {}
for cc, popu in cc_populations.items():
    if popu < 10000000:
        cc1[cc] = popu
    elif popu < 1000000000:
        cc2[cc] = popu
    else:
        cc3[cc] = popu

wm_style = RotateStyle('#336699', base_style=LightColorizedStyle)
wm = World(style=wm_style)
wm.title = 'Population in world'
wm.add('< 10m', cc1)
wm.add('10m - 1b', cc2)
wm.add('> 1b', cc3)
wm.render_to_file('world_populations_new.svg')
