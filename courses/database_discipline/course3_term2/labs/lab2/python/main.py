import os
import time
from lxml import etree
from shutil import copyfile
# page
from page import Page
# category
from category import Category


CURDIR = os.path.dirname(__file__)
# XML FILES PATH [created by parse_xml_from_wiki()]
XML_PATH = os.path.join(CURDIR, "xml")
# ARRANGED FILES PATH [created by reorganize_xml_by_category()]
ARRANGED_XML_PATH = os.path.join(CURDIR, "arranged_xml")
# 691633 pageid ("Category:Software")
MAINCAT_ID = 691633


def parse_xml_from_wiki():
    if not os.path.exists(XML_PATH):
        os.makedirs(XML_PATH)

    # start with (Category) with MAINCAT_ID,
    # get affiliated (Pages) pageids,
    # then get all (Subcategories) pageids of it
    # and get affiliated (Pages) pageids with each of (Subcategories) pageids
    for pageid in Category.analyze_category(MAINCAT_ID):
        print("Parsed page with pageid: {0}".format(pageid))
        Page(pageid).xml_page_create()


def reorganize_xml_by_category():
    if not os.path.exists(ARRANGED_XML_PATH):
        os.makedirs(ARRANGED_XML_PATH)
    for xml_filename in os.listdir(XML_PATH):
        file_path = os.path.join(XML_PATH, xml_filename)
        root = etree.parse(file_path)

        try:
            ct_name = root.xpath("//category/text()")[0].strip()
            category_name = ct_name if ct_name else "nocategory"
        except:
            category_name = "nocategory"

        category_path = os.path.join(ARRANGED_XML_PATH, category_name)
        if not os.path.exists(category_path):
            os.makedirs(category_path)
        copyfile(file_path, os.path.join(category_path, xml_filename))


if __name__ == '__main__':
    start = time.time()

    # parse_xml_from_wiki()
    # reorganize_xml_by_category()

    end = time.time()
    print("\nTermination took " + str(end - start) + " seconds.")
