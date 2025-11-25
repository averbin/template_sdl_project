#include<iostream>

#include<GL/gl.h>
#include<SDL3/SDL.h>

//Starts up SDL, creates window, and Initializes OpenGL
bool Init();

//Initializes matrices and clear color
bool InitGL();

//Input Handler
void HandleKeys(const unsigned char key, const int x, const int y);

//Per frame Update
void Update();

//Renders quad to the screen
void Render();

//Frees media and shuts down SDL
void Close();

//The window we'll be Rendering to
SDL_Window* window = nullptr;

//OpenGL context
SDL_GLContext glContext;

//Render flag
bool gRenderQuad = true;

int main()
{
	std::cout << "_-_-_: Start program\n";
	if(!Init())
		return -1;
	if(!InitGL())
		return -1;

	bool running = true;
	SDL_Event event;

	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_EVENT_QUIT) 
				running = false;
			if(event.type == SDL_EVENT_KEY_DOWN 
				&& event.key.key == SDLK_ESCAPE)
				running = false;
		}

		Render();		
		
	}
	return 0;
}

bool Init()
{
	bool success = true;
	
	if(SDL_Init( SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not Inititalize! SDL Error: " 
			<< SDL_GetError() << "\n";
		success = false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		window = SDL_CreateWindow(
			"SDL OpenGL",
			1024, 768,
			SDL_WINDOW_OPENGL);
		
		if(!window)
		{
			std::cerr << "Window could not be created! SDL Error: "
				<< SDL_GetError() << "\n";
			success = false;	
		}
		else
		{
			glContext = SDL_GL_CreateContext(window);
			
			if(glContext == nullptr)
			{
				std::cerr << "OpenGL context could not be created! SDL Error: "
					<< SDL_GetError() << "\n";
				success = false;
			}
			else
			{
				if(SDL_GL_SetSwapInterval(1) < 0)
				{
					std::cerr << "Warrning: Unable to set VSync! SDL Error: "
						<< SDL_GetError() << "\n";
				}

				if(!InitGL())
				{
					std::cerr << "Unable to Initialize OpenGL!\n";
					success = false;
				}
			}
		}
	}

	return success;
}

bool InitGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		std::cerr << "Error Initializing OpenGL" << "\n";
		success = false;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	error = glGetError();
	if(error != GL_NO_ERROR)
	{
		std::cerr << "Error Initializing OpenGL!\n";
		success = false;
	}

	//Initialize clear color
	glClearColor( 0.5f, 0.1f, 0.7f, 1.f);

	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		std::cerr << "Error Initializing OpenGL!\n";
		success = false;
	}
	return success;
}

void HandleKeys(const unsigned char key, const int x, const int y)
{

}

void Update()
{

}

void Render()
{
	glClearColor(0.5, 0.1f, 0.7f, 0.f);
	glClear( GL_COLOR_BUFFER_BIT );
	
	glBegin(GL_QUADS);
		glColor3f(0.f, 1.f, 0.25f); glVertex2f(-0.5f, -0.5f);
        glColor3f(0.71f, 0.2f, 0.f); glVertex2f(0.5f, -0.5f);
        glColor3f(0.5f, 0.5f, 0.5f); glVertex2f(0.5f, 0.5f);
        glColor3f(1.f, 1.f, 0.3f); glVertex2f(-0.5f, 0.5f);
    glEnd();

	SDL_GL_SwapWindow(window);
}

void Close()
{
	SDL_GL_DestroyContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
