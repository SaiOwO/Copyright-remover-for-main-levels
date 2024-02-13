#include <Geode/Geode.hpp>
#include <Geode/modify/GameOptionsLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/LevelTools.hpp>

using namespace geode::prelude;

struct Copyright {
    void onCopyright(CCObject*) {
        Mod::get()->setSettingValue<bool>("no-copyright", !Mod::get()->getSettingValue<bool>("no-copyright"));
    }
    void onInfo(CCObject*) {
        FLAlertLayer::create("Info", "To apply the change you need restart your attempt\n<cr>(this function only works with main songs, not with customs)</c>", "OK")->show();
    }
};

class $modify(GameOptionsLayer) {
    static GameOptionsLayer* create(GJBaseGameLayer* p0) {
        auto ret = GameOptionsLayer::create(p0);

        auto toggle = CCMenuItemToggler::createWithStandardSprites(ret, menu_selector(Copyright::onCopyright), .8f);
        toggle->setPosition({-100,113});
        toggle->toggle(Mod::get()->getSettingValue<bool>("no-copyright"));
        ret->m_buttonMenu->addChild(toggle);

        auto infoIcon = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        infoIcon->setScale(.5f);
        auto infoBtn = CCMenuItemSpriteExtra::create(infoIcon, ret, menu_selector(Copyright::onInfo));
        infoBtn->setSizeMult(1.5f);
        infoBtn->setPosition({toggle->getPositionX() - 17, toggle->getPositionY() + 17});
        ret->m_buttonMenu->addChild(infoBtn);

        auto text = CCLabelBMFont::create("No copyright", "bigFont.fnt");
        text->setScale(.4f);
        text->setAnchorPoint({0,.5f});
        text->setPosition({toggle->getPositionX() + 20, toggle->getPositionY()});
        ret->m_buttonMenu->addChild(text, 10);

        return ret;
    }
};

class $modify(LevelSelectLayer) {
	bool init(int p0) {
		if (LevelSelectLayer::init(p0));
        
		auto s = CCDirector::sharedDirector()->getWinSize();

        auto menu = CCMenu::create();
        menu->setPosition({ 0, 0 });

        auto sombra = extension::CCScale9Sprite::create("square02_small.png");
        sombra->setContentSize({ 105, 31 });
        sombra->setOpacity(150);
        sombra->setPosition({ 57.5f, 20 });
        this->addChild(sombra, 10);

        auto toggle = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(Copyright::onCopyright), 0.7f);
        toggle->setPosition({20,20});
        toggle->toggle(Mod::get()->getSettingValue<bool>("no-copyright"));
        menu->addChild(toggle);

        auto text = CCLabelBMFont::create("No\nCopyright", "bigFont.fnt");
        text->setScale(.35f);
        text->setAnchorPoint({0,.5f});
        text->setPosition({toggle->getPositionX() + 18, toggle->getPositionY()});
        this->addChild(text, 10);

        this->addChild(menu, 10);

        return true;
	} 
};

class $modify(LevelTools) {
    static gd::string getAudioFileName(int p0) {
        gd::string song = "StereoMadness";

        switch (p0) {
            case 1: song = "BackOnTrack"; break;
            case 2: song = "Polargeist"; break;
            case 3: song = "DryOut"; break;
            case 4: song = "BaseAfterBase"; break;
            case 5: song = "CantLetGo"; break;
            case 6: song = "Jumper"; break;
            case 7: song = "TimeMachine"; break;
            case 8: song = "Cycles"; break;
            case 9: song = "xStep"; break;
            case 10: song = "Clutterfunk"; break;
            case 11: song = "TheoryOfEverything"; break;
            case 12: song = "Electroman"; break;
            case 13: song = "Clubstep"; break;
            case 14: song = "Electrodynamix"; break;
            case 15: song = "HexagonForce"; break;
            case 16: song = "BlastProcessing"; break;
            case 17: song = "TheoryOfEverything2"; break;
            case 18: song = "GeometricalDominator"; break;
            case 19: song = "Deadlocked"; break;
            case 20: song = "Fingerdash"; break;
            case 21: song = "Dash"; break;
            case 22: song = "Explorers"; break;
            case 26: song = "djRubRub"; break;
        }

        if (Mod::get()->getSettingValue<bool>("no-copyright")) 
            song = CCString::createWithFormat("%sAlt.mp3"_spr, song.c_str())->getCString();
        else 
            song = CCString::createWithFormat("%s.mp3", song.c_str())->getCString();

        return song;
    }
};
