package lab6;

import javax.vecmath.*;
import com.sun.j3d.utils.universe.*;
import javax.media.j3d.*;
import com.sun.j3d.utils.behaviors.vp.*;
import com.sun.j3d.utils.image.TextureLoader;
import javax.swing.JFrame;
import com.sun.j3d.loaders.*;
import com.sun.j3d.loaders.objectfile.*;
import java.util.Hashtable;
import java.util.ArrayList;
import java.util.Enumeration;

public class WarriorInteraction extends JFrame {
	public Canvas3D myCanvas3D;
	public final String path = System.getProperty("user.dir") + "/misc/lab6/";
	
	public WarriorInteraction() {
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		myCanvas3D = new Canvas3D(SimpleUniverse.getPreferredConfiguration());
		SimpleUniverse simpUniv = new SimpleUniverse(myCanvas3D);
		simpUniv.getViewingPlatform().setNominalViewingTransform();
		createSceneGraph(simpUniv);
		addLight(simpUniv);
		setTitle("Computer Graphics Lab 6");
		setSize(700, 700);
		getContentPane().add("Center", myCanvas3D);
		setVisible(true);
	}

	// Create objects and add them to scene
	public void createSceneGraph(SimpleUniverse su) {
		ObjectFile file = new ObjectFile(ObjectFile.RESIZE);
		Scene warrior_scene = null;
		
		try {
			warrior_scene = file.load(path + "warrior.obj");
		} catch (Exception e) {
			System.out.println("Failed to load .obj file: " + e);
		}
		
		Hashtable warrior_parts = warrior_scene.getNamedObjects();
		Enumeration enumer = warrior_parts.keys();
		String name;
		// Black App
		Appearance blackApp = new Appearance();
		setToMyDefaultAppearance(blackApp, new Color3f(0.0f, 0.0f, 0.0f));
		// Grey App
		Appearance greyApp = new Appearance();
		setToMyDefaultAppearance(greyApp, new Color3f(0.1f, 0.1f, 0.1f));
		// Red App
		Appearance redApp = new Appearance();
		setToMyDefaultAppearance(redApp, new Color3f(0.2f, 0.0f, 0.0f));
		// Skin App
		Appearance skinApp = new Appearance();
		setToMyDefaultAppearance(skinApp, new Color3f(0.55f, 0.55f, 0.25f));
		
		// Print all the parts
		while (enumer.hasMoreElements())
		{
			name = (String)enumer.nextElement();
			System.out.println("Part name: " + name);
		}
		
		// head shape
		Shape3D head_shape = (Shape3D) ((Shape3D) warrior_parts.get("head")).cloneTree();
		head_shape.setUserData("head");
		head_shape.setAppearance(skinApp);
		
		// chest shape
		Shape3D chest_shape = (Shape3D) ((Shape3D) warrior_parts.get("group1_____02")).cloneTree();
		chest_shape.setUserData("chest");
		chest_shape.setAppearance(blackApp);
		
		// legs shape
		Shape3D legs_shape = (Shape3D) ((Shape3D) warrior_parts.get("group1_____01")).cloneTree();
		legs_shape.setUserData("legs");
		legs_shape.setAppearance(redApp);
		
		// left hand shape
		Shape3D lhand_shape = (Shape3D) ((Shape3D) warrior_parts.get("left_hand")).cloneTree();
		lhand_shape.setUserData("lhand");
		lhand_shape.setAppearance(skinApp);

		// right hand shape
		Shape3D rhand_shape = (Shape3D) ((Shape3D) warrior_parts.get("right_hand")).cloneTree();
		rhand_shape.setUserData("rhand");
		rhand_shape.setAppearance(skinApp);
		
		// axe shape
		Shape3D axe_shape = (Shape3D) ((Shape3D) warrior_parts.get("box02_group1")).cloneTree();
		axe_shape.setUserData("axe");
		axe_shape.setAppearance(greyApp);
		
		// Our main variables that we will later add to our Universe
		TransformGroup head = translate(head_shape, new Vector3f(0, 0, -0.75f));
		TransformGroup chest = translate(chest_shape, new Vector3f(0, 0, -0.75f));
		TransformGroup legs = translate(legs_shape, new Vector3f(0, 0, -0.75f));
		TransformGroup lhand = translate(lhand_shape, new Vector3f(0, 0, -0.75f));
		TransformGroup rhand = translate(rhand_shape, new Vector3f(0, 0, -0.75f));
		TransformGroup axe = translate(axe_shape, new Vector3f(0.2f, 0.25f, -0.75f));

		// Take bounds from the centered part: from chest
		BoundingSphere bounds = (BoundingSphere)chest.getBounds();
		
		
		// ==========1. TAKE THE AXE==========
		float takeaxe_angle_start = 0.0f;
		float takeaxe_angle_end = (float)Math.PI / 4;
		
		// add the elements that will be changed to the list (for mass translate or rotation)
		ArrayList<TransformGroup> takeaxe_tg = new ArrayList<TransformGroup>();
		takeaxe_tg.add(lhand);
		
		// No movement until additional action from user
		Alpha takeaxe_alpha = new Alpha(1, 2000);
		takeaxe_alpha.setStartTime(Long.MAX_VALUE);
		// Move hand to axe
		for(int i = 0; i < takeaxe_tg.size(); i++) {
			TransformGroup part = takeaxe_tg.remove(i);
			part = takeAxe(part, takeaxe_alpha, takeaxe_angle_start, takeaxe_angle_end);
			takeaxe_tg.add(i, part);
		}
		
		// The axe is taken, so we add him to our TransformGroup List
		takeaxe_tg.add(axe);
		
		// No movement until additional action from user
		Alpha takeaxe_alpha2 = new Alpha(1, 2000);
		takeaxe_alpha2.setStartTime(Long.MAX_VALUE);
		// Move hand with axe back
		for(int i = 0; i < takeaxe_tg.size(); i++) {
			TransformGroup part = takeaxe_tg.remove(i);
			part = takeAxe(part, takeaxe_alpha2, takeaxe_angle_start, -takeaxe_angle_end);
			takeaxe_tg.add(i, part);
		}
		
		// re-assign our main variables for their translated/rotated analogs
		// FOLLOW THE SAME ORDER WITH THE ORDER IN WHICH THEY WERE BEING ADDED!
		lhand = takeaxe_tg.remove(0);
		axe = takeaxe_tg.remove(0);
		// ===================================
		
		
		// ==========2. MOVE THE HEAD==========
		float movehead_angle_start = 0.0f;
		float movehead_angle_end = -(float)Math.PI / 2;
		
		// add the elements that will be changed to the list (for mass translate or rotation)
		ArrayList<TransformGroup> movehead_tg = new ArrayList<TransformGroup>();
		movehead_tg.add(head);
		
		// No movement until additional action from user
		Alpha movehead_alpha = new Alpha(1, 1000);
		movehead_alpha.setStartTime(Long.MAX_VALUE);
		// Look right
		for(int i = 0; i < movehead_tg.size(); i++) {
			TransformGroup part = movehead_tg.remove(i);
			part = moveHead(part, movehead_alpha, movehead_angle_start, movehead_angle_end);
			movehead_tg.add(i, part);
		}
		// No movement until additional action from user
		Alpha movehead_alpha2 = new Alpha(1, 1000);
		movehead_alpha2.setStartTime(Long.MAX_VALUE);
		// Look back
		for(int i = 0; i < movehead_tg.size(); i++) {
			TransformGroup part = movehead_tg.remove(i);
			part = moveHead(part, movehead_alpha2, movehead_angle_start, -movehead_angle_end);
			movehead_tg.add(i, part);
		}
		
		// re-assign our main variables for their translated/rotated analogs
		// FOLLOW THE SAME ORDER WITH THE ORDER IN WHICH THEY WERE BEING ADDED!
		head = movehead_tg.remove(0);
		// =====================================
		
		
		// ==========3. ATTACK==========
		float attack_angle_start = 0.0f;
		float attack_angle_end = -(float)Math.PI / 4;
		
		// add the elements that will be changed to the list (for mass translate or rotation)
		ArrayList<TransformGroup> attack_tg = new ArrayList<TransformGroup>();
		attack_tg.add(lhand);
		attack_tg.add(axe);
		
		// No movement until additional action from user
		Alpha attack_alpha = new Alpha(1, 200);
		attack_alpha.setStartTime(Long.MAX_VALUE);
		// swing axe
		for(int i = 0; i < attack_tg.size(); i++) {
			TransformGroup part = attack_tg.remove(i);
			part = attack(part, attack_alpha, attack_angle_start, attack_angle_end);
			attack_tg.add(i, part);
		}
		
		// No movement until additional action from user
		Alpha attack_alpha2 = new Alpha(1, 200);
		attack_alpha2.setStartTime(Long.MAX_VALUE);
		// reverse swing axe
		for(int i = 0; i < attack_tg.size(); i++) {
			TransformGroup part = attack_tg.remove(i);
			part = attack(part, attack_alpha2, attack_angle_start, -attack_angle_end);
			attack_tg.add(i, part);
		}
		
		// re-assign our main variables for their translated/rotated analogs
		// FOLLOW THE SAME ORDER WITH THE ORDER IN WHICH THEY WERE BEING ADDED!
		lhand = attack_tg.remove(0);
		axe = attack_tg.remove(0);
		// =============================
		
		
		// Create the scene
		BranchGroup theScene = new BranchGroup();
		theScene.addChild(head);
		theScene.addChild(legs);
		theScene.addChild(chest);
		theScene.addChild(axe);
		theScene.addChild(lhand);
		theScene.addChild(rhand);
		
		// Create white bg
		Background bg = new Background(new Color3f(1.0f, 1.0f, 1.0f));
		bg.setApplicationBounds(bounds);
		theScene.addChild(bg);
		
		Alpha[] alphas = new Alpha[6];
		alphas[0] = takeaxe_alpha;
		alphas[1] = takeaxe_alpha2;
		alphas[2] = movehead_alpha;
		alphas[3] = movehead_alpha2;
		alphas[4] = attack_alpha;
		alphas[5] = attack_alpha2;
		PickingObjects pickingObjects = new PickingObjects(myCanvas3D, theScene, bounds, alphas);
		theScene.addChild(pickingObjects);
		theScene.compile();
		
		su.addBranchGraph(theScene);
	}

	// Method for generating the outer surface
	public static void setToMyDefaultAppearance(Appearance app, Color3f col) {
		app.setMaterial(new Material(col, col, col, col, 150.0f));
	}

	// Method for adding the light
	public void addLight(SimpleUniverse su) {
		BranchGroup bgLight = new BranchGroup();
		BoundingSphere bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 100.0);
		Color3f lightColour1 = new Color3f(1.0f, 1.0f, 1.0f);
		Vector3f lightDir1 = new Vector3f(-1.0f, 0.0f, -0.5f);
		DirectionalLight light1 = new DirectionalLight(lightColour1, lightDir1);
		light1.setInfluencingBounds(bounds);
		bgLight.addChild(light1);
		su.addBranchGraph(bgLight);
	}

	// Method for doing needed translations/rotations for taking the axe
	TransformGroup takeAxe(Node node, Alpha alpha, float startAngle, float endAngle) {
		Transform3D trans = new Transform3D();
		trans.setTranslation(new Vector3d(0.0f, 0.4f, -0.2f));

		Transform3D rot = new Transform3D();
		rot.rotX(Math.PI / 2);
		rot.mul(trans);

		TransformGroup xformGroup = new TransformGroup();
		xformGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		RotationInterpolator interpolator = new RotationInterpolator(alpha, xformGroup, rot, startAngle, endAngle);
		interpolator.setSchedulingBounds(new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 1.0));
		xformGroup.addChild(interpolator);

		xformGroup.addChild(node);
		return xformGroup;
	}
	
	// Method for doing needed translations/rotations for moving the head
	TransformGroup moveHead(Node node, Alpha alpha, float startAngle, float endAngle) {
		Transform3D trans = new Transform3D();
		trans.setTranslation(new Vector3d(0.875f, 0f, -0.15f));

		Transform3D rot = new Transform3D();
		rot.rotY(Math.PI / 2);
		rot.mul(trans);

		TransformGroup xformGroup = new TransformGroup();
		xformGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		RotationInterpolator interpolator = new RotationInterpolator(alpha, xformGroup, rot, startAngle, endAngle);
		interpolator.setSchedulingBounds(new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 1.0));
		xformGroup.addChild(interpolator);

		xformGroup.addChild(node);
		return xformGroup;
	}
	
	// Method for doing needed translations/rotations for attack
	TransformGroup attack(Node node, Alpha alpha, float startAngle, float endAngle) {
		Transform3D trans = new Transform3D();
		trans.setTranslation(new Vector3d(0.875f, 0f, -0.15f));
		
		Transform3D rot = new Transform3D();
		rot.rotY(Math.PI / 2);
		rot.mul(trans);

		TransformGroup xformGroup = new TransformGroup();
		xformGroup.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		RotationInterpolator interpolator = new RotationInterpolator(alpha, xformGroup, rot, startAngle, endAngle);
		interpolator.setSchedulingBounds(new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 1.0));
		xformGroup.addChild(interpolator);

		xformGroup.addChild(node);
		return xformGroup;
	}

	// Method for doing translations to object (i.e. moving the object)
	TransformGroup translate(Node node, Vector3f vector) {
		Transform3D transform3D = new Transform3D();
		transform3D.setTranslation(vector);
		TransformGroup transformGroup = new TransformGroup();
		transformGroup.setTransform(transform3D);
		transformGroup.addChild(node);
		return transformGroup;
	}
}