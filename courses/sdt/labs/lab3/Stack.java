package lab3;

public class Stack {
	private String stack[];
	private int maxSize;
	private int curSize;
	private int head;

	public Stack(int capacity) {
		maxSize = capacity;
		curSize = 0;
		stack = new String[maxSize];
		head = -1;
	}
	
	public boolean isEmpty() {
		return curSize == 0;
	}
	
	public boolean isFull() {
		return curSize == maxSize;
	}
	
	public void push(String value) {
		if (isFull()){
			System.out.printf("The stack is full, cannot add '%s' element!\n", value);
		}
		else {
			stack[++head] = value;
			curSize++;
		}
	}
	
	public String pop() {
		if (isEmpty()) {
			System.out.println("Nothing to pop, the stack is empty!");
			return "";
		}
		else {
			String del = stack[head--];
			// stack[head] = "";
			curSize--;
			return del;
		}
	}
	
	public void output(){
		int i;
		if (isEmpty()) {
			System.out.printf("The stack is empty, nothing to display!");
		}
		else {
			System.out.printf("Stack: ");
			for (i = head; i >= 0; i--) {
				System.out.printf("%s, ", stack[i]);
			}
		}
		System.out.println("\n");
	}
}
