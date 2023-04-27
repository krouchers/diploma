#include "utils/generate_primitives.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace utils
{

    Data GenerateCube(float edgeLenght)
    {
        float r{edgeLenght};
        return {{{glm::vec3{-r, -r, -r}, glm::normalize(glm::vec3{-r, -r, -r}), 0},
                 {glm::vec3{r, -r, -r}, glm::normalize(glm::vec3{r, -r, -r}), 0},
                 {glm::vec3{r, r, -r}, glm::normalize(glm::vec3{r, r, -r}), 0},
                 {glm::vec3{-r, r, -r}, glm::normalize(glm::vec3{-r, r, -r}), 0},
                 {glm::vec3{-r, -r, r}, glm::normalize(glm::vec3{-r, -r, r}), 0},
                 {glm::vec3{r, -r, r}, glm::normalize(glm::vec3{r, -r, r}), 0},
                 {glm::vec3{r, r, r}, glm::normalize(glm::vec3{r, r, r}), 0},
                 {glm::vec3{-r, r, r}, glm::normalize(glm::vec3{-r, r, r}), 0}},
                {0, 1, 3, 3, 1, 2, 1, 5, 2, 2, 5, 6, 5, 4, 6, 6, 4, 7,
                 4, 0, 7, 7, 0, 3, 3, 2, 7, 7, 2, 6, 4, 5, 0, 0, 5, 1}};
    }
}