package reg_exp;

import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Demo {

	// INITIALISING DATA FROM FILE
	static String[] initData(String path) throws IOException {
		FileReader count = new FileReader(path);
		FileReader string = new FileReader(path);
		BufferedReader buff;

		// amount of lines in file
		buff = new BufferedReader(count);
		int lines = 0;
		while (buff.readLine() != null) {
			lines++;
		}

		// fill the array with lines from file
		buff = new BufferedReader(string);
		String linesArray[] = new String[lines];
		for (int i = 0; i < lines; i++) {
			linesArray[i] = buff.readLine();
		}

		// close the file stream
		buff.close();

		// return the array of Strings
		return (linesArray);
	}
	
	public static void main(String[] args) throws IOException {
		System.out.println("VARIANT ¹10\n");
		final String REG_EXP = "[A-Z]+_?[A-Z\\d]*";
		// init first case
		String[] words = initData("C:/Users/Student/Documents/EclipseWorkspace/Lab1_RegExp/src/reg_exp/words.txt");
		System.out.println("Regular Exspression: " + REG_EXP + "\n");
		// init pattern
		Pattern pattern = Pattern.compile(REG_EXP);
		
		// first case: words on separate lines
        Matcher matcher = null;
		for (int i = 0; i < words.length; i++) {
            matcher = pattern.matcher(words[i]);
			System.out.println("(" + i + "): {" + words[i] + "} - " + matcher.matches());
		}
		
		// init second case (initData returns array of Strings with the only String at [0] position)
		String sentence = initData("C:/Users/Student/Documents/EclipseWorkspace/Lab1_RegExp/src/reg_exp/sentence.txt")[0];
		System.out.println("\n====================\n\nSentence: " + sentence + "\n");
		int counter = 0;
		System.out.println("The boundaries of the words which match the pattern are next:");
		
		// second case: one big sentence
		matcher = pattern.matcher(sentence);
        while (matcher.find()) {	
        	System.out.println("(" + counter + "): " + "[" + matcher.start() + ".." + matcher.end() + "] (" + matcher.group() + ")");
        	counter++;
        }
	}
	
}