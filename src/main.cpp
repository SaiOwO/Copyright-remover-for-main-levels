#include <Geode/Geode.hpp>
#include <Geode/modify/GameOptionsLayer.hpp>
#include <Geode/modify/LevelSelectLayer.hpp>
#include <Geode/modify/FMODAudioEngine.hpp>

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

class $modify(FMODAudioEngine) {
    TodoReturn loadMusic(gd::string p0, float p1, float p2, float p3, bool p4, int p5, int p6) {
        std::string song = p0;

        if (Mod::get()->getSettingValue<bool>("no-copyright")) {
            switch (hash(song.c_str())) {
                case hash("StereoMadness.mp3"): p0 = "StereoMadnessAlt.mp3"_spr; break;
                case hash("BackOnTrack.mp3"): p0 = "BackOnTrackAlt.mp3"_spr; break;
                case hash("Polargeist.mp3"): p0 = "PolargeistAlt.mp3"_spr; break;
                case hash("DryOut.mp3"): p0 = "DryOutAlt.mp3"_spr; break;
                case hash("BaseAfterBase.mp3"): p0 = "BaseAfterBaseAlt.mp3"_spr; break;
                case hash("CantLetGo.mp3"): p0 = "CantLetGoAlt.mp3"_spr; break;
                case hash("Jumper.mp3"): p0 = "JumperAlt.mp3"_spr; break;
                case hash("TimeMachine.mp3"): p0 = "TimeMachineAlt.mp3"_spr; break;
                case hash("Cycles.mp3"): p0 = "CyclesAlt.mp3"_spr; break;
                case hash("xStep.mp3"): p0 = "xStepAlt.mp3"_spr; break;
                case hash("Clutterfunk.mp3"): p0 = "ClutterfunkAlt.mp3"_spr; break;
                case hash("TheoryOfEverything.mp3"): p0 = "TheoryOfEverythingAlt.mp3"_spr; break;
                case hash("Electroman.mp3"): p0 = "ElectromanAlt.mp3"_spr; break;
                case hash("Clubstep.mp3"): p0 = "ClubstepAlt.mp3"_spr; break;
                case hash("Electrodynamix.mp3"): p0 = "ElectrodynamixAlt.mp3"_spr; break;
                case hash("HexagonForce.mp3"): p0 = "HexagonForceAlt.mp3"_spr; break;
                case hash("BlastProcessing.mp3"): p0 = "BlastProcessingAlt.mp3"_spr; break;
                case hash("TheoryOfEverything2.mp3"): p0 = "TheoryOfEverything2Alt.mp3"_spr; break;
                case hash("GeometricalDominator.mp3"): p0 = "GeometricalDominatorAlt.mp3"_spr; break;
                case hash("Deadlocked.mp3"): p0 = "DeadlockedAlt.mp3"_spr; break;
                case hash("Fingerdash.mp3"): p0 = "FingerdashAlt.mp3"_spr; break;
                case hash("Dash.mp3"): p0 = "DashAlt.mp3"_spr; break;
            }
        }
        return FMODAudioEngine::loadMusic(p0, p1, p2, p3, p4, p5, p6);
    }
};

