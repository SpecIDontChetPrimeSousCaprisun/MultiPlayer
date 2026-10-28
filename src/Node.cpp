#include "Node.hpp"

Node::Node() : parent(nullptr) {}
Node::Node(Node* parent) {
    setParent(parent);
}

void Node::onDelete() {}
Node::~Node() {
    onDelete();
    unparent();
    
    for (auto it = children.begin(); it != children.end(); ) {
	delete *it;
	it = children.erase(it);
    }
}

void Node::draw() {}
void Node::drawChildren() {
    for (Node* child : children) {
	child->draw();
    }

    for (Node* child : children) {
	child->drawChildren();
    }
}

void Node::update() {}
void Node::updateChildren() {
    for (Node* child : children) {
	child->update();
    }

    for (Node* child : children) {
	child->updateChildren();
    }
}

void Node::setParent(Node* parent) {
    unparent();
    this->parent = parent;
    parent->children.push_back(this);
}

void Node::unparent() {
    if (!parent) return;

    for (auto it = parent->children.begin(); it != parent->children.end();) {
	if (*it == this) {
	    it = parent->children.erase(it);
	    break;
	} else {
	    it++;
	}
    }

    parent = nullptr;
}

Node* Node::getParent() { return parent; }
std::vector<Node*> Node::getChildren() { return children; }

glm::vec2 Node::getWorldPos() {
    glm::vec2 worldPos = position;

    if (parent) {
	worldPos += parent->getWorldPos();
    }

    return worldPos;
}

glm::vec2 Node::getWorldSize() {
    glm::vec2 worldSize = size;

    if (parent) {
	worldSize += parent->getWorldSize();
    }

    return worldSize;
}
