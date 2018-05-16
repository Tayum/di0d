package lab6;

import javax.media.j3d.*;
import com.sun.j3d.utils.picking.*;
import com.sun.j3d.utils.picking.behaviors.*;
import com.sun.j3d.utils.geometry.*;


public class PickingObjects extends PickMouseBehavior {
	public Alpha[] alphas;
	public int moveaxe;
	public int movehead;
	public int moveattack;

	public PickingObjects(Canvas3D pCanvas, BranchGroup root, Bounds pBounds, Alpha[] alphas) {
		super(pCanvas, root, pBounds);
		setSchedulingBounds(pBounds);
		this.alphas = alphas;
		moveaxe = 0;
		movehead = 0;
		moveattack = 0;
	}

	public void updateScene(int xpos, int ypos) {
		Shape3D pickedShape = null;
		pickCanvas.setShapeLocation(xpos, ypos);
		// Selection of the object
		PickResult pResult = pickCanvas.pickClosest();
		if (pResult != null) {
			pickedShape = (Shape3D) pResult.getNode(PickResult.SHAPE3D);
		}
		// if the object was actually picked
		if (pickedShape != null)
		{
			// First move
			if (pickedShape.getUserData() == "lhand" ||
				pickedShape.getUserData() == "rhand" ||
				pickedShape.getUserData() == "legs")
			{
				if (moveaxe == 0) {
					// Take axe if it was not taken yet
					alphas[0].setStartTime(System.currentTimeMillis() - alphas[0].getTriggerTime());
					System.out.println("The object " + pickedShape.getUserData() + " has been selected.");
					moveaxe = 1;
				}
				else if (moveaxe == 1) {
					// Move the hand with the axe back to body
					alphas[1].setStartTime(System.currentTimeMillis() - alphas[1].getTriggerTime());
					System.out.println("The object " + pickedShape.getUserData() + " has been selected.");
					moveaxe = -1;
				}
			}
			// Second move
			else if (pickedShape.getUserData() == "head")
			{
				if (movehead == 0) {
					// Rotate head to the left
					alphas[2].setStartTime(System.currentTimeMillis() - alphas[2].getTriggerTime());
					System.out.println("The object " + pickedShape.getUserData() + " has been selected.");
					movehead = 1;
				}
				else if (movehead == 1) {
					// Rotate head back
					alphas[3].setStartTime(System.currentTimeMillis() - alphas[3].getTriggerTime());
					System.out.println("The object " + pickedShape.getUserData() + " has been selected.");
					movehead = -1;
				}
			}
			// Third move (moveaxe == -1 ensures that the First move has been made and the axe has been taken)
			else if (moveaxe == -1 && pickedShape.getUserData() == "axe")
			{
				if (moveattack == 0) {
					// swing axe
					alphas[4].setStartTime(System.currentTimeMillis() - alphas[4].getTriggerTime());
					System.out.println("The object " + pickedShape.getUserData() + " has been selected.");
					moveattack = 1;
				}
				else if (moveattack == 1) {
					// reverse swing axe
					alphas[5].setStartTime(System.currentTimeMillis() - alphas[5].getTriggerTime());
					System.out.println("The object " + pickedShape.getUserData() + " has been selected.");
					moveattack = -1;
				}
			}
		}
	}
}
