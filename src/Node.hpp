#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Node {
public:
    Node();
    Node(Node* parent);
    virtual ~Node();

    void drawChildren();
    void updateChildren();
    void setParent(Node* parent);
    void unparent();
    Node* getParent();
    std::vector<Node*> getChildren();
    glm::vec2 getWorldPos();
    glm::vec2 getWorldSize();
    float getWorldRotation();

    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    glm::vec2 size = glm::vec2(0.0f, 0.0f);
    float rotation = 0.0f;
protected:
    virtual void onDelete();
    virtual void draw();
    virtual void update();
private:
    Node* parent = nullptr;
    std::vector<Node*> children;
};
