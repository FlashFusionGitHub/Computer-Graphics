#include <glm/glm.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

class Mesh {
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	struct  Vertex {
		vec4 position;
		vec4 normal;
		vec2 texCoord;
	};

	void initialiseQuad();
	void initialiseFullscreenQuad();

	virtual void draw();

protected:
	unsigned int triCount;
	unsigned int vao, vbo, ibo;
};

