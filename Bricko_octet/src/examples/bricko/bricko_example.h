////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
#include <ctime>
#include <chrono>

namespace octet {
  /// Scene containing a box with octet.
  class bricko_example : public app {
    // scene for drawing box
    ref<visual_scene> app_scene;
	mouse_look ml;
	ref<camera_instance> camera;

	double fps = 100.0f;
	double fixed_delta_time;
	double accumulator = 0.0f;
	double accumulator_max = 0.2f;

	std::clock_t startTime;

  public:
    /// this is called when we construct the class before everything is initialised.
	  bricko_example(int argc, char **argv) : app(argc, argv) {
    }

	  void update_mouse()
	  {
		  //if (is_key_down(key::key_shift))
		  {
			  scene_node *camera_node = camera->get_node();
			  mat4t &camera_to_world = camera_node->access_nodeToParent();
			  ml.update(camera_to_world);
		  }
	}

	  void keyboard(){
		  if (is_key_down(key::key_esc))
		  {
			  exit(0);
		  }
		  if (is_key_down('W')){
			  camera->get_node()->translate(vec3(0, 5, 0));
		  }
		  else if (is_key_down('S')){
			  camera->get_node()->translate(vec3(0, -5, 0));
		  }
		  else if (is_key_down('A')){
			  camera->get_node()->translate(vec3(-5, 0, 0));
		  }
		  else if (is_key_down('D')){
			  camera->get_node()->translate(vec3(5, 0, 0));
		  }
		  else if (is_key_down('Q')){
			  camera->get_node()->translate(vec3(0, 0, 5));
		  }
		  else if (is_key_down('E')){
			  camera->get_node()->translate(vec3(0, 0, -5));
		  }
	  }

    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene =  new visual_scene();
      app_scene->create_default_camera_and_lights();
	  
	  //app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 4, 0));

	  ml.init(this, 200.0f / 360.0f, false);

	  camera = app_scene->get_camera_instance(0);
	  camera->get_node()->translate(vec3(0, 0, 40));
	  camera->set_far_plane(1000);

	  vec3 halfextent = vec3(2.0f);

      material *red = new material(vec4(1, 0, 0, 1));
	  material *green = new material(vec4(0, 1, 0, 1));
	  material *blue = new material(vec4(0, 0, 1, 1));
	  mesh_box *box = new mesh_box(halfextent);
      
	  vec3 iniPos = vec3(0.0f, 10.0f, 0.0f);
	  vec3 iniPos2 = vec3(20.0f, 4.0f, 0.0f);

	  brBodyDef bodydef;
	  bodydef.initialPosition = iniPos; //modelPos.get_translation();
	  bodydef.initialAxis = vec3(0, 1, 0).normalize();
	  bodydef.initialAngle = 0.0f;//45 * (3.14159265f / 180); //bricko uses radiant
	  bodydef.bodyType = Dynamic;
	  bodydef.intialAngularVelocity = vec3(0.7f);//, 2.0f, 2.0f);//vec3(2.0f, 2.0f, 2.0f);
	  bodydef.intialLinearVelocity = vec3(0.0f, 0.0f, 0.0f);//vec3(0.0f, 0.0f, 3.0f);
	  //identity(bodydef.intialLinearVelocity);

	  brTransform t;
	  identity(t);
	  brBoxDef boxdef;
	  //vec3 is halfextent
	  boxdef.Set(t, halfextent);
	  boxdef.density = 1.2f;

	  mat4t mat;
	  mat.translate(iniPos);

	  //adding a static object
	  brBodyDef groundDef;
	  vec3 groundPos(0.0f, -10.0f, 0.0f);
	  vec3 groundHalfExtent(vec3(2.0f));
	  groundDef.bodyType = Static;
	  groundDef.initialAxis = vec3(0, 1, 0).normalize();
	  groundDef.initialPosition = groundPos;

	  brTransform t_ground;
	  identity(t_ground);

	  brBoxDef groundboxdef;	  
	  groundboxdef.Set(t_ground, groundHalfExtent);

	  mat4t mat_ground;
	  mat_ground.loadIdentity();
	  mat_ground.translate(groundPos);

	  mesh_box *ground_box = new mesh_box();
	  
	  app_scene->add_bricko_shape(mat_ground, ground_box, blue, groundDef, groundboxdef);
	  //app_scene->add_bricko_shape(mat, box, red, bodydef, boxdef);
	  

	  fixed_delta_time = 1.0f / fps;
	  startTime = std::clock();
    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {

      keyboard();
      update_mouse();

      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy, vec4(0.0f,0.0f,0.0f, 1.0f));
	  
	  std::clock_t curr_time = std::clock();

	  accumulator += (double)(curr_time - startTime) / CLOCKS_PER_SEC;
	  startTime = curr_time;

	  if (accumulator > accumulator_max)
		  accumulator = accumulator_max;

	  while (accumulator>fixed_delta_time)
	  {
		  app_scene->update_physics((float)fixed_delta_time);
		  accumulator -= fixed_delta_time;
	  }

	  
	  app_scene->update(1.0f / 30);  
	  
	  // draw the scene
      app_scene->render((float)vx / vy);

    }
  };
}
