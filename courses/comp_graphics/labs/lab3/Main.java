package lab3;

import javafx.animation.ParallelTransition;
import javafx.animation.PathTransition;
import javafx.animation.RotateTransition;
import javafx.animation.ScaleTransition;
import javafx.application.Application;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.media.MediaView;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Ellipse;
import javafx.scene.shape.MoveTo;
import javafx.scene.shape.Path;
import javafx.scene.shape.Polygon;
import javafx.scene.shape.QuadCurveTo;
import javafx.scene.shape.Shape;
import javafx.scene.shape.StrokeLineJoin;
import javafx.stage.Stage;
import javafx.util.Duration;

public class Main extends Application {

	@Override
	public void start(Stage primaryStage) throws Exception {
		primaryStage.setTitle("Computer Graphics: Lab 3");
		primaryStage.setResizable(false);
		Group root = new Group();
		Scene scene = new Scene(root, 852, 400, Color.web("AAD8F1"));
		
		// body
		Circle body = new Circle(20, 380, 40);
		body.setFill(Color.web("000000"));
		
        // bottom_body
		Circle temp = new Circle(20, 440, 40);
	    Shape bottom_body = Shape.intersect(body, temp);
	    bottom_body.setFill(Color.web("434343"));
	    
	    // left_eye
	    Circle left_eye_base = new Circle(10, 365, 10);
	    left_eye_base.setFill(Color.web("434343"));
	    
	    Shape left_eye_white = new Circle(12.5, 365 - 2.5f * 1.5f, 6.25);
	    Circle temp1 = new Circle(12.5, 372.5, 7.5);
	    left_eye_white = Shape.subtract(left_eye_white, temp1);
	    left_eye_white.setFill(Color.web("FFFFFF"));
	    left_eye_white.setStroke(Color.web("0A0A0A"));
	    left_eye_white.setStrokeWidth(1);
	    left_eye_white.setStrokeLineJoin(StrokeLineJoin.ROUND);
	    
	    Circle left_eye_dot = new Circle(15, 365 - 2.5f * 1.5f, 2.5);
	    
	    Polygon left_eye_brow = new Polygon(
	    		15, 360,
	    		20, 357.5,
	    		7.5, 337.5,
	    		-2.5, 342.5
	    		);
	    left_eye_brow.setFill(Color.web("B44806"));
	    
	    // right_eye
	    Circle right_eye_base = new Circle(40, 365, 10);
	    right_eye_base.setFill(Color.web("434343"));
	    
	    Shape right_eye_white = new Circle(42.5, 365 - 2.5f * 1.5f, 6.25);
	    Circle temp2 = new Circle(36.25, 368.75, 7.5);
	    right_eye_white = Shape.subtract(right_eye_white, temp2);
	    right_eye_white.setFill(Color.web("FFFFFF"));
	    right_eye_white.setStroke(Color.web("0A0A0A"));
	    right_eye_white.setStrokeWidth(1);
	    right_eye_white.setStrokeLineJoin(StrokeLineJoin.ROUND);
	    
	    Circle right_eye_dot = new Circle(45, 365 - 2.5f * 1.5f, 3);
	    
	    Polygon right_eye_brow = new Polygon(
	    		35, 362.5,
	    		30, 360,
	    		47.5, 342.5,
	    		55, 345
	    		);
	    right_eye_brow.setFill(Color.web("B44806"));
	    
	    // white dot on forehead
	    Circle white_dot_forehead = new Circle(25, 350, 5);
	    white_dot_forehead.setFill(Color.web("#FEFEFE"));
	    
	    // forelock
	    Shape forelock = new Polygon(
	    		20, 345,
	    		35, 345,
	    		25, 335,
	    		12.5, 327.5,
	    		-2.5, 322.5,
	    		-5, 332.5,
	    		5, 337.5
	    		);
	    forelock.setFill(Color.web("000000"));
	    Ellipse temp3 = new Ellipse(-3.75, 327.5, 4, 5);
	    temp3.setFill(Color.web("000000"));
	    forelock = Shape.union(forelock, temp3);
	    forelock.setStroke(Color.web("000000"));
	    forelock.setStrokeWidth(1.5);
	    forelock.setStrokeLineJoin(StrokeLineJoin.ROUND);
	    
	    // yellow forelock
	    Polygon yellow_forelock = new Polygon(
	    		-3.25, 330,
	    		-3.75, 327.5,
	    		-3.25, 325.5,
	    		4.25, 328,
	    		2.75, 330.5,
	    		4.25, 333
	    		);
	    yellow_forelock.setFill(Color.web("FFB707"));
	    
	    // upper lip
	    Polygon upper_lip = new Polygon(
	    		20, 380,
	    		22.5, 372.5,
	    		35, 370,
	    		45, 372.5,
	    		50, 375,
	    		52.5, 377.5,
	    		35, 379.25,
	    		20, 378.75
	    		);
	    upper_lip.setFill(Color.web("FEA704"));
	    upper_lip.setStroke(Color.web("000000"));
	    upper_lip.setStrokeWidth(1);
	    upper_lip.setStrokeLineJoin(StrokeLineJoin.ROUND);
	    
	    // teeth
	    Shape teeth = new Polygon(
	    		35, 380.25,
	    		20, 379.75,
	    		22.5, 383.25
	    		);
	    Ellipse temp4 = new Ellipse(21.25, 382.25, 1.25, 1.75);
	    teeth = Shape.union(teeth, temp4);
	    teeth.setFill(Color.web("FCF6FF"));
	    
	    // lower_lip
	    Polygon lower_lip = new Polygon(
	    		22.5, 384.25,
	    		36, 380.5,
	    		47.5, 378.5,
	    		40.5, 388,
	    		32.5, 393,
	    		25, 395
	    		);
	    lower_lip.setFill(Color.web("FEA704"));
	    
	    
	    // video 
	    MediaPlayer mp = new MediaPlayer(new Media(getClass().getResource("Explosion.mp4").toExternalForm()));
		MediaView media = new MediaView(mp);
		media.setTranslateX(-750);
		media.setTranslateY(500);
	    media.setFitHeight(600);
	    media.setFitWidth(600);
	    media.setVisible(false);
	    media.setRotate(-45);
	    
	    
		// initial angle -45 degrees
		root.setRotate(-45);
		root.getChildren().add(body);
		root.getChildren().add(bottom_body);
		root.getChildren().add(left_eye_base);
		root.getChildren().add(left_eye_white);
		root.getChildren().add(left_eye_dot);
		root.getChildren().add(left_eye_brow);
		root.getChildren().add(right_eye_base);
		root.getChildren().add(right_eye_white);
		root.getChildren().add(right_eye_dot);
		root.getChildren().add(right_eye_brow);
		root.getChildren().add(white_dot_forehead);
		root.getChildren().add(forelock);
		root.getChildren().add(yellow_forelock);
		root.getChildren().add(upper_lip);
		root.getChildren().add(teeth);
		root.getChildren().add(lower_lip);
		root.getChildren().add(media);	
		
		
		// Movement animation: Arc
		Path path = new Path();
		path.getElements().add(new MoveTo(20, 380));
		path.getElements().add(new QuadCurveTo(386, -250, 812, 360));
		PathTransition pathTransition = new PathTransition();
		pathTransition.setDuration(Duration.millis(4000));
		pathTransition.setPath(path);
		pathTransition.setNode(root);
		
		// Movement rotation: Arc (-45...45 degrees)
		RotateTransition rotateTransition =
		new RotateTransition(Duration.millis(4000), root);
		rotateTransition.setByAngle(90.0f);
		
		// Scaling the object to 1.5x...
		ScaleTransition scaleTransition =
		new ScaleTransition(Duration.millis(2000), root);
		scaleTransition.setToX(1.5f);
		scaleTransition.setToY(1.5f);
		// ...and back to 1.0x
		scaleTransition.setCycleCount(2);
		scaleTransition.setAutoReverse(true);
		
		// parallel animation
		ParallelTransition parallelTransition =
		new ParallelTransition();
		parallelTransition.getChildren().addAll(
			pathTransition,
			rotateTransition,
			scaleTransition
		);
		// play animation
		parallelTransition.play();

		// video
		new java.util.Timer().schedule(
				new java.util.TimerTask() {
					@Override
					public void run() {
						media.setVisible(true);
						mp.play();
					}
				}, 3900
				);
		
		// Init scene
		primaryStage.setScene(scene);
		// Visualize scene
		primaryStage.show();
	}

	public static void main(String args[]) {
		launch(args);
	}
}
