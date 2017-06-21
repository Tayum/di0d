package rss;

public class SearchObject {
	private FeedMessage message;
	private int matches;
	
	public SearchObject(FeedMessage msg) {
		message = msg;
		matches = 0;
	}
	
	public FeedMessage getMessage() {
		return message;
	}
	
	public int getMatches() {
		return matches;
	}
	
	public void countMatches(String search_query) {
		String toAnalyze = message.getDescription();
		
		int lastIndex = 0;
		int count = 0;
		
		while (lastIndex != -1) {
			lastIndex = toAnalyze.indexOf(search_query, lastIndex);
			
			if(lastIndex != -1) {
				count++;
				lastIndex += search_query.length();
			}
		}
		matches = count;
	}
}
