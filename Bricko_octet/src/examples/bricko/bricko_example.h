////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
namespace octet {
  /// Scene containing a box with octet.
  class bricko_example : public app {
    // scene for drawing box
    ref<visual_scene> app_scene;
  public:
    /// this is called when we construct the class before everything is initialised.
	  bricko_example(int argc, char **argv) : app(argc, argv) {
    }

    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene =  new visual_scene();
      app_scene->create_default_camera_and_lights();

	  vec3 halfextent = vec3(2.0f, 2.0f, 2.0f);

      material *red = new material(vec4(1, 0, 0, 1));
	  mesh_box *box = new mesh_box(halfextent);
      scene_node *node = new scene_node();
      app_scene->add_child(node);
      //app_scene->add_mesh_instance(new mesh_instance(node, box, red));
	  	  
	  node->rotate(45, vec3(0,0,1));
	  node->translate(vec3(0, 4, 0));
	  mat4t modelPos = node->access_nodeToParent();
	  vec3 mp = modelPos.get_principal_axis();

	  brBodyDef bodydef;
	  bodydef.initialPosition = vec3(0, 4, 0);//modelPos.get_translation();
	  bodydef.initialAxis = vec3(0, 0, 1);
	  bodydef.initialAngle = 45 * (3.14159265f / 180); //bricko uses radiant
	  bodydef.bodyType = Dynamic;
	  bodydef.intialAngularVelocity = vec3(2.0f, 2.0f, 2.0f);
	  bodydef.intialLinearVelocity = vec3(0.0f, 0.0f, 3.0f);

	  brTransform t;
	  identity(t);
	  brBoxDef boxdef;
	  
	  //vec3 is halfextent
	  boxdef.Set(t, halfextent);

	  app_scene->add_bricko_shape(modelPos, box, red, bodydef, boxdef);
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

      // update matrices. assume 30 fps.
	  float dt = 1.0f / 30;
	  float acc = 1.0f;
	  //while (acc >= dt)
	  {
		  app_scene->update_physics(dt);
		  acc -= dt;
	  }
		  
      app_scene->update(1.0f/30);

      // draw the scene
      app_scene->render((float)vx / vy);

      // tumble the box  (there is only one mesh instance)
      //scene_node *node = app_scene->get_mesh_instance(0)->get_node();
      //node->rotate(1, vec3(1, 0, 0));
      //node->rotate(1, vec3(0, 1, 0));
    }
  };
}
