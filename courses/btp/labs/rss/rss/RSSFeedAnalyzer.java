package rss;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;

import javax.xml.stream.XMLEventReader;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.events.Characters;
import javax.xml.stream.events.XMLEvent;

public class RSSFeedAnalyzer {
    private final String TITLE = "title";
    private final String DESCRIPTION = "description";
    private final String LINK = "link";
    private final String ITEM = "item";
    private final String PUB_DATE = "pubDate";

    private URL url;

    
    public RSSFeedAnalyzer() {
    	url = null;
    }
    
    public RSSFeedAnalyzer(String url) {
        try {
            this.url = new URL(url);
        } catch (MalformedURLException e) {
            throw new RuntimeException("The URL is malformed.");
        }
    }
    
    
    public void setURL(String url) {
        try {
            this.url = new URL(url);
        } catch (MalformedURLException e) {
            throw new RuntimeException("The URL is malformed.");
        }
    }
    
    public Feed readFeed() {
        Feed feed = null;
        try {
            boolean isFeedHeaders = true;
            String title = "";
            String description = "";
            String link = "";
            String pubDate = "";

            XMLInputFactory inputFactory = XMLInputFactory.newInstance();
            InputStream inputStream = url.openStream();
            XMLEventReader eventReader = inputFactory.createXMLEventReader(inputStream);
            
            // Parse the XML document:
            while (eventReader.hasNext()) {
                XMLEvent event = eventReader.nextEvent();
                
                if (event.isStartElement()) {
                    String localPart = event.asStartElement().getName().getLocalPart();
                    
                    switch (localPart) {
                    // When it comes to first START TAG "ITEM" it means it has already filled
                    // those fields above with main info (that describes Feed itself)
	                    case ITEM:
	                        if (isFeedHeaders) {
	                            isFeedHeaders = false;
	                            feed = new Feed(title, description, link);
	                        }
	                        break;
	                    case TITLE:
	                        title = getCharacterData(event, eventReader);
	                        break;
	                    case DESCRIPTION:
	                        description = getCharacterData(event, eventReader);
	                        break;
	                    case LINK:
	                        link = getCharacterData(event, eventReader);
	                        break;
	                    case PUB_DATE:
	                        pubDate = getCharacterData(event, eventReader);
	                        break;
	                    default:
	                    	break;
                    }
                }
                else if (event.isEndElement()) {
                    if (event.asEndElement().getName().getLocalPart() == ITEM) {
                        FeedMessage message = new FeedMessage();
                        message.setTitle(title);
                        message.setDescription(description);
                        message.setLink(link);
                        message.setPubDate(pubDate);
                        feed.addMessage(message);
                    }
                }
            }
        }
        catch (IOException e) {
            throw new RuntimeException("Can't open stream for URL.");
        }
        catch (XMLStreamException e) {
            throw new RuntimeException("Some XML stream exception occured.");
        }
        
        return feed;
    }

    private String getCharacterData(XMLEvent event, XMLEventReader eventReader) throws XMLStreamException {
        String result = "<Empty>";
        event = eventReader.nextEvent();
        if (event instanceof Characters) {
            result = event.asCharacters().getData();
        }
        return result;
    }
}