package lab1;
import javafx.application.Application;
import javafx.stage.Stage;

import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.*;


public class Main extends Application {

	public static void main(String[] args) {
		launch(args);
		System.out.println("The program has finished working.");
	}
	
	@Override
	public void start(Stage primaryStage) {
		primaryStage.setTitle("Computer Graphics: Lab 1");
		Group root = new Group();
		Scene scene = new Scene(root, 350, 350, Color.CORNFLOWERBLUE);
		
		Rectangle rect = new Rectangle(120, 165, 15, 50);
		rect.setFill(Color.DARKRED);
		root.getChildren().add(rect);
		
		Polygon top_triangle = new Polygon(125, 25, 110, 75, 145, 75);
		top_triangle.setFill(Color.rgb(0, 128, 0));
		root.getChildren().add(top_triangle);
		
		Polygon middle_triangle = new Polygon(125, 55, 105, 120, 150, 120);
		middle_triangle.setFill(Color.rgb(0, 128, 0));
		root.getChildren().add(middle_triangle);
		middle_triangle = null;
		Polygon bottom_triangle = new Polygon(125, 100, 105, 165, 150, 165);
		bottom_triangle.setFill(Color.rgb(0, 128, 0));
		root.getChildren().add(bottom_triangle);
		
		Rectangle square_1 = new Rectangle(130, 90, 10, 10);
		square_1.setFill(Color.YELLOW);
		root.getChildren().add(square_1);
		
		Rectangle square_2 = new Rectangle(115, 105, 10, 10);
		square_2.setFill(Color.YELLOW);
		root.getChildren().add(square_2);
		
		Rectangle square_3 = new Rectangle(125, 130, 10, 10);
		square_3.setFill(Color.YELLOW);
		root.getChildren().add(square_3);
		
		primaryStage.setScene(scene);
		primaryStage.show();
	}

}
