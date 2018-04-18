package lab3;

public class Queue {
	private String queue[];
	private int maxSize;
	private int curSize;
	private int head;
	private int tail;

	public Queue(int capacity) {
		maxSize=capacity;
		queue = new String[maxSize];
		curSize = 0;
		head = 0;
		tail = 0;
	}
	
	public boolean isEmpty() {
		return curSize == 0;
	}
	
	public boolean isFull() {
		return curSize == maxSize;
	}
	
	public void enqueue(String value) {
		if (isFull()){
			System.out.printf("The queue is full, cannot add '%s' element!\n", value);
		}
		else {
			if (tail == maxSize && head != 0) {
				tail = 0;
			}
			queue[tail] = value;
			tail++;
			curSize++;
		}
	}
	
	public String dequeue() {
		if (isEmpty()) {
			System.out.println("Nothing to dequeue, the queue is empty!");
			return "";
		}
		else {
			String del = queue[head];
			// queue[head] = "";
			if (head == maxSize - 1) {
				head = 0;
			}
			else {
				head++;
			}
			curSize--;
			return del;
		}
	}
	
	public void output(){
		int i;
		if (curSize == 0) {
			System.out.printf("The queue is empty, nothing to display!");
		}
		else {
			System.out.printf("Queue: ");
			if (tail > head) {
				for (i = head; i < tail; i++){
					System.out.printf("%s, ", queue[i]);
				}
			}
			else {
				for (i = head; i < maxSize; i++) {
					System.out.printf("%s, ", queue[i]);
				}
				for (i = 0; i < tail; i++) {
					System.out.printf("%s, ", queue[i]);
				}
			}
		}
		System.out.println("\n");
	}

}
