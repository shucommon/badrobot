# -*- coding: utf-8 -*-
import scrapy


class TopSpider(scrapy.Spider):
    name = 'top'
    allowed_domains = ['http://music.taihe.com']
    start_urls = ['http://http://music.taihe.com/']

    def parse(self, response):
        pass
