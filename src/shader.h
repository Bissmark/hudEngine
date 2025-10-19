#pragma once

#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "transform.h"
#include "camera.h"

class Shader
{
    public:
        Shader(const std::string& fileName);
		virtual ~Shader();

		void Bind();
		void Update(const Transform& transform, const Camera& camera);
		void SetLightDirection(const glm::vec3& lightDir);
		void SetPerlinNoise(bool usePerlin, float noiseScale);

		GLuint GetProgram() const { return m_program; }
    private:
        static const unsigned int NUM_SHADERS = 2;

		enum
		{
			TRANSFORM_U,
			USE_PERLIN_NOISE_U,
			NOISE_SCALE_U,
			CAMERA_POS_U,
			LIGHT_DIR_U,
			NOISE_AMPLITUDE_U,
			NUM_UNIFORMS
		};

		GLuint m_program;
		GLuint m_shaders[NUM_SHADERS];
		GLuint m_uniforms[NUM_UNIFORMS];
};