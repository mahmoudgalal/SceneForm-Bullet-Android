////////////////////////////////////////////////
// Created by Mahmoud Galal on 25/11/2018.
//      mahmoudgalal57@yahoo.com
////////////////////////////////////////////////
package com.mahmoudgalal.sceneformbulletphysics;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;
import com.google.ar.core.exceptions.CameraNotAvailableException;
import com.google.ar.sceneform.Camera;
import com.google.ar.sceneform.FrameTime;
import com.google.ar.sceneform.HitTestResult;
import com.google.ar.sceneform.Node;
import com.google.ar.sceneform.Scene;
import com.google.ar.sceneform.SceneView;
import com.google.ar.sceneform.math.Vector3;
import com.google.ar.sceneform.rendering.Color;
import com.google.ar.sceneform.rendering.Material;
import com.google.ar.sceneform.rendering.MaterialFactory;
import com.google.ar.sceneform.rendering.Renderable;
import com.google.ar.sceneform.rendering.ShapeFactory;
import java.util.Random;
import java.util.concurrent.CompletableFuture;
import static android.view.MotionEvent.ACTION_CANCEL;
import static android.view.MotionEvent.ACTION_DOWN;
import static android.view.MotionEvent.ACTION_MOVE;
import static android.view.MotionEvent.ACTION_OUTSIDE;
import static android.view.MotionEvent.ACTION_UP;
import static com.mahmoudgalal.sceneformbulletphysics.Utils.*;


public class MainActivity extends AppCompatActivity implements Scene.OnUpdateListener,
        View.OnClickListener,Scene.OnPeekTouchListener {

    private SceneView sceneView ;
    private Material boxMaterialRed,groundMaterialBlue,
            cylinderMaterialYellow,sphereMaterialGray;
    private PhysicsManager physicsManager;
    /// Scene Camera
    private Camera mainCamera;
    private TextView numberOfBodiesText;
    private ImageView fireBtn;
    private Node pickedNode ;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (!checkIsSupportedDeviceOrFinish(this)) {
            return;
        }
        physicsManager = new PhysicsManager();
        //initialize physics world
        physicsManager.init();
        setContentView(R.layout.activity_main);

        numberOfBodiesText =  findViewById(R.id.sample_text);
        numberOfBodiesText.setText("Bodies: 0");
        fireBtn = findViewById(R.id.fire_btn);

        sceneView = findViewById(R.id.scene_view);
        sceneView.setBackgroundColor(android.graphics.Color.GREEN);
        fireBtn.setOnClickListener(this);

        mainCamera = sceneView.getScene().getCamera();
        mainCamera.setFarClipPlane(400);
        mainCamera.setWorldPosition(new Vector3(7f,1.5f,24f));
        sceneView.getScene().addOnUpdateListener(this);
        sceneView.getScene().addOnPeekTouchListener(this);

        createDummyObjects();
    }

   private void createGround(){
       if(groundMaterialBlue != null ){
           Vector3 size = new Vector3(1000,1,1000);
           Renderable ground = ShapeFactory.makeCube(size,Vector3.zero(),groundMaterialBlue);
           PhysicsNode node = physicsManager.createGroundPhysicsNode(ground,sceneView.getScene(),
                       size,new Vector3(0,-22,10));
       }
   }
    /**
     * Creates a group of freely falling objects
     */
    private void createDummyObjects(){

        CompletableFuture<Material> boxMaterial =  MaterialFactory.makeOpaqueWithColor(this,
                 new Color(android.graphics.Color.RED));
        CompletableFuture<Material> groundMaterial =  MaterialFactory.makeOpaqueWithColor(this,
                new Color(android.graphics.Color.BLUE));
        CompletableFuture<Material> cylinderMaterial =  MaterialFactory.makeOpaqueWithColor(this,
                new Color(android.graphics.Color.YELLOW));
        CompletableFuture<Material> sphereMaterial =  MaterialFactory.makeOpaqueWithColor(this,
                new Color(android.graphics.Color.DKGRAY));
        CompletableFuture.allOf(boxMaterial,groundMaterial,cylinderMaterial,sphereMaterial).thenAccept(
                (v) -> {
                    if(boxMaterial.isDone() && groundMaterial.isDone() &&
                            cylinderMaterial.isDone() && sphereMaterial.isDone()){
                        try {
                                groundMaterialBlue = groundMaterial.get();
                                boxMaterialRed = boxMaterial.get();
                                cylinderMaterialYellow = cylinderMaterial.get();
                                sphereMaterialGray = sphereMaterial.get();

                                createGround();
                                createFreePhysicsBoxes(10);
                                createFreePhysicsSpheres(3.f,5);
                                createFreePhysicsCylinders(3.f,8,5);

                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    }
        });
    }

    /**
     * Throws a box from the camera eye
     */
    private void createPhysicsBoxFromEye(){
       Vector3 lookat = mainCamera.getForward();
       Vector3 camPos = mainCamera.getWorldPosition();
       Vector3 size = new Vector3(6,6,6);

       Renderable box = ShapeFactory.makeCube(size,
                Vector3.zero(), boxMaterialRed);
        PhysicsNode node = physicsManager.createBoxPhysicsNodeFromEye(box,sceneView.getScene(),
                size,camPos,lookat,490.f,10);
    }

    /**
     * Throws a Sphere from the camera eye
     * @param radius sphere radius
     */
    private void createPhysicsSphereFromEye(float radius){
        Vector3 lookat = mainCamera.getForward();
        Vector3 camPos = mainCamera.getWorldPosition();

        Renderable sphere = ShapeFactory.makeSphere(radius,
                Vector3.zero(), sphereMaterialGray);
        PhysicsNode node = physicsManager.createSpherePhysicsNodeFromEye(sphere,sceneView.getScene(),
                radius,camPos,lookat,490.f,6);
    }

    /**
     * Throws a Cylinder from the camera eye
     * @param radius
     * @param height
     */
    private void createPhysicsCylinderFromEye(float radius,float height){
        Vector3 lookat = mainCamera.getForward();
        Vector3 camPos = mainCamera.getWorldPosition();

        Renderable cylinder = ShapeFactory.makeCylinder(radius,height,
                Vector3.zero(), cylinderMaterialYellow);
        PhysicsNode node = physicsManager.createCylinderPhysicsNodeFromEye(cylinder,sceneView.getScene(),
                radius,height,camPos,lookat,410.f,6.f);
    }

    void createFreePhysicsBoxes(int count ){
        Random random = new Random();
        if(boxMaterialRed != null ){
            Vector3 size = new Vector3(6,6,6);
            Renderable boxRenderable =
                        ShapeFactory.makeCube(size,
                                Vector3.zero(), boxMaterialRed);
            for (int i = 0;i<count;i++){
                int randomOffset = random.nextInt(6);
                PhysicsNode node = physicsManager.createBoxPhysicsNode(boxRenderable,
                        sceneView.getScene(),size,
                        new Vector3(randomOffset,35+randomOffset,
                                -32+randomOffset),10);
            }
        }
    }

    void createFreePhysicsSpheres(float radius,int count){
        Random random = new Random();
        if(boxMaterialRed != null ){
            Renderable sphere = ShapeFactory.makeSphere(radius,
                    Vector3.zero(), sphereMaterialGray);
            for (int i = 0;i<count;i++){
                int randomOffset = random.nextInt(2* (int)radius);
                PhysicsNode node = physicsManager.createSpherePhysicsNode(sphere,sceneView.getScene(),radius,
                        new Vector3(randomOffset,37+randomOffset,
                                -34+randomOffset),6);
            }
        }
    }

    void createFreePhysicsCylinders(float radius,float height ,int count){
        Random random = new Random();
        if(cylinderMaterialYellow != null ){
            Renderable cylinder = ShapeFactory.makeCylinder(radius,height,
                    Vector3.zero(), cylinderMaterialYellow);
            for (int i = 0;i<count;i++){
                int randomOffset = random.nextInt(2* (int)radius);
                PhysicsNode node = physicsManager.createCylinderPhysicsNode(cylinder,sceneView.getScene(),
                        radius,height,new Vector3(randomOffset,39+randomOffset,
                                -33+randomOffset),6);
            }
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        sceneView.pause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        try {
            sceneView.resume();
        } catch (CameraNotAvailableException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        //remove physics world
        physicsManager.destroy();
    }

    @Override
    public void onUpdate(FrameTime frameTime) {
        physicsManager.updatePhysicsObjects();
        physicsManager.stepPhysicsWorld(frameTime.getDeltaSeconds());
        if(((int) (1000*frameTime.getStartSeconds())) % 30 == 0){
            long numberOfPhysicsBodies = physicsManager.getNumberOfPhysicsBodies();
            numberOfBodiesText.setText("Bodies: "+ (numberOfPhysicsBodies>0?numberOfPhysicsBodies:0));
        }
    }

      @Override
    public void onClick(View view) {
        int rand = new Random().nextInt(3);
        if(rand == 0)
           createPhysicsBoxFromEye();
        else if (rand == 1)
            createPhysicsSphereFromEye(3.0f);
        else
            createPhysicsCylinderFromEye(3.f,8.f);
    }

    @Override
    public void onPeekTouch(HitTestResult hitTestResult, MotionEvent motionEvent) {
        Node node = hitTestResult.getNode();
        switch (motionEvent.getAction()){
            case ACTION_DOWN:
            case ACTION_MOVE:
                break;
            case ACTION_CANCEL:
            case ACTION_OUTSIDE:
            case ACTION_UP:
                pickedNode = null;
                return;
        }
        if( node instanceof PhysicsNode && pickedNode == null){
            PhysicsNode node1 = (PhysicsNode) node;
            if(!node1.isStatic()) {
                //apply an up-ward force
                Vector3 relPos = new Vector3(1,3.7f,2f);
                Vector3 force = new Vector3(0,3000,-3.1f);
                physicsManager.applyForce(node1,force,relPos);
                pickedNode = node1;
            }
        }
    }
}