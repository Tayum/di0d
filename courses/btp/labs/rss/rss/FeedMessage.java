package rss;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;


public class FeedMessage {
    private String title;
    private String description;
    private String link;
    private Date pubDate;
    
    public FeedMessage() {
    	title = "";
    	description = "";
    	link = "";
    	pubDate = null;
    }
    
    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String desc) {
        description = desc;
    }

    public String getLink() {
        return link;
    }

    public void setLink(String link) {
        this.link = link;
    }
    
    public Date getPubDate() {
    	return pubDate;
    }
    
    public String getPubDateAsString() {
        return pubDate.toString();
    }

	public void setPubDate(String pubDate) {
    	DateFormat df = new SimpleDateFormat("EEE, dd MMM yyyy HH:mm:ss zzz", Locale.ENGLISH);
    	try {
    		this.pubDate = df.parse(pubDate);
    	}
    	catch(ParseException e) {
    		this.pubDate = null;
    	}
    }

    public String getFeedMessage() {
        return "---FeedMessage---\n" +
        	   "Title: " + title + "\n" +
        	   "Description: " + description + "\n" +
               "Link: " + link + "\n" +
        	   "Published on: " + getPubDateAsString() + "\n" + 
               "----------\n";
    }

}
