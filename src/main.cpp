#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "Michka.h"
#include <Windows.h>
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

class Person
{
public:
    Person()
    {
        //
    }

    Person(const Michka::String& _name)
    {
        mName = _name;
    }

    Person(const Person& _other)
    {
        mName = _other.mName;
    }

    Person(Person&& _other)
    {
        mName = std::move(_other.mName);
    }

    Michka::String getName() const
    {
        return mName;
    }

    void runSomething(int i)
    {
        printf("Very long started %d %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
        for (int j = 0; j < 300; j++)
        {
            Sleep(10);
        }
        printf("Very long ended %d %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
    }

    void runSomething2()
    {
        printf("Very long started %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
        for (int j = 0; j < 300; j++)
        {
            Sleep(10);
        }
        printf("Very long ended %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
    }

    static void runSomethingStatic(Person* p)
    {
        (p->runSomething)(14);
    }
protected:
    Michka::String mName;
};


void sayHello(int i)
{
    printf("Very long started %d - %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
    for (int i = 0; i < 300; i++)
    {
        Sleep(10);
    }
    printf("Very long ended %d - %llu (%llu)\n", i, Thread::getCurrent()->getId(), Thread::getCurrentId());
}

Mutex mutex;

class CustomThread : public Thread
{
protected:
    void run() override
    {
        printf("Very long started %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
        for (int i = 0; i < 50; i++)
        {
            MutexLock ml(mutex);
            Sleep(10);
        }
        printf("Very long ended %llu (%llu)\n", Thread::getCurrent()->getId(), Thread::getCurrentId());
    }
};

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
    Vertex(-1.0f,  1.0f,  1.0f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f)  // bottom-left
};

u32 indices[] = {1, 0, 2, 0, 1, 3, 5, 4, 6, 6, 4, 7, 9, 8, 10, 10, 8, 11, 13, 12, 14, 12, 13, 15, 17, 16, 18, 18, 16, 19, 21, 20, 22, 20, 21, 23};

int main()
{
    std::cout << "Welcome to engine!\n-------------------------------------\n\n";

    Device* device = Device::instance(Device::Driver::OpenGL);
    VertexBuffer* vb = device->createVertexBuffer(&Vertex::decl());
    vb->set(&vertices, sizeof(vertices));
    IndexBuffer* ib = device->createIndexBuffer();
    vb->set(&indices, sizeof(indices) / sizeof(indices[0]));

    while (device->getWindow()->isDestroyed() == false)
    {
        device->clear(true, true, true, Vector4(0.2f, 0.7f, 1.0f, 1.0f));
        device->setVertexBuffer(vb);
        device->setIndexBuffer(ib);
        //
    }

    delete vb;
    delete ib;

    std::cout << "\nBYE\n";
    system("PAUSE");
    return 0;
}
