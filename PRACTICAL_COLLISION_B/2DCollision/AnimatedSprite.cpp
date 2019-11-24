#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() 
{
	m_current_frame = 0;
}

AnimatedSprite::AnimatedSprite(const sf::Texture& t) : Sprite(t), m_current_frame(0), m_time(seconds(2.0f)) {}

AnimatedSprite::AnimatedSprite(const sf::Texture& t, const sf::IntRect& rect) : Sprite(t), m_current_frame(0), m_time(seconds(2.0f)) {
	m_frames.push_back(rect);
	Sprite::setTexture(t);
}

AnimatedSprite::~AnimatedSprite() {}

const sf::Clock& AnimatedSprite::getClock() {
	return m_clock;
}

const sf::Time& AnimatedSprite::getTime() {
	return m_time;
}

const vector<IntRect>& AnimatedSprite::getFrames() {
	return m_frames;
}

const IntRect& AnimatedSprite::getFrame(int n) {
	return m_frames[n];
}

void AnimatedSprite::addFrame(IntRect& frame) {
	m_frames.push_back(frame);
	Sprite::setTextureRect(m_frames[m_current_frame]);
}

const int AnimatedSprite::getCurrentFrame() {
	return m_current_frame;
}

void AnimatedSprite::update(){
	if (m_clock.getElapsedTime() > m_time) {
		if (m_frames.size() > m_current_frame + 1)
		{
			m_current_frame++;
			Sprite::setTextureRect(m_frames[m_current_frame]);
		}
		else {
			m_current_frame = 0;
			Sprite::setTextureRect(m_frames[m_current_frame]);
		}
		m_clock.restart();
	}
}

void AnimatedSprite::reset()
{
	m_current_frame = 0;
}

