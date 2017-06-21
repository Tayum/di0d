package rss;

import java.util.ArrayList;


public class Feed {
    private String title;
    private String description;
    private String link;
    public ArrayList<FeedMessage> messages = new ArrayList<FeedMessage>();

    
    public Feed(String title, String desc, String link) {
        this.title = title;
        description = desc;
        this.link = link;
    }


    public String getTitle() {
        return title;
    }
    
    public String getDescription() {
        return description;
    }

    public String getLink() {
        return link;
    }
    
    public ArrayList<FeedMessage> getMessages() {
        return messages;
    }
    
    public void addMessage(FeedMessage message) {
    	messages.add(message);
    }

    public String getFeed() {
        return "~~~Feed~~~\n" +
        	   "Title: " + title + "\n" +
        	   "Description: " + description + "\n" +
               "Link to feed: " + link + "\n" +
        	   "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }

}