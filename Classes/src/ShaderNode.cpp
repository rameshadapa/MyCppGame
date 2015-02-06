#include "ShaderNode.h"

USING_NS_CC;

ShaderNode::ShaderNode() : _center(Vec2(0.0f, 0.0f)),
			   _resolution(Vec2(0.0f, 0.0f)),
			   _time(0.0f),
			   _type(false)
{
}

ShaderNode::~ShaderNode()
{
}

ShaderNode* ShaderNode::shaderNodeWithVertex(const std::string &vert, const std::string &frag)
{
	auto node = new (std::nothrow) ShaderNode();
	node->initWithVertex(vert, frag);
	node->autorelease();

	return node;
}

bool ShaderNode::initWithVertex(const std::string &vert, const std::string &frag)
{
	Size size = Director::getInstance()->getVisibleSize();
#if CC_ENABLE_CACHE_TEXTURE_DATA
	auto listener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom *event) {
		this->setGLProgramState(nullptr);
		loadShaderVertex(_vertFileName, _fragFileName);
	});

    	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

#endif
    	_vertFileName = vert;
	_fragFileName = frag;

  	loadShaderVertex(vert, frag);

	_time = 0;
	_resolution = Vec2(size.width, size.height);

	getGLProgramState()->setUniformVec2("resolution", _resolution);
	scheduleUpdate();
	setContentSize(Size(size.width, size.height));
	setAnchorPoint(Vec2(0.5f, 0.5f));

	return true;
}

void ShaderNode::loadShaderVertex(const std::string &vert, const std::string &frag)
{
	auto fileUtils = FileUtils::getInstance();
	
	//frag
	auto fragmentFilePath = fileUtils->fullPathForFilename(frag);
	auto fragSource = fileUtils->getStringFromFile(fragmentFilePath);

	//vert
	std::string vertSource;
	if(vert.empty())
	{
		vertSource = ccPositionTextureColor_vert;
	} else {
		std::string vertexFilePath = fileUtils->fullPathForFilename(vert);
		vertSource = fileUtils->getStringFromFile(vertexFilePath);
	}
	
	auto glprogram = GLProgram::createWithByteArrays(vertSource.c_str(), fragSource.c_str());
	auto glProgramState = GLProgramState::getOrCreateWithGLProgram(glprogram);
	setGLProgramState(glProgramState);
}

void ShaderNode::update(float dt)
{
/*	if(_type)
	{
		getGLProgramState()->setUniformVec2("lightposition", _lightPos);
	}*/
	_time += dt;
}

void ShaderNode::setPosition(const Vec2 &newPosition)
{
	Node::setPosition(newPosition);
	auto position = getPosition();
	_center = Vec2(position.x * CC_CONTENT_SCALE_FACTOR(), position.y * CC_CONTENT_SCALE_FACTOR());
	getGLProgramState()->setUniformVec2("center", _center);
}

void ShaderNode::setLightPos(const Vec2 &position)
{
	_lightPos = position;
//	getGLProgramState()->setUniformVec2("lightposition", position);
}

void ShaderNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);
}

void ShaderNode::onDraw(const Mat4 &transform, uint32_t flags)
{
	Size size = Director::getInstance()->getVisibleSize();
	float w = size.width, h = size.height;
	GLfloat vertices[12] = {0, 0, w, 0, w, h, 0, 0, 0, h, w, h};

	auto glProgramState = getGLProgramState();
	glProgramState->setVertexAttribPointer("a_position", 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glProgramState->apply(transform);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
	CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, 6);
}
