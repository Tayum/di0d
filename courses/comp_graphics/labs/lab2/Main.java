package lab2;

import java.awt.*;
import javax.swing.JFrame;

public class Main {

	public static void main(String[] args) {
		JFrame frame = new JFrame("Computer Graphics: Lab 2");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(650, 650);
		frame.setLocationRelativeTo(null);
		frame.setResizable(false);
		
		Skeleton skeleton = new Skeleton();
		frame.add(skeleton);
		
		frame.setVisible(true);
		Dimension size = frame.getSize();
		Insets insets = frame.getInsets();
		skeleton.setMaxWidth(size.width - insets.left - insets.right - 1);
		skeleton.setMaxHeight(size.height - insets.top - insets.bottom - 1);
		
		// System.out.println("The program is working...");
	}
	
}
