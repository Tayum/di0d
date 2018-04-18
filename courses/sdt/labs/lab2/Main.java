package lab2;

public class Main {

	public static void main(String[] args) {
		String[] workers = new String[]{
				"Larry Walraven",
				"John Yerger",
				"Armand Rodrigues",
				"Riley Moorehouse",
				"Pedro Meininger",
				"Dwight Raymer",
				"Cory Eargle",
				"Reggie Chartrand",
				"Vernon Lasher",
				"Long Griese",
				"Jonah Gervais",
				"Daryl Mcnerney",
				"Rashad Conniff",
				"Jorge Considine",
				"Ramon Baron"
		};
		
		System.out.println("Initial array:\n");
		arr_print(workers);
		
		System.out.println("\nThe array has been sorted in ascending order:\n");
		sort_selection(workers, true);
		arr_print(workers);
		
		System.out.println("\nThe array has been sorted in descending order:\n");
		sort_selection(workers, false);
		arr_print(workers);
		
		// End of program
		System.out.println("\nThe program has finished working.");
	}
	
	// asc = true - ascending order
	// asc = false - descending order
	static void sort_selection(String[] arr, boolean asc) {
		for (int i = 0; i < arr.length - 1; i++) {
			int minIndex = i;
			for (int j = i + 1; j < arr.length; j++) {
				/* compares the strings */
				if (asc) {
					if (arr[j].compareTo(arr[minIndex]) < 0) {
						minIndex = j;
					}
				}
				else {
					if (arr[j].compareTo(arr[minIndex]) > 0) {
						minIndex = j;
					}
				}
			}
			
			String temp = arr[i];
			arr[i] = arr[minIndex];
			arr[minIndex] = temp;
		}
	}
	
	static void arr_print(String arr[]) {
		int i = 0; 
		for(String str: arr) {
			System.out.println(++i + ". " + str);
			
		}
	}
}
