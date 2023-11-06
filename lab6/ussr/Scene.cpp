#include "pch.h"
#include <glm/glm.hpp>
#include "Scene.h"
#include <vector>

Scene::~Scene()
{
    delete[] m_vertices;
    delete[] m_arr;
    delete[] m_indices;
}

void Scene::SetupFlag(float width, float height, int pixels)
{
    width = width / pixels;
    height = height / pixels;
    int widthSegments = 100,
        heightSegments = 100;

    float
        textureWidth = 1,
        textureHeight = 1,
        textureWidthStep = textureWidth / (float)widthSegments,
        textureHeightStep = textureHeight / (float)heightSegments,
        widthStep = width / (float)widthSegments,
        heightStep = height / (float)heightSegments;

    glm::vec3 startPoint(100, 100, 0);


    int pointsCount = widthSegments * heightSegments;

    m_verticesCount = 8 * widthSegments * heightSegments;

    m_arr = new float[m_verticesCount];

    int indecessBufferSize = widthSegments * heightSegments * 6;
    m_indices = new unsigned int[indecessBufferSize];
    float debug = 0;
    // Садание буффера точек (получается прямоугольник)
    for (size_t i = 0; i < heightSegments; i++) {
        for (size_t j = 0; j < widthSegments; j++) {
            size_t arrIndex = j + (i * widthSegments);
            int arrBufferIndex = arrIndex * 8;
            // X
            m_arr[arrBufferIndex] = startPoint.x + (j * widthStep);
            // Y
            m_arr[arrBufferIndex + 1] = startPoint.y + (i * heightStep);
            // Z
            m_arr[arrBufferIndex + 2] = startPoint.z + 0;
            // texX
            m_arr[arrBufferIndex + 3] = i * textureHeightStep;
            // texY
            m_arr[arrBufferIndex + 4] = j * textureWidthStep;

            m_arr[arrBufferIndex + 5] = 0.0f;
            m_arr[arrBufferIndex + 6] = 0.0f;
            m_arr[arrBufferIndex + 7] = 0.0f;
            debug = arrBufferIndex + 7;

            /* Задаются индексы вершин
                0-----1
                |   / |
                |  /  |
                | /   |
                2-----3
            */
            if (!(j >= (widthSegments - 1)) && !(i >= (heightSegments - 1))) {
                auto indx = arrIndex * 6;
                // 0
                m_indices[indx] = arrIndex;
                // 1
                m_indices[indx + 1] = arrIndex + 1;
                // 2
                m_indices[indx + 2] = arrIndex + widthSegments;
                // 1
                m_indices[indx + 3] = arrIndex + 1;
                // 2
                m_indices[indx + 4] = arrIndex + widthSegments;
                // 3
                m_indices[indx + 5] = arrIndex + widthSegments + 1;
            }

        }
    }

    glGenVertexArrays(1, &m_buffer);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_buffer);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * pointsCount * 8, m_arr, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);


    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * pointsCount * 6, m_indices, GL_STATIC_DRAW);

    // vert location
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vert aTexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // vert aNormal
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);
}

void Scene::Draw()
{
    glBindVertexArray(m_buffer);
    glDrawElements(GL_TRIANGLES, m_verticesCount, GL_UNSIGNED_INT, 0);
}