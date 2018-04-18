package lab3;

public class Main {

	public static void main(String[] args) {
		stack_demonstration();
		// queue_demonstation();

		// End of program
		System.out.println("\nThe program has finished working.");
	}
	
	static void stack_demonstration() {
		Stack s = new Stack(5);
		String[] notifications = new String[] {
				"4:20: Task completed (100%) by Sergei",
				"8:28: Task in progress (50%) by Andrew",
				"11:29: Task completed (100%) by Fedai",
				"13:37: Task in progress (27%) by Honchar",
				"14:48: Task in progress (89%) by Sasha"
		};
		
		// notifications sent to Technologist
		for(String n: notifications) {
			System.out.println("Notification sent: " + n);
			s.push(n);
		}
		
		System.out.println();
		s.output();
		
		// Technologist checks the notifications:
		for(;s.isEmpty() != true;) {
			System.out.println("Notification received: " + s.pop());
		}
	}
	
	static void queue_demonstation() {
		Queue q = new Queue(10);
		String[] tasks = new String[] {
				"Take an apple",
				"Take a pen",
				"Create apple-pen",
				"Take a pen",
				"Take a pineapple",
				"Create pineapple-pen",
				"Take a apple-pen",
				"Take a pineapple-pen",
				"Say \"Ooh!\"",
				"Create pen-pineapple-apple-pen"
		};
		
		// Technologist adds all the tasks:
		for(String t: tasks) {
			System.out.println("Added task: " + t);
			q.enqueue(t);
		}
		
		System.out.println();
		q.output();
		
		// Master copes with all the tasks:
		for(;q.isEmpty() != true;) {
			System.out.println("Coped with task: " + q.dequeue());
		}
	}
	
}