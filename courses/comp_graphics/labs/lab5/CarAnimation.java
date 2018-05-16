package lab5;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.media.j3d.*;
import javax.swing.JFrame;
import javax.swing.Timer;
import javax.vecmath.*;

public class CarAnimation implements ActionListener, KeyListener {
    private Button go;
    private TransformGroup wholeCar;
    private Transform3D translateTransform;
    private Transform3D tmpTransform;
    private JFrame mainFrame;
    
    private final float zoom = 0.5f;
    private float sign;
    private float xloc;
    private float speed;
    private float yloc;
    private float zloc;
    private float angle;
    private Timer timer;
    
    public CarAnimation(TransformGroup wholeCar, Transform3D trans, JFrame frame) {
    	setDefaultPositionValues();
    	
        go = new Button("Enable interaction");
        this.wholeCar = wholeCar;
        this.translateTransform = trans;
        this.mainFrame = frame;
        
        Lab5.canvas.addKeyListener(this);
        timer = new Timer(100, this);
        
        Panel p = new Panel();
        p.add(go);
        mainFrame.add("North", p);
        go.addActionListener(this);
        go.addKeyListener(this);
    }
    
    private void setDefaultPositionValues() {
        sign = 1.0f;
        xloc = 0.0f;
        yloc = 0.0f;
        zloc = 0.0f;
        speed = 0.0f;
        angle = 0.0f;
        tmpTransform = new Transform3D();
    }
    
    private void defaultState() {
    	setDefaultPositionValues();
        if (timer.isRunning()) {
        	timer.stop();
    	}
        go.setLabel("Enable interaction");
        
        translateTransform = new Transform3D();
        translateTransform.rotX(Math.PI/2);
        tmpTransform = new Transform3D();
        tmpTransform.rotY(Math.PI/2);
        translateTransform.mul(tmpTransform);
        translateTransform.setScale(new Vector3d(zoom, zoom, zoom));
        translateTransform.setTranslation(new Vector3f(xloc, yloc, zloc));
        wholeCar.setTransform(translateTransform);
    }
    
    @Override
    public void actionPerformed(ActionEvent e) {
       //  When the button was pressed
       if (e.getSource() == go){
    	  // if "Enable" was clicked
          if (!timer.isRunning()) {
        	  timer.start();
        	  go.setLabel("Disable interaction");
          }
          else {
        	  // if "Disable" was clicked
        	  defaultState();
          }
       }
       // if event is not referred to that button
       else {
           Move();
           translateTransform.setScale(new Vector3d(zoom, zoom, zoom));
           translateTransform.setTranslation(new Vector3f(xloc, yloc, zloc));
           wholeCar.setTransform(translateTransform);
       }
    }

    private void Move() {
    	if (speed != 0) {
    		if (speed > 0) {
    			xloc += (float)Math.cos(angle) * speed;
    			yloc += (float)Math.sin(angle) * speed;
    			speed -= 0.005;
    			speed = (float)(Math.round(speed * 1000.0) / 1000.0);
    		}
    		else if (speed < 0) {
    			xloc += (float)Math.cos(angle) * speed;
    			yloc += (float)Math.sin(angle) * speed;
    			speed += 0.005;
    			speed = (float)(Math.round(speed * 1000.0) / 1000.0);
    		}
    	}
    }
    
    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyPressed(KeyEvent e) {
        if (e.getKeyChar() == 'w') {
        	speed += 0.01;
        	xloc += (float)Math.cos(angle) * 0.01f;
        	yloc += (float)Math.sin(angle) * 0.01f;
    	}
        if (e.getKeyChar() == 's') {
        	speed -= 0.01;
        	xloc -= (float)Math.cos(angle) * 0.01f;
        	yloc -= (float)Math.sin(angle) * 0.01f;
    	}
        if (e.getKeyChar() == 'a') {
        	angle += Math.PI/45;
            tmpTransform.rotY(Math.PI/45);
            translateTransform.mul(tmpTransform);
        }
        if (e.getKeyChar() == 'd') {
        	angle -= Math.PI/45;
            tmpTransform.rotY(-Math.PI/45);
            translateTransform.mul(tmpTransform);
    	}
        if(e.getKeyChar() == '0') {
            tmpTransform.rotZ(Math.PI/2);
            translateTransform.mul(tmpTransform);
        }
    }
    
    @Override
    public void keyReleased(KeyEvent e) {
    	
    }
    
}
