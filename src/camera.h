#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
    public:
        Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
        ~Camera();

        void Update();
    private:
};