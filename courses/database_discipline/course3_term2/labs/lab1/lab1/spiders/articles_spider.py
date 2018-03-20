import scrapy
from scrapy.spiders import CrawlSpider


class ArticlesSpider(CrawlSpider):
    name = "articles"
    start_urls = [
        "https://ua.igotoworld.com/ru/articles_list/spisok-blogiv.htm",
        "https://ua.igotoworld.com/ru/articles_list/spisok-blogiv.htm?page=2"
    ]

    def parse(self, response):
        for text in response.xpath("//div[@class='tour-description-text']"):
            yield {
                'url': response.url,
                'fragments': text.xpath(".//p/text()").extract(),
                'images': text.xpath(".//img/@src").extract(),
            }

        for a in response.xpath("//div[@id='newsListItemsHolder']")\
                .xpath(".//a[@class='newsListItemTextTitle']"):
            yield response.follow(a, callback=self.parse)

