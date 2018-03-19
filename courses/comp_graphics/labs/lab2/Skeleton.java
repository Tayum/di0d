package lab2;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.*;

import javax.swing.JPanel;
import javax.swing.Timer;


@SuppressWarnings("serial")
public class Skeleton extends JPanel implements ActionListener {
	
	private int maxWidth;
	private int maxHeight;
	
	private double angle;
	private double scale;
	private double delta;
	
	private Timer timer;

	
	public Skeleton() {
		maxWidth = 0;
		maxHeight = 0;
		
		angle = 0;
		scale = 1;
		delta = 0.01;
		
		timer = new Timer(10, this);
		timer.start();
	}
	
	public int getMaxWidth() {
		return maxWidth;
	}
	
	public void setMaxWidth(int maxWidth) {
		this.maxWidth = maxWidth;
	}
	
	public int getMaxHeight() {
		return maxHeight;
	}
	
	public void setMaxHeight(int maxHeight) {
		this.maxHeight = maxHeight;
	}
	
	public void paint(Graphics g) {
		Graphics2D g2d = (Graphics2D)g;
		RenderingHints rh = new RenderingHints(
				RenderingHints.KEY_ANTIALIASING,
				RenderingHints.VALUE_ANTIALIAS_ON);
		rh.put(RenderingHints.KEY_RENDERING,
				RenderingHints.VALUE_RENDER_QUALITY);
		g2d.setRenderingHints(rh);
		
		// BG Color:
		g2d.setBackground(Color.BLUE);
		g2d.clearRect(0, 0, maxWidth + 1, maxHeight + 1);
		
		// Drawing: Trunk
		// Task 1: common Rectangle
		g2d.setColor(new Color(120, 70, 0));
		g2d.fillRect(120, 165, 15, 50);
		
		g2d.setColor(new Color(0, 100, 0));
		double[][] trg_points;
		GeneralPath trg;
		
		// Drawing: upper_triangle
		// Task 1: point-based
		trg_points = new double[][] {
				{ 125, 25 }, { 110, 75 }, { 145, 75 }
		};
		trg = new GeneralPath();
		trg.moveTo(trg_points[0][0], trg_points[0][1]);
		for (int i = 1; i < trg_points.length; i++) {
			trg.lineTo(trg_points[i][0], trg_points[i][1]);
		}
		trg.closePath();
		g2d.fill(trg);
		
		// Drawing: middle_triangle
		// Task 1: point-based
		trg_points = new double[][] {
				{ 125, 55 }, { 105, 120 }, { 150, 120 }
		};
		trg = new GeneralPath();
		trg.moveTo(trg_points[0][0], trg_points[0][1]);
		for (int i = 1; i < trg_points.length; i++) {
			trg.lineTo(trg_points[i][0], trg_points[i][1]);
		}
		trg.closePath();
		g2d.fill(trg);
		
		// Drawing: bottom_triangle
		// Task 1: point-based
		trg_points = new double[][] {
				{ 125, 100 }, { 105, 165 }, { 150, 165 }
		};
		trg = new GeneralPath();
		trg.moveTo(trg_points[0][0], trg_points[0][1]);
		for (int i = 1; i < trg_points.length; i++) {
			trg.lineTo(trg_points[i][0], trg_points[i][1]);
		}
		trg.closePath();
		g2d.fill(trg);
		
		// Drawing: 3 squares
		// Task 1: common Rectangle
		g2d.setColor(new Color(255, 255, 0));
		g2d.fillRect(130, 90, 10, 10);
		g2d.fillRect(115, 105, 10, 10);
		g2d.fillRect(125, 130, 10, 10);
		
		// Drawing: Frame
		// Task 3: frame
		g2d.setColor(new Color(140, 0, 0));
		BasicStroke frameStroke = new BasicStroke(5, BasicStroke.CAP_ROUND,
				BasicStroke.JOIN_MITER);
		g2d.setStroke(frameStroke);
		g2d.drawRect(maxWidth / 2 + 25, maxHeight / 2 + 25, 250, 250);
		// Reset Stroke
		g2d.setStroke(new BasicStroke());
		
		// Drawing: gradiented Animated Object (Star has been chosen as the object to be animated)
		// Task 4: animated object
		// Task 2: gradient
		GradientPaint gp = new GradientPaint(5, 25,
				new Color(0, 255, 0), 20, 2, new Color(128, 0, 255), true);
		g2d.setPaint(gp);
		double[][] star_points;
		GeneralPath star;
		// Shifting the center of the coordinates
		// (maxWidth / 2 + 25) is the center of coordinates;
		// + 125 is the center of the "frame"
		g2d.translate(maxWidth / 2 + 25 + 125, maxHeight / 2 + 25 + 125);
		star_points = new double[][] {
				{ -100, -15 }, { -25, -25 }, { 0, -90 }, { 25, -25 },
				{ 100, -15 }, { 50, 25 }, { 60, 100 }, { 0, 50 },
				{ -60, 100 }, { -50, 25 }, { -100, -15 }
		};
		star = new GeneralPath();
		star.moveTo(star_points[0][0], star_points[0][1]);
		for (int i = 1; i < star_points.length; i++) {
			star.lineTo(star_points[i][0], star_points[i][1]);
		}
		star.closePath();
		
		// Turn animation
		g2d.rotate(angle, star.getBounds2D().getCenterX(), star.getBounds2D().getCenterY());
		// Scale animation
		g2d.scale(scale, 0.99);
		
		g2d.fill(star);
	}
	
	public void actionPerformed(ActionEvent e) {
		if (scale < 0.01 || scale > 0.99) {
			delta = -delta;
		}
		scale += delta;
		angle -= 0.01;
		repaint();
	}
	
}
