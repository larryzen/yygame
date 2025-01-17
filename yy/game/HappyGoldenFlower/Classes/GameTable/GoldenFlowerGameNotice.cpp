#include "GoldenFlowerGameNotice.h"
#include "cocostudio/CocoStudio.h"
#include "HNLobbyExport.h"
//#include "FontConfig.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

namespace goldenflower
{
	static const char* NOTICE_BG_SRC  = "goldenflower/noticemessege/notice_bg.png";

	GameNotice::GameNotice()
		:_bg(nullptr)
	{

	}

	GameNotice::~GameNotice()
	{

	}

	GameNotice* GameNotice::create(cocos2d::Node* parent, std::string noticeMsg)
	{
		GameNotice* ptr = new GameNotice();
		if (nullptr != ptr && ptr->init(parent,noticeMsg))
		{
			ptr->autorelease();
			return ptr;
		}
		return nullptr;
	}

	bool GameNotice::init(cocos2d::Node* parent, std::string& noticeMsg)
	{
		if (!HNLayer::init())
		{
			return false;
		}

		_parent = parent;
		HNSprite* sp = HNSprite::create(NOTICE_BG_SRC);
		//sp->setScale(0.5f);
		Size size = sp->getContentSize();
		this->ignoreAnchorPointForPosition(false);
		this->setContentSize(size);

		sp->setAnchorPoint(Vec2(0.5f, 0.5f));
		sp->setPosition(size.width / 2, size.height / 2);
		sp->ignoreAnchorPointForPosition(false);
		addChild(sp, 0);
		_bg = sp;

		//auto contextLable = Label::createWithTTF(gFontConfig_22, noticeMsg);
		auto contextLable = Label::createWithSystemFont(noticeMsg, "", 22);

		contextLable->setAnchorPoint(Vec2(0.5f, 0.5f));
		contextLable->setPosition(Vec2(size.width / 2, size.height / 2));
		addChild(contextLable, 1);

		return true;
	}

	void GameNotice::show(bool bAction)
	{
		auto winSize = Director::getInstance()->getWinSize();
		this->setPosition(winSize.width * 0.5f, winSize.height * 0.62f);
		this->setScale(bAction?0.0f:1.2f);
		_parent->addChild(this);
	

		if (bAction)
		{
			auto come = ScaleTo::create(0.3f, 1.0f);
			auto leave = ScaleTo::create(0.3f, 0.0f);
			auto seq = Sequence::create(come, DelayTime::create(2.0f), leave, RemoveSelf::create(true), nullptr);
			this->runAction(seq);
		}
	}

	void GameNotice::hide()
	{
		this->setVisible(false);
		_parent->removeChild(this);
	}
}



