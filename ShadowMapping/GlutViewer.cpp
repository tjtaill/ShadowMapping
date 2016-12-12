#include "StdAfx.h"
#include "GlutViewer.h"
#include <gl/glew.h>
#include <iostream>
#include "Math3D.h"
#include "GLError.h"
#include <boost/foreach.hpp>
#include <list>

using namespace boost;

using namespace std;

float light_rotation = 0.0f;
float light_rotation_step = 2.0f;

float const scene_radius = 30.0f;

float offset_bias = 4.0f;
float offset_bias_step = 1.00f;
bool show_shadow_map = false;
bool pcf_on = false;
int shadowHeight, shadowWidth;


float epsilon = 0.1f;
float epsilon_step = 0.1f;

float shadow_ratio = 0.75f;
float shadow_ratio_step = 0.05f;

float light_height = 10.0f;
float light_distance = 40.0f;
float light_step = 1.0f;

bool regenerate_shadow = true;

const GLfloat global_ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
const float initial_light_pos[3] = { 0.0f, light_height, light_distance };

list<Program* const> programs;
Program* current_program;

void GlutViewer::draw(){

	glPushMatrix();
		GLfloat wlpos[4] = { 0.0f, 0.0f, 0.0f, 1.0f};
		GLfloat wlnpos[4];
		translate( initial_light_pos[0], 
			light_height,
			light_distance, wlpos, wlnpos);
		rotate_y( light_rotation, wlnpos, wlpos);
		whiteLight.position_is( wlpos );
		light_view->look_from( wlpos );
		glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;
		glEnable ( GL_COLOR_MATERIAL ) ;
		glColor3ub( 255, 255, 255 );
		whiteLight.draw();
		glDisable ( GL_COLOR_MATERIAL ) ;
	glPopMatrix();

	glPushMatrix();
		glTranslated( 0.0, 0.0, 12.5);
		silverMaterial.on();
		ball.draw();
		silverMaterial.off();
	glPopMatrix();


	glPushMatrix();
		glTranslated( 0.0, 2.5, -12.5 );
		glRotated( light_rotation, 0.0, 1.0, 0.0 );
		rubyMaterial.on();
		torus.draw();
		rubyMaterial.off();
	glPopMatrix();

	
	glPushMatrix();
		glTranslated( 0.0, -7.5, 0.0 );
		glRotated(90.0, 1.0, 0.0, 0.0 );
		greenMaterial.on();
		floor.draw();
		greenMaterial.off();
	glPopMatrix();
	
	
	glPushMatrix();
		glRotated( -light_rotation, 0.0, 1.0, 0.0 );
		blueMaterial.on();
		glutSolidTeapot(5.0);
		blueMaterial.off();
	glPopMatrix();
	
	
	


	
}

void compile_and_link( Program& program, Shader& vshader, Shader& fshader)
{
	if ( vshader.didNotCompileOk() ) cout << vshader.compilerErrors() << endl;
	program.addShader( vshader.shader() );
	if ( fshader.didNotCompileOk()) cout << fshader.compilerErrors() << endl;
	program.addShader( fshader.shader() );
	program.link();
	if ( program.didNotLinkOk() ) cout << program.linkerErrors() << endl;
}

void set_parameters( Program* const program )
{
	program->start();
	glUniform1i( program->rloc("LightNumber"), 0);
	glUniform1i( program->rloc("TextureUnit"), 0);
	glUniform1i( program->rloc("ShadowMap"), 0);
	glUniform1f( program->rloc("Epsilon"), epsilon);
	glUniform1f( program->rloc("ShadowRatio"), shadow_ratio);
	program->end();
}


GlutViewer::GlutViewer(int argc, 
					   char** argv,
					   double scene_size) :
GlutApplication(argc, argv, "Glut Viewer"),
floor( scene_radius, scene_radius, 2.0 ),
blueMaterial(0.0, 0.1, 0.06, 0.0, 0.50980392, 0.50980392, 0.50196078, 0.50196078, 0.50196078, .25),
whiteLight( ZERO, 1.0f, 1.0f, 1.0f, 1.0f ),
shadow_map( FIRST ),
ssm_vert(".\\shaders\\ssm.vert", VERTEX),
ssm_frag(".\\shaders\\ssm.frag", FRAGMENT),
pcfsm_frag(".\\shaders\\pcfsm.frag", FRAGMENT),
gaussm_frag(".\\shaders\\gaussm.frag", FRAGMENT),
ditsm_frag(".\\shaders\\ditsm.frag", FRAGMENT),
ball( 5.0, 16, 8 ),
torus( 2.5, 5.0, 16, 16),
rubyMaterial(0.1745, 0.01175, 0.01175, 0.61424, 0.04136, 0.04136, 0.727811, 0.626959, 0.626959, 0.6),
silverMaterial(0.19225, 0.19225, 0.19225, 0.50754, 0.50754, 0.50754, 0.508273, 0.508273, 0.508273, 0.4),
chromeMaterial(0.25, 0.25, 0.25, 0.4, 0.4, 0.4, 0.774597, 0.774597, 0.774597, 0.6 ),
whiteMaterial(0.05, 0.05, 0.05, 0.5, 0.5, 0.5, 0.7, 0.7, 0.7, .078125),
redMaterial(0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.7, 0.6, 0.6, .25),
greenMaterial(0.0, 0.0, 0.0, 0.1, 0.35, 0.1, 0.45, 0.55, 0.45, .25)
{

	glutApplicationPointer = this;
	
	whiteLight.on();	

	// load, compile link the shaders
	compile_and_link( ssm_program, ssm_vert, ssm_frag );
	compile_and_link( pcfsm_program, ssm_vert, pcfsm_frag );
	compile_and_link( gaussm_program, ssm_vert, gaussm_frag );
	compile_and_link( ditsm_program, ssm_vert, ditsm_frag );

	programs.push_back( &ssm_program );
	programs.push_back( &pcfsm_program );
	programs.push_back ( &gaussm_program );
	programs.push_back( &ditsm_program );

	BOOST_FOREACH( Program* const program, programs )
	{
		set_parameters( program );
	}

	current_program = &ssm_program;

	shadow_map.on();
	
	
	timeVarying = false;

	// initilize the view paramaters
	phi=0.0;
	theta=0.0;
	sdepth = scene_size / 2.0;
	zNear=1.0;
	zFar= scene_size;
	downY = 0;
	downX = 0;
	aspect = (double) windowWidth_ / (double) windowHeight_;
	leftButton = false;
	middleButton = false;

	// initialize light frustum
	shadowWidth = windowWidth_;
	shadowHeight = windowHeight_;
	light_view = new Frustum( shadowWidth, shadowHeight, 
		initial_light_pos, scene_radius );

	OnInit();
}





GlutViewer::~GlutViewer(void)
{
	delete light_view;
}

void GlutViewer::OnInit(void)
{	
	glClearDepth (1.0);
	glEnable (GL_DEPTH_TEST) ;
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, global_ambient);

}

void GlutViewer::OnReshapeWindow(int newWidth, int newHeight)
{
	windowHeight_ = newHeight;
	windowWidth_ = newWidth;
	shadowWidth = windowWidth_;
	shadowHeight = windowHeight_;
	light_view->view_size_is( windowWidth_, windowHeight_ );
	regenerate_shadow = true;
	aspect =  (double)windowWidth_ / (double)windowHeight_;
	glViewport( 0, 0, windowWidth_, windowHeight_ );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(64.0, 1.0, zNear, zFar);
	glutPostRedisplay();
}


void GlutViewer::update(void){
	
	if ( !timeVarying ) return;
	
	light_rotation = light_rotation >= 360.0f ? 0.0f : light_rotation + light_rotation_step;
	regenerate_shadow = true;
	
	
}

void display_shadow_map()
{
        // Display shadow map for educational purposes
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMatrixMode(GL_TEXTURE);
        glPushMatrix();
        glLoadIdentity();
        glEnable(GL_TEXTURE_2D);
        glDisable(GL_LIGHTING);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        // Show the shadowMap at its actual size relative to window
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(-1.0f, -1.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(1.0f, 
                       -1.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(1.0f, 1.0f);
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(-1.0f, 1.0f);
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        gluPerspective(45.0f, 1.0f, 1.0f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
}

void GlutViewer::OnDisplay(void)
{
	glPolygonOffset( offset_bias, 0.0f );
	
	
	// first render pass build shadow map
	if ( regenerate_shadow ) {
		light_view->change();
		shadow_map.pre_render( light_view );
		draw( );
		shadow_map.post_render( light_view );
		light_view->restore();
		regenerate_shadow = false;
	}

	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if ( show_shadow_map )
	{
		current_program->end();
		display_shadow_map();
	}
	else
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glPushMatrix();
			glTranslated(0.0, 0.0, -sdepth);
			glRotated(-theta, 1.0, 0.0, 0.0);
			glRotated(phi, 0.0, 0.0, 1.0);
			shadow_map.pre_draw_scene();
			draw();
			shadow_map.post_draw_scene();
		glPopMatrix();
	}

	glutSwapBuffers();
}

void update_shader(Program* const program)
{
	program->start();
	glUniform1f( program->uloc("Epsilon"), epsilon );
	glUniform1f( program->uloc("ShadowRatio"), shadow_ratio );
}
	
void GlutViewer::OnSpecialKeyPressed(int keyPressed, int x, int y){
	regenerate_shadow = true;
	switch( keyPressed ){
		case GLUT_KEY_F1 :
			timeVarying = timeVarying ? false : true;
			break;
		case GLUT_KEY_F2 :
			offset_bias += offset_bias_step;
			break;
		case GLUT_KEY_F3 :
			offset_bias -= offset_bias_step;
			break;
		case GLUT_KEY_F4 :
			show_shadow_map = show_shadow_map ? false : true;
			break;
		case GLUT_KEY_F5 :
			if ( pcf_on )
				shadow_map.pcf_on();
			else
				shadow_map.pcf_off();
			pcf_on = pcf_on ? false : true;
			break;
		case GLUT_KEY_F6 :
			if ( shadow_map.is_culling_on() )
				shadow_map.cull_none();
			else
				shadow_map.cull_front();
			break;
		case GLUT_KEY_F7 :
			if ( ssm_program.active() )
				ssm_program.end();
			else
			{
				current_program->end();
				current_program = &ssm_program;
				update_shader( current_program );
			}
			break;
		case GLUT_KEY_F8 :
			if ( pcfsm_program.active() )
				pcfsm_program.end();
			else
			{
				current_program->end();
				current_program = &pcfsm_program;
				update_shader( current_program );
			}
			break;
		case GLUT_KEY_F9:
			if ( gaussm_program.active() )
				gaussm_program.end();
			else
			{
				current_program->end();
				current_program = &gaussm_program;
				update_shader( current_program );
			}
			break;
		case GLUT_KEY_F10:
			epsilon += epsilon_step;
			update_shader( current_program );
			break;
		case GLUT_KEY_F11:
			epsilon -= epsilon_step;
			update_shader( current_program );
			break;
		case GLUT_KEY_HOME:
			
			if ( ditsm_program.active() )
				ditsm_program.end();
			else
			{
				current_program->end();
				current_program = &ditsm_program;
				update_shader( current_program );
			}	
			break;
		case GLUT_KEY_END:
			shadow_ratio += shadow_ratio_step;
			update_shader( current_program );
			break;
		case GLUT_KEY_INSERT:
			shadow_ratio -= shadow_ratio_step;
			update_shader( current_program );
			break;
		case GLUT_KEY_UP:
			light_distance -= light_step;
			break;
		case GLUT_KEY_DOWN:
			light_distance += light_step;
			break;
		case GLUT_KEY_PAGE_UP:
			light_height += light_step;
			break;
		case GLUT_KEY_PAGE_DOWN:
			light_height -= light_step;
			break;
		case GLUT_KEY_LEFT:
			shadowHeight /= 2;
			shadowWidth /= 2;
			light_view->view_size_is( shadowWidth, shadowHeight );
			break;
		case GLUT_KEY_RIGHT:
			shadowHeight *= 2;
			shadowWidth *= 2;
			light_view->view_size_is( shadowWidth, shadowHeight );
			break;
		default:
			break;
	}
	glutPostRedisplay();

}

void GlutViewer::OnNormalKeyPressed(unsigned char keyPressed, int x, int y)
{
	
	

}

void GlutViewer::OnMousePressed(int button, int state, int x, int y)
{
	
	downX = x; downY = y;

	leftButton = ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN));

	middleButton = ((button == GLUT_MIDDLE_BUTTON) &&  (state == GLUT_DOWN));

	glutPostRedisplay();
}

void GlutViewer::OnMouseDrag(int x, int y)
{
	
	if (leftButton)
	{
		
		phi += (double)(x-downX)/4.0;
		theta += (double)(downY-y)/4.0;
		
		
	} // rotate

	if (middleButton)
	{
		float delta = (double)(downY - y) / 10.0;
		sdepth += delta;
		zFar += delta;
		zNear += delta;
		gluPerspective(64.0, 1.0, zNear, zFar);
	} // scale

	downX = x;   downY = y; 

	glutPostRedisplay();
}
