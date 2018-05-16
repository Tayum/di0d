package lab5;

import com.sun.j3d.utils.universe.*;

import java.awt.Color;
import javax.media.j3d.*;
import javax.media.j3d.Material;
import javax.vecmath.*;
import javax.media.j3d.Background;

import com.sun.j3d.loaders.*;
import com.sun.j3d.loaders.objectfile.ObjectFile;
import com.sun.j3d.loaders.lw3d.Lw3dLoader;
import com.sun.j3d.utils.image.TextureLoader;
import java.awt.*;
import java.io.FileReader;
import java.io.IOException;
import java.util.Map;
import javax.swing.JFrame;

public class Lab5 extends JFrame {
    static SimpleUniverse universe;
    static Scene scene;
    static Map<String, Shape3D> nameMap;
    static BranchGroup root;
    static Canvas3D canvas;
    
    static TransformGroup wholeCar;
    static Transform3D transform3D;
    
    public Lab5 () throws IOException{
        configureWindow();
        configureCanvas();
        configureUniverse();
        addModelToUniverse();
        setCarElementsList();
        addAppearance();
        addImageBackground();
        addLightToUniverse();
        addOtherLight();
        ChangeViewAngle();
        root.compile();
        universe.addBranchGraph(root);
    }
    
    private void configureWindow() {
        setTitle("Computer Graphics: Lab 5");
        setSize(1000, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    private void configureCanvas() {
        canvas = new Canvas3D(SimpleUniverse.getPreferredConfiguration());
        canvas.setDoubleBufferEnable(true);
        getContentPane().add(canvas, BorderLayout.CENTER);
    }
    
    private void configureUniverse() {
        root = new BranchGroup();
        universe = new SimpleUniverse(canvas);
        universe.getViewingPlatform().setNominalViewingTransform();
    }
    
    public static Scene getSceneFromObjFile(String location) throws IOException {
        ObjectFile file = new ObjectFile(ObjectFile.RESIZE);
        file.setFlags (ObjectFile.RESIZE | ObjectFile.TRIANGULATE | ObjectFile.STRIPIFY);
        return file.load(new FileReader(location));
    }
    
    // Doesn't work at all
    public static Scene getSceneFromLwoFile(String location) throws IOException {
        Lw3dLoader loader = new Lw3dLoader();
        return loader.load(new FileReader(location));
    }
    
    private void addModelToUniverse() throws IOException {
    	scene = getSceneFromObjFile(System.getProperty("user.dir") + "\\misc\\lab5\\mitsubishi\\L200-OBJ.obj");
    	// Doesn't work with 1/7/8/9.6 versions of LWO
        // scene = getSceneFromLwoFile(System.getProperty("user.dir") + "\\misc\\lab5\\car.lwo");
        root=scene.getSceneGroup();
    }
    
    private void printModelElementsList(Map<String, Shape3D> nameMap) {
    	System.out.println("Elements: ");
        for (String elem: nameMap.keySet()) {
            System.out.printf("Element: %s\n", elem);
        }
    }
    
    private void setCarElementsList() {
        nameMap = scene.getNamedObjects();
        printModelElementsList(nameMap);
      
        wholeCar = new TransformGroup();
        
        transform3D = new Transform3D();
        transform3D.rotX(Math.PI/2);
        Transform3D tmp = new Transform3D();
        tmp.rotY(Math.PI/2);
        tmp.setScale(new Vector3d(0.5, 0.5, 0.5));
        transform3D.mul(tmp);
        
        
        wholeCar.setTransform(transform3D);
        for (String elem: nameMap.keySet()) {
        	root.removeChild(nameMap.get(elem));
            wholeCar.addChild(nameMap.get(elem));
        }
        wholeCar.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
        root.addChild(wholeCar);
    }
    
    Texture getTexture(String path) {
        TextureLoader textureLoader = new TextureLoader(path, "LUMINANCE", canvas);
        Texture texture = textureLoader.getTexture();
        texture.setBoundaryModeS(Texture.WRAP);
        texture.setBoundaryModeT(Texture.WRAP);
        texture.setBoundaryColor(new Color4f(0.0f, 1.0f, 0.0f, 0.0f));
        return texture;
    }             
    
    Material getMaterial() {
        Material material = new Material();
        material.setAmbientColor (new Color3f(0.5f, 0f, 0.25f));
        material.setDiffuseColor (new Color3f(1f, 0f, 0f));
        material.setSpecularColor(new Color3f(0.25f, 0.75f, 0.5f));
        material.setShininess(0.3f);
        material.setLightingEnable(true);
        return material;
    }
    
    private void addAppearance() {
        Appearance planeAppearance = new Appearance();
        planeAppearance.setTexture(getTexture(System.getProperty("user.dir") + "\\misc\\lab5\\metallic.jpg"));
        TextureAttributes texAttr = new TextureAttributes();
        texAttr.setTextureMode(TextureAttributes.COMBINE);
        planeAppearance.setTextureAttributes(texAttr);
        planeAppearance.setMaterial(getMaterial());
        for (String name : nameMap.keySet()) {
            Shape3D part = nameMap.get(name);
            part.setAppearance(planeAppearance);
        }
    }
    
    private void addImageBackground() {
        TextureLoader t = new TextureLoader(System.getProperty("user.dir") + "\\misc\\lab5\\road2.jpg", canvas);
        Background background = new Background(t.getImage());
        background.setImageScaleMode(Background.SCALE_FIT_ALL);
        BoundingSphere bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 2000.0);
        background.setApplicationBounds(bounds);
        root.addChild(background);
    }
    
    private void addLightToUniverse() {
        Bounds bounds = new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 2000.0);
        Color3f color = new Color3f(100/255f, 0/255f, 0/255f);
        Vector3f lightdirection = new Vector3f(-1f, -1f, -1f);
        DirectionalLight dirlight = new DirectionalLight(color, lightdirection);
        dirlight.setInfluencingBounds(bounds);
        root.addChild(dirlight);
    }
    
    private void addOtherLight() {
        Color3f directionalLightColor = new Color3f(Color.BLACK);
        Color3f ambientLightColor = new Color3f(Color.WHITE);
        Vector3f lightDirection = new Vector3f(-1F, -1F, -1F);

        AmbientLight ambientLight = new AmbientLight(ambientLightColor);
        DirectionalLight directionalLight = new DirectionalLight(directionalLightColor, lightDirection);

        Bounds influenceRegion = new BoundingSphere(new Point3d(0.0, 0.0, 0.0), 2000.0);

        ambientLight.setInfluencingBounds(influenceRegion);
        directionalLight.setInfluencingBounds(influenceRegion); 
        root.addChild(ambientLight);
        root.addChild(directionalLight);
    }
    
    private void ChangeViewAngle(){
        ViewingPlatform vp = universe.getViewingPlatform();
        TransformGroup vpGroup = vp.getMultiTransformGroup().getTransformGroup(0);
        Transform3D vpTranslation = new Transform3D();
        Vector3f translationVector = new Vector3f(0.0F, 0F, 8F);
        vpTranslation.setTranslation(translationVector);
        vpGroup.setTransform(vpTranslation);
    }
    
    
    public static void main(String[]args){
        try {
            Lab5 window = new Lab5();
            CarAnimation carMovement = new CarAnimation(wholeCar, transform3D, window);
            window.addKeyListener(carMovement);
            window.setVisible(true);
        }
        catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
