import scrapy
from scrapy.spiders import CrawlSpider
from scrapy.contrib.linkextractors import LinkExtractor


class ProductsSpider(CrawlSpider):
    name = "products"
    start_urls = [
        "http://m.ua/kata/122/",
    ]

    def parse(self, response):
        for product in response.css('table[id="list"] tr.list-tr'):
            yield {
                'title': product.css('div.list-model-title a::text').extract_first(),
                'desc': product.css('div.list-model-desc::text').extract_first(),
                'price_from': product.css('div.list-big-price a span::text').extract()[0],
                'price_to': product.css('div.list-big-price a span::text').extract()[1],
                'img': response.urljoin(product.css('div.pictb.h img::attr(src)').extract_first()),
            }
        next_page = response.css('div.pager a[id="pager_next"]::attr(href)').extract_first()
        # a block to parse only 2 pages
        if next_page is not None and int(next_page[10]) < 2:
            next_page = response.urljoin(next_page)
            yield scrapy.Request(next_page, callback=self.parse)

