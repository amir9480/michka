#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Michka.h"
using namespace Michka;

template<typename T>
std::ostream& operator << (std::ostream& _ostream, Vector<T> _array)
{
    for (auto element: _array)
    {
        _ostream << element << ",";
    }
    _ostream << "\n";
    return _ostream;
}

template<typename T>
std::ostream& operator << (std::ostream& _ostream, List<T> _array)
{
    for (auto element: _array)
    {
        _ostream << element << ",";
    }
    _ostream << "\n";
    return _ostream;
}

struct Vertex
{
	f32 px, py, pz;
	f32 nx, ny, nz;
	f32 tx, ty, tz;
	f32 u, v;


	Vertex(f32 _px, f32 _py, f32 _pz,
		f32 _u, f32 _v,
		f32 _nx = 0.0f, f32 _ny = 0.0f, f32 _nz = 0.0f) :
		px(_px), py(_py), pz(_pz),
		nx(_nx), ny(_ny), nz(_nz),
		u(_u), v(_v),
		tx(0), ty(0), tz(0)
	{}

	Vertex(f32 _px, f32 _py, f32 _pz,
		f32 _u, f32 _v,
		f32 _nx, f32 _ny, f32 _nz,
		f32 _tx, f32 _ty, f32 _tz) :
		px(_px), py(_py), pz(_pz),
		nx(_nx), ny(_ny), nz(_nz),
		u(_u), v(_v),
		tx(_tx), ty(_ty), tz(_tz)
	{}

	Vertex(const Vertex& _other) { *this = _other; }

    static VertexDeclaration& decl()
    {
        static auto d =
        VertexDeclaration::begin()
            .float32(3, VertexAttribute::Name::position)
            .float32(3, VertexAttribute::Name::normal)
            .float32(3, VertexAttribute::Name::tangent)
            .float32(2, VertexAttribute::Name::texcoord0)
        .end();
        return d;
    }

	Vertex& operator = (const Vertex& _other)
    {
		px = _other.px; py = _other.py; pz = _other.pz;
		nx = _other.nx; ny = _other.ny; nz = _other.nz;
		tx = _other.tx; ty = _other.ty; tz = _other.tz;
		u = _other.u; v = _other.v;
		return *this;
	}
};

Vertex vertices[] =
{
    // back face
    Vertex(-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f), // bottom-left
    Vertex(1.0f,   1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f, -1.0f), // top-right
    Vertex(1.0f,  -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,  0.0f, -1.0f), // bottom-right
    Vertex(-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f), // top-left
    // front face
    Vertex(-1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f,  0.0f,  1.0f), // bottom-left
    Vertex(+1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 0.0f,  0.0f,  1.0f), // bottom-right
    Vertex(+1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  0.0f,  1.0f), // top-right
    Vertex(-1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  0.0f,  1.0f), // top-left
    // left face
    Vertex(-1.0f,  1.0f,  1.0f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f), // top-right
    Vertex(-1.0f,  1.0f, -1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f), // top-left
    Vertex(-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f), // bottom-left
    Vertex(-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f), // bottom-right
    // right face
    Vertex(+1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f), // top-left
    Vertex(+1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f), // bottom-right
    Vertex(+1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f), // top-right
    Vertex(+1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f), // bottom-left
    // bottom face
    Vertex(-1.0f, -1.0f, -1.0f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f), // top-right
    Vertex(+1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f), // top-left
    Vertex(+1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f), // bottom-left
    Vertex(-1.0f, -1.0f,  1.0f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f), // bottom-right
    // top face
    Vertex(-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f), // top-left
    Vertex(+1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f), // bottom-right
    Vertex(+1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f), // top-right
    Vertex(-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f), // bottom-left
};

u32 indices[] = {1, 0, 2, 0, 1, 3, 5, 4, 6, 6, 4, 7, 9, 8, 10, 10, 8, 11, 13, 12, 14, 12, 13, 15, 17, 16, 18, 18, 16, 19, 21, 20, 22, 20, 21, 23};

Vertex vertices2[] =
{
    Vertex(-0.8f, -0.8f, 0.0f, 0.0f, 0.0f),
    Vertex( 0.0f,  0.8f, 0.0f, 0.5f, 1.0f),
    Vertex( 0.8f, -0.8f, 0.0f, 1.0f, 0.0f),
};

u32 indices2[] = {0, 1, 2};

#include "Graphics/OpenGL/OpenGLHeaders.h"

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";

    MICHKA_LOG("This is debug!");
    MICHKA_INFO("This is info!");
    MICHKA_WARNING("This is warning!");
    MICHKA_ERROR("This is error!");
    MICHKA_CRITICAL("This is critical!");
    MICHKA_ABORT("Hello World");
    Log::info(MICHKA_SRC_PATH, __FILE__, __LINE__);
    system("PAUSE");
    return 0;
    Image image("test-assets/grass.jpg");

    Window* window = new Window();
    Window* window2 = new Window();
    Device* device = Device::instance(Device::Driver::openGL);
    window->show();
    window2->show();
    Texture* rt1 = device->createTexture(320, 240, Michka::TextureFormat::r8g8b8, true);
    Texture* rt2 = device->createTexture(320, 240, Michka::TextureFormat::r8g8b8, true);
    Texture* db = device->createTexture(320, 240, Michka::TextureFormat::depth32, true);
    IndexBuffer* ib = device->createIndexBuffer();
    ib->set(indices2, sizeof(indices2) / sizeof(indices2[0]));
    VertexBuffer* vb = device->createVertexBuffer(&Vertex::decl());
    vb->set(vertices2, sizeof(vertices2));
    Texture* texture = device->createTexture(image);
    Shader* shader = device->createShader(File::getContents("shaders/test.vert"), File::getContents("shaders/test.frag"));
    if (! shader->compile())
    {
        MessageBoxW(0, shader->getErrors().cstr(), L"ERROR", MB_OK);
        exit(-1);
    }

    bool firstTime = true;
    int j = 0;

    while (window->isDestroyed() == false)
    {
        std::cout << j++ << " : " << window->isDestroyed() << std::endl;
        device->setRenderTarget(0, rt1);
        device->setRenderTarget(1, rt2);
        device->setDepthBuffer(db);
        device->clear(true, true, true, Vector4(0.4f, 0.8f, 1.0f, 1.0f));
        device->setIndexBuffer(ib);
        device->setVertexBuffer(vb);
        device->setShader(shader);
        shader->set("test", ((clock()/1000)%3) + 1);
        shader->set("testTexture", texture);
        device->draw();

        device->setWindow(window);
        device->drawOnScreen(rt1);
        device->setWindow(window2);
        device->drawOnScreen(rt2);

        if (firstTime)
        {
            rt1->get().save("test-assets/screenshot.jpg");
            firstTime = false;
        }
    }

    delete vb;
    delete ib;
    delete shader;
    delete texture;
    delete window;
    delete window2;

    std::cout << "\nBYE\n";
    system("PAUSE");
    return 0;
}
