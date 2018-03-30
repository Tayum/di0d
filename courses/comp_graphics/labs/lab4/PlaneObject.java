package lab4;

import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import com.sun.j3d.utils.geometry.*;
import com.sun.j3d.utils.image.TextureLoader;
import com.sun.j3d.utils.universe.SimpleUniverse;

import javax.media.j3d.*;
import javax.swing.Timer;
import javax.vecmath.*;

public class PlaneObject implements ActionListener {
	private Transform3D t3d_plane;
	private TransformGroup tg_plane;
	private float angle;
	private Timer timer;


	public PlaneObject() {
		t3d_plane = new Transform3D();
		tg_plane = new TransformGroup();
		angle = 0;
		timer = new Timer(50, this);
		timer.start();
		
		// It is crucial to create branch first, then create The Universe
		BranchGroup branch = createBranch();
		SimpleUniverse universe = new SimpleUniverse();
		universe.getViewingPlatform().setNominalViewingTransform();
		universe.addBranchGraph(branch);
	}

	
	public BranchGroup createBranch() {
		BranchGroup root = new BranchGroup();
		// allow to transform the objects in tg_plane(rotation)
		tg_plane.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		
		TransformGroup[] details = createPlane();
		for (int i = 0; i < details.length; i++) {
			tg_plane.addChild(details[i]);
		}
		root.addChild(tg_plane);

		// create white color
		Color3f light1Color = new Color3f(0.5f, 0.5f, 0.5f);
		BoundingSphere bounds =	new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 100.0);
		Vector3f light1Direction = new Vector3f(4.0f, -7.0f, -12.0f);
		DirectionalLight light1	= new DirectionalLight(light1Color, light1Direction);
		light1.setInfluencingBounds(bounds);
		root.addChild(light1);

		// create non-directional light
		AmbientLight ambientLight =	new AmbientLight(new Color3f(.5f, .5f, .5f));
		ambientLight.setInfluencingBounds(bounds);
		root.addChild(ambientLight);
		return root;
	}
	
	// get appearance (returns the same metal appearance every time)
	private Appearance getAppearance(boolean isPicture) {
		Appearance ap = new Appearance();
		// (0.0f, 0.0f, 0.0f);
		Color3f emissive = new Color3f(0.0f, 0.0f, 0.0f);
		// (0.9f, .15f, .15f);
		Color3f ambient = new Color3f(0.2f, 0.2f, 0.2f);
		// (0.7f, .15f, .15f);
		Color3f diffuse = new Color3f(1f, 1f, 1f);
		// (0.0f, 0.0f, 0.0f);
		Color3f specular = new Color3f(0.25f, 0.25f, 0.25f);
		
		// set new material
		ap.setMaterial(new Material(ambient, emissive, diffuse, specular, 0.5f));

		// should the metal pattern picture be used
		if (isPicture) {
			// texture
			TextureLoader loader = new TextureLoader(System.getProperty("user.dir") + "\\misc\\lab4\\pattern.jpg", "RGB", new Container());
			Texture texture = loader.getTexture();
			// wrap borders
			texture.setBoundaryModeS(Texture.WRAP);
			texture.setBoundaryModeT(Texture.WRAP);
			// set color
			//texture.setBoundaryColor(new Color4f(0.0f, 1.0f, 1.0f, 0.0f));
			
			// texture attr
			TextureAttributes texAttr = new TextureAttributes();
			texAttr.setTextureMode(TextureAttributes.REPLACE);

			// add texture to appearance
			ap.setTexture(texture);
			ap.setTextureAttributes(texAttr);
		}
		return ap;
	}
	
	// create one of the details of the airplane
	private TransformGroup createDetail(String detailName) {
		TransformGroup tg = new TransformGroup();
		Transform3D t3d = new Transform3D();
		int primflags = Primitive.GENERATE_NORMALS + Primitive.GENERATE_TEXTURE_COORDS;
		
		// "Primitive" is the base class for any of the shapes
		// that will be created
		Primitive detail = null;
		Vector3f translateVector = null;
		Transform3D temp = null;
		switch(detailName) {
		case "BODY":
			detail = new Cylinder(0.1f, 0.8f, primflags, getAppearance(true));
			translateVector = new Vector3f(0f, -0.4f, 0f);
			t3d.rotX(-Math.PI / 2);
			break;
		case "CABIN":
			detail = new Sphere(0.1f, primflags, getAppearance(true));
			translateVector = new Vector3f(0f, -0.4f, 0.4f);
			break;
		case "NOSE":
			detail = new Cone(0.1f, 0.2f, primflags, getAppearance(true));
			translateVector = new Vector3f(0f, -0.4f, 0.5f);
			t3d.rotX(Math.PI / 2);
			break;
		case "TAIL":
			detail = new Box(0.01f, 0.1f, 0.099f, primflags, getAppearance(true));
			translateVector = new Vector3f(0f, -0.3f, -0.3f);
			break;
		case "LWING":
			detail = new Box(0.02f, 0.3f, 0.1f, primflags, getAppearance(true));
			translateVector = new Vector3f(0.25f, -0.4f, 0.05f);
			temp = new Transform3D();
			temp.rotX(Math.PI / 4);
			t3d.rotZ(Math.PI / 2);
			// multiply 2 transformation matrices
			t3d.mul(temp);
			break;
		case "RWING":
			detail = new Box(0.02f, 0.3f, 0.1f, primflags, getAppearance(true));
			translateVector = new Vector3f(-0.25f, -0.4f, 0.05f);
			temp = new Transform3D();
			temp.rotX(- Math.PI / 4);
			t3d.rotZ(Math.PI / 2);
			// multiply 2 transformation matrices
			t3d.mul(temp);
			break;
		default:
			// sphere with radius 0 (this case should not be actually used!)
			detail = new Sphere(0.0f, primflags, getAppearance(true));
			translateVector = new Vector3f(0f, 0f, 0f);
			break;
		}
		
		t3d.setTranslation(translateVector);
		tg.setTransform(t3d);
		tg.addChild(detail);
		return tg;
	}
	
	// create all the details
	// and return them
	private TransformGroup[] createPlane() {
		return new TransformGroup[] {
				// body
				createDetail("BODY"),
				// cabin
				createDetail("CABIN"),
				// nose of the cabin
				createDetail("NOSE"),
				// tail
				createDetail("TAIL"),
				// left wing
				createDetail("LWING"),
				// right wing
				createDetail("RWING")
		};
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		t3d_plane.rotY(angle);
		tg_plane.setTransform(t3d_plane);
		angle -= Math.PI / 45;
	}
}
