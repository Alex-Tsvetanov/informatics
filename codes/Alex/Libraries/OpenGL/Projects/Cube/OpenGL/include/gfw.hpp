#pragma once
#include <fstream>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include <cassert>
#include <cstddef>

#include <GL/gl.h>
#include <SDL.h>

#include "gfw/math.hpp"

namespace gfw{

GFW__CHECK(GLfloat);
GFW__CHECK(GLdouble);
GFW__CHECK(GLbyte);
GFW__CHECK(GLubyte);
GFW__CHECK(GLshort);
GFW__CHECK(GLushort);
GFW__CHECK(GLint);
GFW__CHECK(GLuint);

struct GLContext;
struct Screen;
struct Window{
	SDL_Window *sdl_window;
	GLContext *gl;

	Screen *screen;

	Window(SDL_Window *native);
	~Window();

	static void _dispatch_window(const SDL_Event &ev);
	void _event_window(const SDL_Event &ev);
	Screen *attach(Screen *s);
	void _render();
};
struct GLCacheEntry{
	virtual ~GLCacheEntry();
};

class Screen{
	friend class Window;

	Screen *_gl_next=nullptr, *_gl_prev=nullptr;
	public:
		GLContext *gl=nullptr;

		virtual ~Screen();

		void gl_attach(GLContext *ctx);
		void gl_detach();

	protected:
		virtual void gl_init();
		virtual void gl_deinit();
		virtual void render(uint width, uint height)=0;
};

class GLContext{
	friend class Window;
	friend class Screen;

	std::unordered_map<std::type_index, GLCacheEntry*> cache_entries;
	GLCacheEntry *&cache_get(const std::type_info &key);
	GLCacheEntry *cache_pop(const std::type_info &key);
	SDL_GLContext sdl_glctx;
	Screen *screen=nullptr;
	public:
		template<class T>
		T *cache_get(){
			return static_cast<T*>(cache_get(typeid(T)));
		}
		template<class T>
		void cache_set(T *next){
			GLCacheEntry *&e=cache_get(typeid(T));
			if(e) delete e;
			e=next;
			return;
		}
		template<class T>
		void cache_remove(T *next){
			GLCacheEntry *e=cache_pop(typeid(T));
			if(e) delete e;
			return;
		}
		template<class T>
		T *cache_swap(T *next){
			GLCacheEntry *&e=cache_get(typeid(T)), *old=e;
			if(e) delete e;
			e=next;
			return static_cast<T*>(old);
		}
		template<class T>
		T *cache_remove(T *next){
			GLCacheEntry *&e=cache_get(typeid(T)), *old=e;
			if(e) delete e;
			e=next;
			return static_cast<T*>(old);
		}
		template<class T>
		T *cache(){
			GLCacheEntry *&e=cache_get(typeid(T));
			if(!e) e=new T;
			return static_cast<T*>(e);
		}

		GLContext(SDL_GLContext native);
		~GLContext();

		#define X(f,t) t f;
		#include "gfw/gl.x"
};

GLuint make_shader(GLContext *gl, GLenum tp, const char *name);

GLuint make_program(GLContext *gl, std::vector<GLuint> shaders, bool destroy=true);

}
