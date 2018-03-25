package lab1;

import java.util.Scanner;
import java.util.InputMismatchException;

public class Main {
	
	// roles of users
	public enum ROLE {
		NONE,
		MASTER,
		TECHNOLOGIST
	}
	
	public static void main(String[] args) {
		// at the very start of the application, it connects to database.
		// application can work properly only if connection to database is set
		// 1.1: if
		boolean db_connection = true;
		if (db_connection) {
			// proceed to program
			// while loop can come in handy in the way:
			// while(true) or while(1) to create infinite cycle like this:
			// 2.2: while:
			while(true) {
				int option;
				String[] options;
				// read input until the moment it is valid
				// 2.3: do while
				do {
					// let's assume we've received the role from somewhere
					// let role = ROLE.MASTER
					ROLE role = ROLE.MASTER;
					// 1.2: switch
					switch(role) {
						case MASTER:
							options = menu_printMasterMenu();
							break;
						case TECHNOLOGIST:
							options = menu_printTechnologistMenu();
							break;
						case NONE:
							options = menu_printAuthMenu();
							break;
						default:
							System.out.println("Invalid role!");
							options = null;
							break;
					}
					
					Scanner reader = new Scanner(System.in);
					System.out.println("Choose an option.\n> ");
					try {
						option = reader.nextInt();
						reader.close();
					}
					catch (InputMismatchException e) {
						option = -1;
					}
				} while(option == -1 || option > options.length);
				// work with valid input (chosen option):
				react_on_chosen_option(option);	
			}
		}
		else {
			// error
			System.err.println("Cannot establish the connection to database");
		}
		
		System.out.println("The program has finished working.");
	}
	
	
	// every menu returns the options that it has inside
	public static String[] menu_printAuthMenu() {
		String[] options = {
				"Login via barcode",
				"Login via password",
				"Exit"
		};
		return menu_print(options);
		
	}
	
	// every menu returns the options that it has inside
	public static String[] menu_printMasterMenu() {
		String[] options = {
			"Start Task",
			"Fill info about completed Task",
			"Check assigned Tasks",
			// etc
			"Exit"
		};
		return menu_print(options);
	}

	// every menu returns the options that it has inside
	public static String[] menu_printTechnologistMenu() {
		String[] options = {
			"Create new Task",
			"Assign Task to Master",
			"Go to Map of building",
			// etc
			"Exit"
		};
		return menu_print(options);
	}
	
	// return the array of printed options
	private static String[] menu_print(String[] options) {
		// 2.1: for
		for (int i = 0; i < options.length; i++) {
			System.out.println((i + 1) + ". " + options[i]);
		}
		return options;
	}
	
	// dummy implementation:
	public static void react_on_chosen_option(int option) {
		// do nothing
	}
}
