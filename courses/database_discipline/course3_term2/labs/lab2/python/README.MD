* lib used to parse Wikipedia: https://github.com/5j9/wikitextparser
1. launch python script with "parse_xml_from_wiki()" function call
2. launch python script with "reorganize_xml_by_category()" function call

It will result in arranged system of folders inside "arrange_xml folder"
Each folder inside represents 1 category, each .xml file inside represents 1 page

---
* How to get the pageid of your main category:
1. Go to https://en.wikipedia.org/wiki/Category:{Software}
where {Software} is the name of your category
2. View HTML content of the page (view-source, Ctrl+U for Chrome)
3. Ctrl+F for "wgRelevantArticleId"
---