package rss;

import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

import com.thoughtworks.xstream.XStream;

public class Main {
	final static int EXP_MILLISEC = 259200000; // 259200000 millisec is 3 days
	final static String PATH = "C:\\Users\\Student\\Documents\\EclipseWorkspace\\Lab3_RSS\\";
	
	public static void main(String[] args) throws IOException {
        XStream xstream = new XStream();
        xstream.alias("FeedMessage", FeedMessage.class);
		// Prepare the list of stop-words:
        List<String> stopWords = Files.readAllLines(Paths.get(PATH + "src\\rss\\stop-words.txt"));
        
        
        // Read database from file
		ArrayList<FeedMessage> db_messages = readFromDatabase(xstream);
		// Read URLs from file
		List<String> URLs = createURLs();
		
		
		ArrayList<Feed> url_feeds = null;
		ArrayList<FeedMessage> url_messages = null;
		if (URLs != null) {
			// Create Feeds
			url_feeds = createFeedsFromURLs(URLs);
			// Combine FeedMessages from Feeds
			url_messages = createMessagesFromFeeds(url_feeds);
		}	
		
		System.out.println("VARIANT #10");
		System.out.println("Topic: News.USA");
		System.out.println("Available commands:");
		System.out.println("--help ~~ Show the list of available commands");
		System.out.println("--db ~~ Print the FeedMessages from Database");
		System.out.println("--index ~~ Print the most relevant 10 results to the given phrase");
		System.out.println("--feeds ~~ Show the brief description of analyzed Feeds from URLs");
		System.out.println("--update ~~ Delete old (>3 days) FeedMessages and Update Database with new FeedMessages from URLs");
		System.out.println("--save ~~ Save current state of Database to file and Exit the program");
		System.out.println("--quit ~~ Exit the program without saving anything to local Database file\n");
		
		// Analyze input:
	    Scanner scanner = new Scanner(System.in);
        while(true) {
        	System.out.print("\n\n> ");
        	String input_string = scanner.nextLine();
        	if(input_string.isEmpty()) {
        		continue;
        	}
        	else if ("--help".equals(input_string)) {
        		System.out.println("--help ~~ Show the list of available commands");
        		System.out.println("--db ~~ Print the FeedMessages from Database");
        		System.out.println("--index ~~ Print the most relevant 10 results to the given phrase");
        		System.out.println("--feeds ~~ Show the brief description of analyzed Feeds from URLs");
        		System.out.println("--update ~~ Delete old (>3 days) FeedMessages and Update Database with new FeedMessages from URLs");
        		System.out.println("--save ~~ Save current state of Database to file and Exit the program");
        		System.out.println("--quit ~~ Exit the program without saving anything to local Database file\n");
        	}
        	else if("--db".equals(input_string)) {
        		if(db_messages != null) {
            		printMessages(db_messages);
        		}
        		else {
        			System.out.println("The Database is currently <empty>");
        		}
        	}
        	else if("--index".equals(input_string)) {
        		System.out.println("Now please enter the word or phrase (will be checked as mutual). For example, 'Trump':");
        		String search_query = scanner.nextLine();
        		List<SearchObject> search_results = search(db_messages, stopWords, search_query);
        		if(search_results == null) {
        			System.out.println("You have input the query that consists of the stop-word only. Please, try another query.");
        		}
        		else {
        			System.out.println("> These are the FeedMessages that fits your query the most:\n");
            		for(SearchObject srch : search_results) {
            			System.out.println(srch.getMessage().getFeedMessage());
            			System.out.println("(number of entries here: " + srch.getMatches() + ")\n\n");
            		}
        		}
        	}
        	else if("--feeds".equals(input_string)) {
        		if(url_feeds != null) {
            		printFeeds(url_feeds);
        		}
        		else {
        			System.out.println("There were no valid URLs in the file.");
        		}
        	}
        	else if("--update".equals(input_string)) {
        		if(url_messages == null) {
        			System.out.println("Nothing to provide with URLs (no valid URLs);\n"
        					+ "Still will try to delete old messages from DB, if any...");
        		}
        		updateDBMessages(db_messages, url_messages);
        		System.out.println("The 'update' has been completed successfully");
        	}
        	else if("--save".equals(input_string)) {
    			saveDBMessages(db_messages, xstream);
        		System.out.println("The local program Database is saved to file.\n"
        				+ "Exiting the program...");
        		break;
        	}
        	else if("--quit".equals(input_string)) {
        		scanner.close();
        		break;
        	}
        	else {
        		System.out.println("Wrong input; try again.");
        	}
        }

	}
	
	static ArrayList<FeedMessage> readFromDatabase(XStream xstream) throws IOException {
		ArrayList<FeedMessage> db_messages = new ArrayList<FeedMessage>();
        List<String> rawXML = Files.readAllLines(Paths.get(PATH + "MongoDB.xml"), Charset.forName("ISO-8859-1"));
		for(int i = 0; i <= rawXML.size() - 6; i+=6) {
			String singleXML = "";
			for(int j = 0; j < 6; j++) {
				singleXML += rawXML.get(i + j);
			}
			db_messages.add((FeedMessage)xstream.fromXML(singleXML));
		}
		return db_messages;
	}
	
	static List<String> createURLs() {
		List<String> URLs = null;
		try {
			URLs = Files.readAllLines(Paths.get(PATH + "src\\rss\\rssfeeds.txt"));
		}
		catch(IOException e) {
			System.out.println("No such file exists.");
		}
		return URLs;
	}
	
	static ArrayList<Feed> createFeedsFromURLs(List<String> URLs) {
		ArrayList<Feed> feeds = new ArrayList<Feed>();
		RSSFeedAnalyzer analyzer = new RSSFeedAnalyzer();
		
		for(String url : URLs) {
	        try {
	        	analyzer.setURL(url);
	            Feed curFeed = analyzer.readFeed();
	            feeds.add(curFeed);
	        }
	        catch(RuntimeException e) {
	        	System.out.println(e.getMessage());
	        }
		}
		return feeds;
	}
	
	static void printFeeds(ArrayList<Feed> feeds) {
		for(int i = 0; i < feeds.size();i++) {
			Feed curFeed = feeds.get(i);
            System.out.println((i + 1) + ") " + curFeed.getFeed());
		}
	}
	
	static ArrayList<FeedMessage> createMessagesFromFeeds(ArrayList<Feed> feeds) {
		ArrayList<FeedMessage> messages = new ArrayList<FeedMessage>();
		for(int i = 0; i < feeds.size();i++) {
			Feed curFeed = feeds.get(i);
			messages.addAll(curFeed.getMessages());
		}
		return messages;
	}
	
	static void printMessages(ArrayList<FeedMessage> messages) {
		int msgs = 0;
		for (FeedMessage message : messages) {
			System.out.println(message.getFeedMessage());
			msgs++;
		}
		System.out.println("(" + msgs + " messages printed)");
	}
	
	static void updateDBMessages(ArrayList<FeedMessage> db_messages, ArrayList<FeedMessage> messagesToUpdateWith) {
		// STEP 4.1: DELETE OLD ONES
		long now_millisec = new Date().getTime();
		for(int i = db_messages.size() - 1; i >= 0; i--) {
			long msg_millisec = db_messages.get(i).getPubDate().getTime();
			if (now_millisec - msg_millisec >= EXP_MILLISEC) {
				db_messages.remove(i);
			}
		}
		// STEP 4.2: UPDATE
		if(messagesToUpdateWith != null) {
			int size = db_messages.size();
			for(FeedMessage msg : messagesToUpdateWith) {
				for(int i = 0; i <= size; i++) {
					if(now_millisec - msg.getPubDate().getTime() < EXP_MILLISEC) {
						if(i == size) {
							db_messages.add(msg);
						}
						else if(msg.getLink().equals(db_messages.get(i).getLink())) {
							if(!msg.getPubDateAsString().equals(db_messages.get(i).getPubDateAsString())) {
								db_messages.remove(i);
								db_messages.add(i, msg);
							}
							break;
						}
					}
				}
			}
		}
	}
	
	static void saveDBMessages(ArrayList<FeedMessage> db_messages, XStream xstream) throws IOException {
        String xmlFileString = "";
        for(FeedMessage msg : db_messages) {
        	xmlFileString += xstream.toXML(msg) + "\n";
        }
        File file = new File("MongoDB.xml");
        if(!file.exists()) {
        	file.createNewFile();
        }
        PrintWriter xmlFile = new PrintWriter("MongoDB.xml");
        xmlFile.write(xmlFileString);
        xmlFile.close();
	}

	static List<SearchObject> search(ArrayList<FeedMessage> db_messages, List<String> stopWords, String search_query) {
		for(String stopWord : stopWords) {
			if(search_query.equals(stopWord)) {
				return null;
			}
		}
		ArrayList<SearchObject> searchObjects = new ArrayList<SearchObject>();
		for(FeedMessage msg : db_messages) {
			SearchObject srch = new SearchObject(msg);
			srch.countMatches(search_query);
			searchObjects.add(srch);
		}
		Collections.sort(searchObjects, new Comparator<SearchObject>() {
			@Override
			public int compare(final SearchObject obj1, final SearchObject obj2) {
				return obj2.getMatches() - obj1.getMatches();
			}
		});
	
		return searchObjects.subList(0, 9);
	}
}
