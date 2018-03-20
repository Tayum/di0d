from lxml import etree
import os
# from scrapy import cmdline
import subprocess


def articles_parse():
    try:
        os.remove("articles.xml")
    except OSError:
        print("OS Error occurred while trying to delete articles.xml")
        pass

    # cmdline.execute("scrapy crawl articles -o articles.xml -t xml".split())
    subprocess.call([r'C:\WINDOWS\system32\WindowsPowerShell\v1.0\powershell.exe',
                    '-ExecutionPolicy', 'Unrestricted', 'scrapy crawl articles -o articles.xml -t xml'])

    root = etree.parse("articles.xml")
    pages_amount = 0
    images_amount = 0
    for page in root.iterfind(".//item"):
        pages_amount += 1
        for child in page:
            if child.tag == "images":
                images_amount += len(child)
                break
    if pages_amount != 0:
        print("Pages: " + str(pages_amount) + "\n"
              "Images: " + str(images_amount) + "\n"
              "Avg: " + str(images_amount / float(pages_amount)))
    else:
        print("No pages in XML tree")


def products_parse():
    try:
        os.remove("products.xml")
    except OSError:
        print("OS Error occurred while trying to delete products.xml")
        pass

    # cmdline.execute("scrapy crawl products -o products.xml -t xml".split())
    subprocess.call([r'C:\WINDOWS\system32\WindowsPowerShell\v1.0\powershell.exe',
                    '-ExecutionPolicy', 'Unrestricted', 'scrapy crawl products -o products.xml -t xml'])


def xml_to_xhtml():
    dom = etree.parse("products.xml")
    xslt = etree.parse("products.xsl")
    transform = etree.XSLT(xslt)
    result = transform(dom)
    
    try:
        os.remove("products.html")
    except OSError:
        print("OS Error occurred while trying to delete products.html")
        pass
    result.write_output("products.html")


if __name__ == "__main__":
    # articles_parse()
    # products_parse()
    xml_to_xhtml()
    print("Exiting the program...")
